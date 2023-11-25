
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
void convertASTToASM(ASTNode* tree, const char* fileName)
{
	char* asmPath = NULL;
	asmPath = (char*)calloc(strlen(fileName) + 5, sizeof(char));

	strcpy(asmPath, fileName);
	strcat(asmPath, ".asm");
	FILE* asmFile = openFile(asmPath, "w");

	copyBoneFile(asmFile, FIRST); // copy first half of the basic functions and start of main

	writeBranch(tree, asmFile); // write instructions from the ast

	copyBoneFile(asmFile, SECOND); // copy the second half
	free(asmPath);
	fclose(asmFile);
}




/*
writeBranch: this function will write all instructions to the asm file after the first bone was added
input: the tree, and the asm file
output: non
*/
void writeBranch(ASTNode* tree, FILE* asmFile)
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
	

	if (currentToken->type == NUM || currentToken->type == ADD || currentToken->type == SUB || currentToken->type == MUL || currentToken->type == DIV)// checking for numeric branch
	{
		writeNumericBranch(tree, asmFile);
		fprintf(asmFile, "pop eax\n");
	}
	else if (currentToken->type == PRINT)// checking for function branch
	{
		writeFunctionBranch(tree, asmFile);
	}

	if(next != NULL)
	{
		writeBranch(next, asmFile);
	}
	
}



/*
writeNumericBranch: this function will get a numeric branch and write it into the asm file
input: the branch and the asm file
output: non
*/
void writeNumericBranch(ASTNode * branch, FILE * asmFile)
{
	if(branch->token->type == NUM)
	{
		fprintf(asmFile, "push %d\n", *(int*)branch->token->value);
		return;
	}

	// token is an operator:

	writeNumericBranch(branch->children[0], asmFile);
	writeNumericBranch(branch->children[1], asmFile);

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
	if (operand->type == ADD)//checking for the correct operand, and preforming it on eax
	{
		fprintf(asmFile, "add eax, ebx\n");
	}
	else if (operand->type == SUB)
	{
		fprintf(asmFile, "sub eax, ebx\n");
	}
	else if (operand->type == MUL)
	{
		fprintf(asmFile, "cdq\nimul eax, ebx\n");
	}
	else if (operand->type == DIV)//using ebx seince idiv cannot use immidiates
	{
		fprintf(asmFile, "cdq\nidiv ebx\n");
	}
	return;
}

//
///*
//writeNumericInstruction: this function will get the operand and value of a numeric type, and write the correct instruction
//input: the tokens of the operand and value, and the asm file
//output: non
//*/
//void writeNumericInstruction(Token* operand, Token* value, FILE* asmFile)
//{
//	if (operand->type == ADD)//checking for the correct operand, and preforming it on eax
//	{
//		fprintf(asmFile, "add eax, %d\n", *(int*)value->value);
//	}
//	else if (operand->type == SUB)
//	{
//		fprintf(asmFile, "sub eax, %d\n", *(int*)value->value);
//	}
//	else if (operand->type == MUL)
//	{
//		fprintf(asmFile, "imul eax, %d\n", *(int*)value->value);
//	}
//	else if (operand->type == DIV)//using ebx sience idiv cannot use immidiates
//	{
//		fprintf(asmFile, "mov ebx, %d\nidiv ebx\n", *(int*)value->value);
//	}
//	return;
//}




/*
writeFunctionBranch: this function will write the branches of functions
input: the branch and the asm file
output:non
*/
void writeFunctionBranch(ASTNode* branch, FILE* asmFile)
{

	if (branch->token->type == PRINT)// checking for print (in the futer there will be )
	{
		writeNumericBranch(branch->children[0], asmFile);
		fprintf(asmFile, "call print_number_signed\n");
	}
	return;
}







