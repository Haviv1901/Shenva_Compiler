
#ifndef INSTRUCTIONWRITING_H
#include "InstructionWriting.h"
#endif
#include <stdio.h>


#include "fileHelper.h"
bool isLastValFloat = false;
unsigned long lableNum = 0;
int currentScope = 0;
int ScopeCounter = 0;

/// <summary>
/// function to copy the functions and the assembly code bone to the assembly file
/// </summary>
/// <param name="asmFile"> asmFile file to copy to </param>
/// <param name="boneFileNumber"> false for first bone file, true for second bone file </param>
void copyBoneFile(FILE* asmFile, bool boneFileNumber)
{
	FILE* boneFile = openFile(boneFileNumber ? SECOND_BONE_FILE : FIRST_BONE_FILE, "r");
	// Open FIRST_BONE_FILE for reading

	if (boneFile == NULL)
	{
		printf("Error opening file %s\n", boneFileNumber ? SECOND_BONE_FILE : FIRST_BONE_FILE);
		return;
	}
	printf("Successfully opened file %s\n", boneFileNumber ? SECOND_BONE_FILE : FIRST_BONE_FILE);


	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), boneFile) != NULL)
	{
		fputs(buffer, asmFile);
	}

	fclose(boneFile);
}

/**
 * \brief function will convert the AST to assembly code
 * \param tree AST
 * \param fileName sulotion file name
 */
void convertASTToASM(ASTNode* tree, const char* fileName, VariableList* varList)
{
	char* asmPath = NULL;
	asmPath = (char*)calloc(strlen(fileName) + 5, sizeof(char));

	strcpy(asmPath, fileName);
	strcat(asmPath, ".asm");
	FILE* asmFile = openFile(asmPath, "w");

	copyBoneFile(asmFile, FIRST); // copy first half of the basic functions and start of main

	writeBranch(tree, asmFile, varList); // write instructions from the ast

	copyBoneFile(asmFile, SECOND); // copy the second half
	free(asmPath);
	fclose(asmFile);
}



/*
writeBranch: this function will write all instructions to the asm file after the first bone was added
input: the tree, and the asm file
output: non
*/
void writeBranch(ASTNode* tree, FILE* asmFile, VariableList* varList)
{
	if (tree == NULL)// if the tree is null do nothing
	{
		return;
	}

	Token* currentToken;
	ASTNode* next = NULL;
	int labelHolder = 0;
	bool isNullFlag = false;
	if (tree->token == NULL)
	{
		currentToken = tree->children[EXPRESSION]->token;// getting the command part of this node
		next = tree->children[NEXT];
		tree = tree->children[EXPRESSION];
		isNullFlag = true;
	}
	else
	{
		currentToken = tree->token;// getting the command part of this node
		isNullFlag = false;
	}


	if (isExpressionToken(*currentToken) || isBooleanExpressionToken(currentToken->type) || currentToken->type == TOKEN_OR || currentToken->type == TOKEN_AND) // checking for expression branch
	{
		isLastValFloat = writeLogicalBranch(tree, asmFile, varList);
		if (isNullFlag)
		{
			fprintf(asmFile, "pop eax\n");
		}
	}
	else if (isPrintToken(*currentToken) || isInputToken(*currentToken))// checking for function branch
	{
		writeFunctionBranch(tree, asmFile, varList);
	}
	else if (currentToken->type == TOKEN_INT ||
		currentToken->type == TOKEN_CHAR ||
		currentToken->type == TOKEN_FLOAT || currentToken->type == TOKEN_BOOL)// checking for decleration branch
	{
		writeDeclerationBranch(tree, asmFile, varList);
	}
	else if (currentToken->type == TOKEN_ASSIGN)
	{
		writeAssignBranch(tree, asmFile, varList);
	}
	else if(currentToken->type == TOKEN_IF)
	{
		labelHolder = lableNum;
		lableNum++;
		writeConditionBranch(tree, asmFile, varList, labelHolder);
		fprintf(asmFile, "label_%d:\n", labelHolder);
	}
	if (next != NULL)
	{
		writeBranch(next, asmFile, varList);
	}

}


/*
writeConditionBranch: this fucntion will write a condition bracnch
input: the branch, asm file, vairable list and the label to the end of the block
output: non
*/
void writeConditionBranch(ASTNode* branch, FILE* asmFile, VariableList* varList, int endLabel)
{
	int finishLabel = lableNum, scopeSaver = currentScope, scopeSize = 0;
	lableNum++;

	ASTNode* elseBranch = branch->children[ELSE];
	writeBranch(branch->children[CONDITION], asmFile, varList);//writing condition

	fprintf(asmFile, "pop eax\n");
	fprintf(asmFile, "cmp eax, 0\n");
	fprintf(asmFile, "je label_%d\n", finishLabel);//going to next if

	ScopeCounter++;
	currentScope = ScopeCounter;//going into scope

	writeBranch(branch->children[CODE], asmFile, varList);//writing the block
	currentScope = scopeSaver;//retreiving scope

	scopeSize = getSizeOfScope(varList, currentScope + 1);//deleteing scope
	if (scopeSize != 0)
	{
		fprintf(asmFile, "add esp, %d\n", scopeSize);
	}

	fprintf(asmFile, "jmp label_%d\n", endLabel);//ending label, and opening next
	fprintf(asmFile, "label_%d:\n", finishLabel);

	lableNum++;
	if (elseBranch != NULL)//if there is an else branch
	{
		if (elseBranch->children[0] == NULL)//if empty else
		{
			return;
		}
		else if (elseBranch->children[0]->token == NULL)//is virgin else
		{
			ScopeCounter++;
			currentScope = ScopeCounter;

			writeBranch(elseBranch->children[0], asmFile, varList);
			currentScope = scopeSaver;
		}
		else// if else if
		{
			writeConditionBranch(elseBranch->children[0], asmFile, varList, endLabel);
		}
	}
}





/*
writeAssignBranch: this function will write an assign branch into the asm file
input: the decleration branch, and the asm file
output: non
*/
void writeAssignBranch(ASTNode* branch, FILE* asmFile, VariableList* varList) 
{
	writeBranch(branch->children[1], asmFile, varList);
	if (getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->Type == VAR_CHAR || getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->Type == VAR_BOOL)
	{
		if (isLastValFloat)
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}
		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "mov byte ptr [ebp - %d], al\n", getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->placeInMemory);
		
	}
	else if (getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->Type == VAR_INT)
	{
		if (isLastValFloat)
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}
		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "mov [ebp - %d], eax\n", getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->placeInMemory);
	}
	else if (getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->Type == VAR_FLOAT)
	{
		if (!isLastValFloat)
		{
			fprintf(asmFile, "fild dword ptr [esp]\n");
			fprintf(asmFile, "fstp dword ptr [esp]\n");
		}
		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "mov [ebp - %d], eax\n", getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->placeInMemory);
	}

}

/*
writeDeclerationBranch: this function will write a decleration branch into the asm file
input: the decleration branch, and the asm file
output: non
*/
void writeDeclerationBranch(ASTNode* branch, FILE* asmFile, VariableList* varList)
{
	if (branch->token->type == TOKEN_INT)
	{
		if (branch->children[1] != NULL)
		{
			writeBranch(branch->children[1], asmFile, varList);
			if (isLastValFloat)
			{
				fprintf(asmFile, "call ConvertFloatToInt\n");
			}
		}
		else
		{
			fprintf(asmFile, "push 0\n");
		}
	}
	else if (branch->token->type == TOKEN_FLOAT)
	{
		if (branch->children[1] != NULL)
		{
			writeBranch(branch->children[1], asmFile, varList);
			if (!isLastValFloat)
			{
				fprintf(asmFile, "fild dword ptr [esp]\n");
				fprintf(asmFile, "fstp dword ptr [esp]\n");
			}
		}
		else
		{
			fprintf(asmFile, "push 0\n");
		}
	}
	else if (branch->token->type == TOKEN_CHAR || branch->token->type == TOKEN_BOOL)
	{

		fprintf(asmFile, "sub esp, 1\n");

		if (branch->children[1] != NULL)
		{
			writeBranch(branch->children[1], asmFile, varList);
			if (isLastValFloat)
			{
				fprintf(asmFile, "call ConvertFloatToInt\n");
			}
			fprintf(asmFile, "pop eax\n");
			fprintf(asmFile, "mov byte ptr [ebp - %d], al\n", getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->placeInMemory);
		}
		else
		{
			fprintf(asmFile, "mov byte ptr[esp], 0\n");
		}
	}

}





/*
writeLogicalBranch: this function will write a logical branch
input: the vranch, the asm file and the varlist.
output: a true or false for the isLastValFloat bool
*/
int writeLogicalBranch(ASTNode* branch, FILE* asmFile, VariableList* varList)
{
	bool is_float = false;
	if (branch->token->type == TOKEN_NOT)
	{
		writeLogicalBranch(branch->children[0], asmFile, varList);
		fprintf(asmFile, "xor dword ptr [esp], 1\n");// xoring the first bit
		return false;
	}
	else if (branch->token->type == TOKEN_AND)
	{
		writeLogicalBranch(branch->children[0], asmFile, varList);
		writeLogicalBranch(branch->children[1], asmFile, varList);

		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "pop ebx\n");

		fprintf(asmFile, "and eax, ebx\n");// logical and
		fprintf(asmFile, "push eax\n");
		return false;
	}
	else if (branch->token->type == TOKEN_OR)
	{
		writeLogicalBranch(branch->children[0], asmFile, varList);

		fprintf(asmFile, "cmp dword ptr [esp], 1\n");
		fprintf(asmFile, "je label_%d\n", lableNum);

		writeLogicalBranch(branch->children[1], asmFile, varList);// doing so only if the first value isnt 1
		fprintf(asmFile, "pop eax\n");

		fprintf(asmFile, "mov dword ptr [esp], eax\n");
		fprintf(asmFile, "label_%d:\n", lableNum);
		lableNum += 1;
		return false;
	}
	else
	{
		is_float = writeBooleanBranch(branch, asmFile, varList);// going to the next precendence
		return is_float;
	}
}










/*
writeBooleanBranch: this function will write a boolean branch
input: the vranch, the asm file and the varlist.
output: a true or false for the isLastValFloat bool
*/
int writeBooleanBranch(ASTNode* branch, FILE* asmFile, VariableList* varList)
{
	bool float_val = false;
	if (isBooleanExpressionToken(branch->token->type))// checking for boolean expressions
	{
		float_val = writeNumericBranch(branch->children[0], asmFile, varList);
		if (!float_val)
		{
			fprintf(asmFile, "fild dword ptr [esp]\n");
			fprintf(asmFile, "fstp dword ptr [esp]\n");
		}
		float_val = writeNumericBranch(branch->children[1], asmFile, varList);
		if (!float_val)
		{
			fprintf(asmFile, "fild dword ptr [esp]\n");
			fprintf(asmFile, "fstp dword ptr [esp]\n");
		}
		fprintf(asmFile, "pop ebx\n");
		fprintf(asmFile, "pop eax\n");

		fprintf(asmFile, "xor edx, edx\n");
		fprintf(asmFile, "cmp eax, ebx\n");

		writeJMPcondition(asmFile, branch->token->type);// taking coresponding jmp condition
		fprintf(asmFile, "mov edx, 1\n");
		fprintf(asmFile, "label_%d:\n", lableNum);

		fprintf(asmFile, "mov eax, edx\n");
		fprintf(asmFile, "push eax\n");
		lableNum += 1;
		return false;
	}
	else
	{
		float_val = writeNumericBranch(branch, asmFile, varList);
		return float_val;
	}
}


/*
this switch case will get a bool compairson type, and wrtie the right jmp condition
*/
void writeJMPcondition(FILE* asmFile, enum TokenTypes type)
{
	switch (type)
	{
	case TOKEN_EQUALS:// each condition is the opposite of the token's condition
		fprintf(asmFile, "jne label_%d\n", lableNum);
		break;
	case TOKEN_NOT_EQUALS:
		fprintf(asmFile, "je label_%d\n", lableNum);
		break;
	case TOKEN_GREATER:
		fprintf(asmFile, "jng label_%d\n", lableNum);
		break;
	case TOKEN_NOT_GREATER:
		fprintf(asmFile, "jg label_%d\n", lableNum);
		break;
	case TOKEN_LESSER:
		fprintf(asmFile, "jnl label_%d\n", lableNum);
		break;
	case TOKEN_NOT_LESSER:
		fprintf(asmFile, "jl label_%d\n", lableNum);
		break;
	case TOKEN_GREATER_EQUALS:
		fprintf(asmFile, "jl label_%d\n", lableNum);
		break;
	case TOKEN_LESSER_EQUALS:
		fprintf(asmFile, "jg label_%d\n", lableNum);
		break;
	default:
		break;
	}

}

/*
writeNumericBranch: this function will get a numeric branch and write it into the asm file
input: the branch and the asm file
output: non
*/
int writeNumericBranch(ASTNode* branch, FILE* asmFile, VariableList* varList)
{
	if (branch->token->type == TOKEN_NUM)
	{
		fprintf(asmFile, "push %d\n", *(int*)branch->token->value);
		return false;
	}
	if (branch->token->type == TOKEN_DECIMAL)
	{
		fprintf(asmFile, "push %d\n", getIEEE754(*(float*)branch->token->value));
		return true;
	}
	if (branch->token->type == TOKEN_LETTER)
	{
		fprintf(asmFile, "push %d\n", *(char*)branch->token->value);
		return false;
	}
	if (branch->token->type == TOKEN_VAR)
	{
		if (getVariableByScope(varList, (char*)(branch->token->value), currentScope)->Type == VAR_CHAR || getVariableByScope(varList, (char*)(branch->token->value), currentScope)->Type == VAR_BOOL)
		{
			fprintf(asmFile, "xor eax, eax\n");
			fprintf(asmFile, "mov al, byte ptr [ebp - %d]\n", getVariableByScope(varList, (char*)(branch->token->value), currentScope)->placeInMemory);
			fprintf(asmFile, "push eax\n");
		}
		else
		{
			fprintf(asmFile, "push [ebp - %d]\n", getVariableByScope(varList, (char*)(branch->token->value), currentScope)->placeInMemory);// getting the stack position of this specific var from the var list
		}

		if (getVariableByScope(varList, (char*)(branch->token->value), currentScope)->Type == VAR_FLOAT)
		{
			return true;
		}

		return false;
	}
	if (branch->token->type == TOKEN_INPUT_INT)
	{
		fprintf(asmFile, "call readInt\n");
		fprintf(asmFile, "push eax\n");
		return false;
	}
	if (branch->token->type == TOKEN_INPUT_FLOAT)
	{
		fprintf(asmFile, "call readFloat\n");
		fprintf(asmFile, "push 0\n");
		fprintf(asmFile, "fstp dword ptr [esp]\n");
		return true;
	}
	if (branch->token->type == TOKEN_INPUT_CHAR)
	{
		fprintf(asmFile, "xor eax, eax\n");
		fprintf(asmFile, "call get_char_func\n");
		fprintf(asmFile, "push eax\n");
		return false;
	}

	// token is an operator:

	bool isEAXdecimal = writeNumericBranch(branch->children[0], asmFile, varList);
	bool isEBXdecimal = writeNumericBranch(branch->children[1], asmFile, varList);

	fprintf(asmFile, "pop ebx\n"); // put into ebx the solution for the right side if the tree
	fprintf(asmFile, "pop eax\n"); // put into eax the solution for the left side if the tree

	writeNumericInstruction(branch->token, asmFile, isEAXdecimal, isEBXdecimal); // write the instruction

	return true;
}

int isInputToken(Token token)
{
	return token.type == TOKEN_INPUT_INT ||
		token.type == TOKEN_INPUT_FLOAT ||
		token.type == TOKEN_INPUT_CHAR;
}

/*
writeNumericInstruction: this function will get the operand and value of a numeric type, and write the correct instruction
input: the tokens of the operand and value, and the asm file
output: non
*/
void writeNumericInstruction(Token* operand, FILE* asmFile, bool isEAXdecimal, bool isEBXdecimal)
{

	fprintf(asmFile, "push eax\n");
	if (isEAXdecimal)
	{
		fprintf(asmFile, "fld dword ptr[esp]\n");
	}
	else
	{
		fprintf(asmFile, "fild dword ptr[esp]\n");
	}
	fprintf(asmFile, "mov dword ptr [esp], ebx\n");
	if (isEBXdecimal)
	{
		fprintf(asmFile, "fld dword ptr[esp]\n");
	}
	else
	{
		fprintf(asmFile, "fild dword ptr[esp]\n");
	}

	if (operand->type == TOKEN_ADD)
	{
		fprintf(asmFile, "fadd\n"); // Floating-point addition using FPU stack
	}
	else if (operand->type == TOKEN_SUB)
	{
		fprintf(asmFile, "fsub\n"); // Floating-point subtraction using FPU stack
	}
	else if (operand->type == TOKEN_MUL)
	{
		fprintf(asmFile, "fmul\n"); // Floating-point multiplication using FPU stack
	}
	else if (operand->type == TOKEN_DIV)
	{
		fprintf(asmFile, "fdiv\n"); // Floating-point division using FPU stack
	}
	else if (operand->type == TOKEN_MODULO)
	{
		fprintf(asmFile, "fprem\n"); // Floating-point remainder using FPU stack
	}


	// extract result to eax
	fprintf(asmFile, "fstp dword ptr[esp]\n");

}


/*
writeFunctionBranch: this function will write the branches of functions
input: the branch and the asm file
output:non
*/
void writeFunctionBranch(ASTNode* branch, FILE* asmFile, VariableList* varList)
{
	if (branch->token->type == TOKEN_PRINT_INT)// checking for print (in the futer there will be )
	{
		writeBranch(branch->children[0], asmFile, varList);
		if (isLastValFloat)
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}
		fprintf(asmFile, "call print_number_signed\n");
	}
	else if (branch->token->type == TOKEN_PRINT_CHAR)
	{
		writeBranch(branch->children[0], asmFile, varList);
		if (isLastValFloat)
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}
		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "call WriteChar\n");
	}
	else if (branch->token->type == TOKEN_PRINT_FLOAT)
	{
		writeBranch(branch->children[0], asmFile, varList);
		if (!isLastValFloat)
		{
			fprintf(asmFile, "fild DWORD PTR [esp]\n");
		}
		else
		{
			fprintf(asmFile, "fld DWORD PTR [esp]\n");
		}
		// write branch's result is in eax already
		fprintf(asmFile, "call WriteFloat\n");
		fprintf(asmFile, "fstp dword ptr [esp]\n");
		fprintf(asmFile, "pop eax\n");

	}
	return;
}







/*
getIEEE754: this function will get the ieee754 value of a float
input: the float
output: the ieee754 value
*/
int getIEEE754(float val)
{
	int result = 0;
	memcpy(&result, &val, sizeof(float));//copying bits
	return result;
}


