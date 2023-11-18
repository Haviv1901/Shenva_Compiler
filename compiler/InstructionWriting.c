
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
	if (asmPath == NULL)
	{
		printf("could not open file: %s\n", fileName);
		return;
	}
	strcpy(asmPath, fileName);
	strcat(asmPath, ".asm");
	FILE* asmFile = openFile(asmPath, "w");
	copyBoneFile(asmFile, FIRST); // copy first half of the basic functions and start of main

	writeInstructions(tree, asmFile); // write instructions from the ast
	copyBoneFile(asmFile, SECOND); // copy the second half
	free(asmPath);
	fclose(asmFile);
}




/*
writeInstructions: this function will write all instructions to the asm file after the first bone was added
input: the tree, and the asm file
output: non
*/
void writeInstructions(ASTNode* tree, FILE* asmFile)
{
	if (tree == NULL)// if the tree is null do nothing
	{
		return;
	}
	Token* currentToken = tree->children[1]->token;// getting the command part of this node
	if (currentToken->type == NUM || currentToken->type == ADD || currentToken->type == SUB || currentToken->type == MUL || currentToken->type == DIV)// checking for numeric branch
	{
		writeNumericBranch(tree->children[1], asmFile);
	}
	else if (currentToken->type == PRINT)// checking for function branch
	{
		writeFunctionBranch(tree->children[1], asmFile);
	}
	writeInstructions(tree->children[0], asmFile);
	return;
}



/*
writeNumericBranch: this function will get a numeric branch and write it into the asm file
input: the branch and the asm file
output: non
*/
void writeNumericBranch(ASTNode * branch, FILE * asmFile)
{
	if (branch->token->type == NUM)// checking if its an only number
	{
		fprintf(asmFile, "mov eax, %d\n", *(int*)branch->token->value);
		return;
	}
	if (branch->children[0]->token->type == NUM && branch->children[1]->token->type == NUM)//if its the deepest root
	{
		fprintf(asmFile, "mov eax, %d\n", *(int*)branch->children[0]->token->value);//writing the first put
		writeNumericInstruction(branch->token, branch->children[1]->token, asmFile);//writing instructions
	}
	else
	{
		writeNumericBranch(branch->children[1], asmFile);// going to the deepest root first
		writeNumericInstruction(branch->token, branch->children[0]->token, asmFile);//writing instruction

	}
	return;




}



/*
writeNumericInstruction: this function will get the operand and value of a numeric type, and write the correct instruction
input: the tokens of the operand and value, and the asm file
output: non
*/
void writeNumericInstruction(Token* operand, Token* value, FILE* asmFile)
{
	if (operand->type == ADD)//checking for the correct operand, and preforming it on eax
	{
		fprintf(asmFile, "add eax, %d\n", *(int*)value->value);
	}
	else if (operand->type == SUB)
	{
		fprintf(asmFile, "sub eax, %d\n", *(int*)value->value);
	}
	else if (operand->type == MUL)
	{
		fprintf(asmFile, "imul eax, %d\n", *(int*)value->value);
	}
	else if (operand->type == DIV)//using ebx sience idiv cannot use immidiates
	{
		fprintf(asmFile, "mov ebx, %d\nidiv ebx\n", *(int*)value->value);
	}
	return;
}




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
		fprintf(asmFile, "push eax\ncall print_number_signed\n");
	}
	return;
}








