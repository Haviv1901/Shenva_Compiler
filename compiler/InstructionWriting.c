
#ifndef INSTRUCTIONWRITING_H
#include "InstructionWriting.h"
#endif
#include <stdio.h>


#include "fileHelper.h"
bool isLastValFloat = false, isInFunc = false, isAssignToAdress = false;
unsigned long lableNum = 0;
int currentScope = 0;
int ScopeCounter = 0;
int funcEndLabel = 0;

/// <summary>
/// function to copy the functions and the assembly code bone to the assembly file
/// </summary>
/// <param name="asmFile"> asmFile file to copy to </param>
/// <param name="boneFileNumber"> false for first bone file, true for second bone file </param>
void copyBoneFile(FILE* asmFile, bool boneFileNumber)
{
	FILE* boneFile = openFile(boneFileNumber ? SECOND_BONE_FILE : FIRST_BONE_FILE, "r");
	// Open FIRST_BONE_FILE for reading

	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), boneFile) != NULL)
	{
		fputs(buffer, asmFile);
	}

	fclose(boneFile);
}


// function will open the main in the asm file.
void writeMain(char* asmFile)
{
	fprintf(asmFile, "main:\n"
	"push ebp\n"
    "mov ebp, esp\n"
    "mov esi, ebp\n"
    "finit\n"
    "sub esp, 2\n"
    "fstcw word ptr[esp]\n"
    "mov ax, [esp]\n"
    "and ax, 0FCFFh\n"
    "or ax, 00C00h\n"
    "mov[esp], ax\n"
    "fldcw word ptr[esp]\n"
    "add esp, 2\n");
}


void startWriting(ASTNode* tree, const char* fileName, VariableList* varList, FILE* asmFile)
{
	int mainEndLabel = 0;

	// copy first half of the basic functions and start of main
	copyBoneFile(asmFile, FIRST); 
	mainEndLabel = lableNum;
	lableNum++;

	// write fuinctions
	writeDefs(tree, asmFile, varList);
	// open main function
	writeMain(asmFile);
	funcEndLabel = mainEndLabel;
	// write instructions from the ast
	writeBranch(tree, asmFile, varList);
	fprintf(asmFile, "label_%d:\n", mainEndLabel);
	// close the main function and the asm program
	copyBoneFile(asmFile, SECOND); 
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
	free(asmPath);

	startWriting(tree, fileName, varList, asmFile);

	
	fclose(asmFile);
}



/*
writeDefs: this function will write the functions
input: the tree, the asmFile, and the var list
output: non
*/
void writeDefs(ASTNode* tree, FILE* asmFile, VariableList* varList)
{
	ASTNode* curr = tree, *def;
	FuncNode* func = NULL;
	while (curr != NULL)// going through the tree
	{
		if (curr->children[EXPRESSION]->token->type == TOKEN_DEF)//if a function is found
		{
			def = curr->children[EXPRESSION];
			func = callGetFunction(def->children[FUNC_ID]->token->value);//getting the function
			
			funcEndLabel = lableNum;
			lableNum++;//picking lable

			fprintf(asmFile, "function_%d PROC\n", callGetFuncIndexByName(def->children[FUNC_ID]->token->value));
			fprintf(asmFile, "push ebp\n");
			fprintf(asmFile, "mov ebp, esp\n");

			isInFunc = true;//setting is func to true
			currentScope = func->scope;
			ScopeCounter = func->scope;

			writeBranch(curr->children[EXPRESSION]->children[CODE_BLOCK], asmFile, varList);//writing function body

			isInFunc = false;
			currentScope = 0;
			ScopeCounter = 0;//reseting scope current and counter

			fprintf(asmFile, "xor eax, eax\n");//writing a function end
			fprintf(asmFile, "label_%d:\n", funcEndLabel);
			fprintf(asmFile, "mov esp, ebp\n");
			fprintf(asmFile, "pop ebp\n");
			fprintf(asmFile, "retn %d\n", func->paramSize);		

			fprintf(asmFile, "function_%d ENDP\n", callGetFuncIndexByName(def->children[FUNC_ID]->token->value));
		}
		curr = curr->children[NEXT];
	}
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


	if (isExpressionToken(*currentToken) || isBooleanExpressionToken(currentToken->type) || currentToken->type == TOKEN_OR || currentToken->type == TOKEN_AND || currentToken->type == TOKEN_VAR) // checking for expression branch
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
		currentToken->type == TOKEN_FLOAT || currentToken->type == TOKEN_BOOL || currentToken->type == TOKEN_INT_POINTER
		|| currentToken->type == TOKEN_CHAR_POINTER || currentToken->type == TOKEN_FLOAT_POINTER ||
		currentToken->type == TOKEN_BOOL_POINTER)// checking for decleration branch
	{
		writeDeclerationBranch(tree, asmFile, varList);
	}
	else if (currentToken->type == TOKEN_ASSIGN)
	{
		writeAssignBranch(tree, asmFile, varList);
	}
	else if(currentToken->type == TOKEN_IF || currentToken->type == TOKEN_WHILE)
	{
		writeConditionBranch(tree, asmFile, varList);
	}
	else if (currentToken->type == TOKEN_DEF)
	{
		ScopeCounter += ScopeCountGetter(tree->children[CODE]);
	}
	else if (currentToken->type == TOKEN_RETURN)
	{
		if (tree->children[LEAF] != NULL)
		{
			isLastValFloat = writeLogicalBranch(tree->children[LEAF], asmFile, varList);
			if (!isLastValFloat)
			{
				fprintf(asmFile, "fild dword ptr [esp]\n");
				fprintf(asmFile, "fstp dword ptr [esp]\n");
				fprintf(asmFile, "pop eax\n");
			}
		}
		else
		{
			fprintf(asmFile, "mov eax, 0\n");
		}
		fprintf(asmFile, "jmp label_%d\n", funcEndLabel);
	}
	if (next != NULL)
	{
		writeBranch(next, asmFile, varList);
	}

}


/*
writeconditionBranch: this function will handle conditions and scope managment
input: the branch the asm file, and the var list
output: non
*/
void writeConditionBranch(ASTNode* branch, FILE* asmFile, VariableList* varList)
{
	int labelHolder = 0;
    if (branch->token->type == TOKEN_IF)
	{
		labelHolder = lableNum;
		lableNum++;
		writeIfBranch(branch, asmFile, varList, labelHolder);
		fprintf(asmFile, "label_%d:\n", labelHolder);
	}
	else if (branch->token->type == TOKEN_WHILE)
	{
		writeLoopBranch(branch, asmFile, varList);
	}
}




void writeLoopBranch(ASTNode* branch, FILE* asmFile, VariableList* varList)
{
	int labelHolder = lableNum, scopeHolder = currentScope, endlabel = 0, scopeSize;
	lableNum++;
	endlabel = lableNum;
	lableNum++;
	fprintf(asmFile, "label_%d:\n", labelHolder);
	writeBranch(branch->children[CONDITION], asmFile, varList);//writing condition

	fprintf(asmFile, "pop eax\n");
	fprintf(asmFile, "cmp eax, 0\n");
	fprintf(asmFile, "je label_%d\n", endlabel);//going to next if
	ScopeCounter++;
	currentScope = ScopeCounter;//going into scope

	writeBranch(branch->children[CODE], asmFile, varList);//writing the block
	currentScope = scopeHolder;//retreiving scope

	scopeSize = getSizeOfScope(varList, currentScope + 1);//deleteing scope
	if (scopeSize != 0)
	{
		fprintf(asmFile, "add esp, %d\n", scopeSize);
	}
	fprintf(asmFile, "jmp label_%d\n", labelHolder);//ending label, and opening next
	fprintf(asmFile, "label_%d:\n", endlabel);
}



/*
writeIfBranch: this fucntion will write a condition bracnch
input: the branch, asm file, vairable list and the label to the end of the block
output: non
*/
void writeIfBranch(ASTNode* branch, FILE* asmFile, VariableList* varList, int endLabel)
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
			writeConditionBranch(elseBranch->children[0], asmFile, varList);
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
	if (branch->children[0]->token->type != TOKEN_VAR)
	{
		if (isLastValFloat)
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}
		isAssignToAdress = true;
		writeBranch(branch->children[0], asmFile, varList);
		isAssignToAdress = false;
		if (isLastValFloat)
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}
		fprintf(asmFile, "pop ebx\n");
		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "xchg ebx, esp\n");
		if (isDereferencedPTRpointsToBoolOrChar(branch, varList))
		{
			fprintf(asmFile, "mov byte ptr [esp], al\n");
		}
		else
		{
			fprintf(asmFile, "mov dword ptr [esp], eax\n");
		}
		fprintf(asmFile, "xchg ebx, esp\n");
		return;
	}

	if (getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->Type == VAR_CHAR || getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->Type == VAR_BOOL)
	{
		if (isLastValFloat)
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}
		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "mov byte ptr [ebp - %d], al\n", getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->placeInMemory);
		
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
	else// must be int or pointer
	{
		if (isLastValFloat)
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}
		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "mov [ebp - %d], eax\n", getVariableByScope(varList, (char*)(branch->children[0]->token->value), currentScope)->placeInMemory);
	}

}

/*
writeArrayInitWithSize: this function will init an array with 0 by size
input: the size and the decleration type token and also the asm file
output: non
*/
void writeArrayInitWithSize(int size, Token* decTok, FILE* asmFile)
{
	if (decTok->type == TOKEN_INT_POINTER || decTok->type == TOKEN_FLOAT_POINTER)
	{
		for (int i = 0; i < size; i++)
		{
			fprintf(asmFile, "push 0\n");
		}
	}
	else
	{
		while (size >= 4)
		{
			fprintf(asmFile, "push 0\n");
			size -= 4;
		}

		while (size > 0)
		{
			fprintf(asmFile, "sub esp, 1\n");
			fprintf(asmFile, "mov byte ptr [esp], 0\n");
			size--;
		}
	}
	fprintf(asmFile, "push esp\n");
}

/*
writeDeclerationBranch: this function will write a decleration branch into the asm file
input: the decleration branch, and the asm file
output: non
*/
void writeDeclerationBranch(ASTNode* branch, FILE* asmFile, VariableList* varList)
{
	if (branch->token->type == TOKEN_INT || branch->token->type == TOKEN_INT_POINTER || branch->token->type == TOKEN_FLOAT_POINTER || branch->token->type == TOKEN_CHAR_POINTER || branch->token->type == TOKEN_BOOL_POINTER)
	{
		if (branch->children[1] != NULL)
		{

			if (branch->children[1]->token->type == TOKEN_LIST_SIZE_DECLERATION)
			{
				writeArrayInitWithSize(*(int*)(branch->children[1]->children[0]->token->value), branch->token, asmFile);
			}
			else
			{
				writeBranch(branch->children[1], asmFile, varList);
				if (isLastValFloat)
				{
					fprintf(asmFile, "call ConvertFloatToInt\n");
				}
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
			fprintf(asmFile, "mov byte ptr [esp], al\n");
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
ScopeCountGetter: this function will get the number of scopes from a tree
input: the branch to collect scopes
output: all of the scopes including the current one
*/
int ScopeCountGetter(ASTNode* branch)
{
	int result = 1;
	ASTNode* curr = branch, *holder = NULL;
	while (curr)// while can still scan
	{
		if (curr->children[EXPRESSION]->token->type == TOKEN_IF)
		{
			result += ScopeCountGetter(curr->children[EXPRESSION]->children[CODE_BLOCK]);// getting scopes
			holder = curr->children[EXPRESSION]->children[ELSE];//checking for else
			while (holder)
			{
				if (holder->children[LEAF] != NULL && holder->children[LEAF]->token == NULL)//if a virgin else
				{
					result += ScopeCountGetter(holder->children[LEAF]);//get leaf
					holder = NULL;
				}
				else if (holder->children[LEAF] != NULL && holder->children[LEAF]->token->type == TOKEN_IF)// if else if
				{
					result += ScopeCountGetter(holder->children[LEAF]->children[CODE_BLOCK]);
					holder = holder->children[LEAF]->children[ELSE];//going to next else
				}
				else
				{
					result++;// empty else
					holder = NULL;
				}
			}
		}
		else if (curr->children[EXPRESSION]->token->type == TOKEN_WHILE)// getting scopes from while and defs
		{
			result += ScopeCountGetter(curr->children[EXPRESSION]->children[CODE_BLOCK]);
		}
		else if (curr->children[EXPRESSION]->token->type == TOKEN_DEF)
		{
			result += ScopeCountGetter(curr->children[EXPRESSION]->children[CODE_BLOCK]);
		}
		curr = curr->children[NEXT];

	}

	return result;
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
	Variable* var = NULL;
	VariableList* firstParam = NULL;
	int funcScope = 0;
	bool isGlobalVar = false;
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
		var = getVariableByScope(varList, (char*)(branch->token->value), currentScope);
		if (isInFunc == true && var->scope == 0)
		{
			fprintf(asmFile, "xchg ebp, esi\n");
			isGlobalVar = true;
		}
		if (var->Type == VAR_CHAR || var->Type == VAR_BOOL)
		{
			fprintf(asmFile, "xor eax, eax\n");
			fprintf(asmFile, "mov al, byte ptr [ebp - %d]\n", var->placeInMemory);
			fprintf(asmFile, "push eax\n");
		}
		else
		{
			fprintf(asmFile, "push [ebp - %d]\n", var->placeInMemory);// getting the stack position of this specific var from the var list
		}

		if (isGlobalVar)
		{
			fprintf(asmFile, "xchg ebp, esi\n");
			isGlobalVar = false;
		}

		if (var->Type == VAR_FLOAT)
		{
			return true;
		}

		return false;
	}
	if (branch->token->type == TOKEN_INPUT_INT)//inputs
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
	if (branch->token->type == TOKEN_FUNCTION_CALL)
	{
		funcScope = callGetFunction(branch->token->value)->scope;
		firstParam = getFuncFirstParameterNode(varList, funcScope);
		writeParams(branch->children[LEAF], firstParam, funcScope, asmFile, varList);
		fprintf(asmFile, "call function_%d\n", callGetFuncIndexByName(branch->token->value));
		fprintf(asmFile, "push eax\n");
		return true;
	}
	if (branch->token->type == TOKEN_REFERENCE)
	{
		if (branch->children[LEAF]->token->type == TOKEN_DEREFERENCE)
		{
			return writeNumericBranch(branch->children[LEAF]->children[LEAF], asmFile, varList);
		}

		fprintf(asmFile, "mov eax, ebp\n");
		fprintf(asmFile, "sub eax, %d\n", getVariableByScope(varList, (char*)(branch->children[LEAF]->token->value), currentScope)->placeInMemory);

		fprintf(asmFile, "push eax\n");
		return false;
	}
	if (branch->token->type == TOKEN_DEREFERENCE)
	{
		if (branch->children[LEAF]->token->type == TOKEN_REFERENCE)
		{
			return writeNumericBranch(branch->children[LEAF]->children[LEAF], asmFile, varList);
		}
		 
		if (branch->children[LEAF]->token->type == TOKEN_ADD)//index situation
		{
			if (getVariableByScope(varList, branch->children[LEAF]->children[LEAF]->token->value, currentScope)->Type == VAR_BOOL_POINTER || getVariableByScope(varList, branch->children[LEAF]->children[LEAF]->token->value, currentScope)->Type == VAR_CHAR_POINTER)
			{
				*(int*)(branch->children[LEAF]->children[ONE_CHILD_NODE]->children[LEAF]->token->value) = 1;
			}
		}

		if (isAssignToAdress == true)
		{
			isAssignToAdress = false;
			return writeNumericBranch(branch->children[LEAF], asmFile, varList);
		}


		if (writeNumericBranch(branch->children[LEAF], asmFile, varList))
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}

		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "xchg eax, esp\n");
		if (isDereferencedPTRpointsToBoolOrChar(branch, varList))
		{
			fprintf(asmFile, "xor ebx, ebx\n");
			fprintf(asmFile, "mov bl, byte ptr [esp]\n");
		}
		else
		{
			fprintf(asmFile, "mov ebx, dword ptr [esp]\n");
		}
		fprintf(asmFile, "xchg eax, esp\n");
		fprintf(asmFile, "push ebx\n");
		return isDereferencedPTRpointsToFloat(branch, varList);
	}

	// token is an operator:




	bool isEAXdecimal = writeNumericBranch(branch->children[0], asmFile, varList);
	bool isEBXdecimal = writeNumericBranch(branch->children[1], asmFile, varList);

	fprintf(asmFile, "pop ebx\n"); // put into ebx the solution for the right side if the tree
	fprintf(asmFile, "pop eax\n"); // put into eax the solution for the left side if the tree

	writeNumericInstruction(branch->token, asmFile, isEAXdecimal, isEBXdecimal); // write the instruction

	return true;
}




/*
isDereferencedPTRpointsToFloat: this function will return true if the bottom var in a dereference chain is a float ptr
input: the branch and varList
ouput: a bool
*/
bool isDereferencedPTRpointsToFloat(ASTNode* branch, VariableList* varList)
{
	while (branch->token->type != TOKEN_VAR)//going to the bottom var
	{
		branch = branch->children[LEAF];
	}
	return getVariableByScope(varList, (char*)(branch->token->value), currentScope)->Type == VAR_FLOAT_POINTER;
}


/*
isDereferencedPTRpointsToboolOrChar: this function will return true if the bottom var in a dereference chain is a bool or char ptr
input: the branch and varList
ouput: a bool
*/
bool isDereferencedPTRpointsToBoolOrChar(ASTNode* branch, VariableList* varList)
{
	while (branch->token->type != TOKEN_VAR)//going to the bottom var
	{
		branch = branch->children[LEAF];
	}
	return (getVariableByScope(varList, (char*)(branch->token->value), currentScope)->Type == VAR_BOOL_POINTER) || (getVariableByScope(varList, (char*)(branch->token->value), currentScope)->Type == VAR_CHAR_POINTER);
}




void writeParams(ASTNode* paramBranch, VariableList* paramPtr, int funcScope, FILE* asmFile, VariableList* varlist)
{
	if (paramPtr == NULL || paramPtr->var->scope != funcScope || paramPtr->var->placeInMemory >= 0)
	{
		return;
	}
	writeParams(paramBranch->children[NEXT], paramPtr->next, funcScope, asmFile, varlist);
	bool isParamFloat = writeLogicalBranch(paramBranch->children[EXPRESSION], asmFile, varlist);
	Variable* parameter = paramPtr->var;
	if (isParamFloat)
	{
		if (parameter->Type != VAR_FLOAT)
		{
			fprintf(asmFile, "call ConvertFloatToInt\n");
		}
	}
	else
	{
		if (parameter->Type == VAR_FLOAT)
		{
			fprintf(asmFile, "fild dword ptr [esp]\n");
			fprintf(asmFile, "fstp dword ptr [esp]\n");
		}
	}

	if (parameter->Type == VAR_BOOL || parameter->Type == VAR_CHAR)
	{
		fprintf(asmFile, "pop eax\n");
		fprintf(asmFile, "sub esp, 1\n");
		fprintf(asmFile, "mov byte ptr [esp], al\n");
	}
	return;
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
	if (operand->type == TOKEN_MODULO)
	{
		fprintf(asmFile, "fstp dword ptr[esp]\n");
		fprintf(asmFile, "sub esp, 4\n");
		fprintf(asmFile, "fstp dword ptr[esp]\n");
		fprintf(asmFile, "add esp, 4\n");
	}
	else
	{
		fprintf(asmFile, "fstp dword ptr[esp]\n");
	}
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


