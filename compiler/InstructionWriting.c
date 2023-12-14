
#ifndef INSTRUCTIONWRITING_H
#include "InstructionWriting.h"
#endif
#include <stdio.h>



#ifndef FILEHELPER_H
#include "fileHelper.h"
#endif



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
	if(tree->token == NULL)
	{
		currentToken = tree->children[EXPRESSION]->token;// getting the command part of this node
		next = tree->children[NEXT];
		tree = tree->children[EXPRESSION];
	}
	else
	{
		currentToken = tree->token;// getting the command part of this node
	}
	

	if (currentToken->type == TOKEN_NUM  ||
		currentToken->type == TOKEN_VAR ||
		currentToken->type == TOKEN_ADD ||
		currentToken->type == TOKEN_SUB ||
		currentToken->type == TOKEN_MUL ||
		currentToken->type == TOKEN_DIV ||
		currentToken->type == TOKEN_MODULO ||
		currentToken->type == TOKEN_LETTER)// checking for numeric branch
	{
		writeNumericBranch(tree, asmFile, varList);
		fprintf(asmFile, "pop eax\n");
	}
	else if (currentToken->type == TOKEN_PRINT_INT ||
			currentToken->type == TOKEN_PRINT_CHAR)// checking for function branch
	{
		writeFunctionBranch(tree, asmFile, varList);
	}
	else if (currentToken->type == TOKEN_INT ||
			currentToken->type == TOKEN_CHAR ||
			currentToken->type == TOKEN_FLOAT)// checking for decleration branch
	{
		writeDeclerationBranch(tree, asmFile, varList);
	}
	else if (currentToken->type == TOKEN_ASSIGN)
	{
		writeAssignBranch(tree, asmFile, varList);
	}

	if(next != NULL)
	{
		writeBranch(next, asmFile, varList);
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
	if(getVariable(varList, (char*)(branch->children[0]->token->value))->Type == VAR_CHAR)
	{
		fprintf(asmFile, "mov byte ptr [ebp - %d], al\n", getVariable(varList, (char*)(branch->children[0]->token->value))->placeInMemory);
	}
	else if (getVariable(varList, (char*)(branch->children[0]->token->value))->Type == VAR_INT)
	{
		fprintf(asmFile, "mov [ebp - %d], eax\n", getVariable(varList, (char*)(branch->children[0]->token->value))->placeInMemory);
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
			fprintf(asmFile, "push eax\n");
		}
		else
		{
			fprintf(asmFile, "push 0\n");
		}
	}
	else if (branch->token->type == TOKEN_CHAR)
	{

		fprintf(asmFile, "sub esp, 1\n");

		if (branch->children[1] != NULL)
		{
			writeBranch(branch->children[1], asmFile, varList);
			fprintf(asmFile, "mov byte ptr [ebp - %d], al\n", getVariable(varList, (char*)(branch->children[0]->token->value))->placeInMemory);
		}
	}

}

/*
writeNumericBranch: this function will get a numeric branch and write it into the asm file
input: the branch and the asm file
output: non
*/
void writeNumericBranch(ASTNode* branch, FILE* asmFile, VariableList* varList)
{
	if (branch->token->type == TOKEN_NUM)
	{
		fprintf(asmFile, "push %d\n", *(int*)branch->token->value);
		return;
	}
	if (branch->token->type == TOKEN_DECIMAL)
	{
		fprintf(asmFile, "push %d\n", getIEEE754(*(float*)branch->token->value));
		return;
	}
	if (branch->token->type == TOKEN_LETTER)
	{
		fprintf(asmFile, "push %d\n", *(char*)branch->token->value);
		return;
	}
	if (branch->token->type == TOKEN_VAR)
	{
		if (getVariable(varList, (char*)(branch->token->value))->Type == TOKEN_CHAR)
		{
			fprintf(asmFile, "xor eax, eax\n");
			fprintf(asmFile, "mov al, byte ptr [ebp - %d]\n", getVariable(varList, (char*)(branch->token->value))->placeInMemory);
			fprintf(asmFile, "push eax\n");
		}
		else
		{
			fprintf(asmFile, "push [ebp - %d]\n", getVariable(varList, (char*)(branch->token->value))->placeInMemory);// getting the stack position of this specific var from the var list
		}
		return;
	}

	// token is an operator:

	writeNumericBranch(branch->children[0], asmFile, varList);
	writeNumericBranch(branch->children[1], asmFile, varList);

	fprintf(asmFile, "pop ebx\n"); // put into ebx the solution for the right side if the tree
	fprintf(asmFile, "pop eax\n"); // put into eax the solution for the left side if the tree

	writeNumericInstruction(branch->token, asmFile); // write the instruction

	// push the final solution to the stack
	fprintf(asmFile, "push eax\n");

}



/*
writeNumericInstruction: this function will get the operand and value of a numeric type, and write the correct instruction
input: the tokens of the operand and value, and the asm file
output: non
*/
void writeNumericInstruction(Token* operand, FILE* asmFile)
{
	if (operand->type == TOKEN_ADD)//checking for the correct operand, and preforming it on eax
	{
		fprintf(asmFile, "add eax, ebx\n");
	}
	else if (operand->type == TOKEN_SUB)
	{
		fprintf(asmFile, "sub eax, ebx\n");
	}
	else if (operand->type == TOKEN_MUL)
	{
		fprintf(asmFile, "cdq\nimul eax, ebx\n");
	}
	else if (operand->type == TOKEN_DIV)//using ebx seince idiv cannot use immidiates
	{
		fprintf(asmFile, "cdq\nidiv ebx\n");
	}
	else if (operand->type == TOKEN_MODULO)//using ebx seince idiv cannot use immidiates
	{
		fprintf(asmFile, "xor edx, edx\ncdq\nidiv ebx\nmov eax, edx\n");
	}
	return;
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
		fprintf(asmFile, "push eax\n");
		fprintf(asmFile, "call print_number_signed\n");
	}
	else if (branch->token->type == TOKEN_PRINT_CHAR)
	{
		writeBranch(branch->children[0], asmFile, varList);
		// write branch's result is in eax already
		// and WriteChar works with al
		fprintf(asmFile, "call WriteChar\n");
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


