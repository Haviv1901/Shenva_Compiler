
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
	FILE* asmFile = openFile(fileName, "w");
	copyBoneFile(asmFile, FIRST); // copy first half of the basic functions and start of main

	writeInstructions(tree, asmFile); // write instructions from the ast
	copyBoneFile(asmFile, SECOND); // copy the second half
	fclose(asmFile);
}

void writeInstructions(ASTNode* tree, FILE* asmFile)
{
	if (tree == NULL)
	{
		return;
	}
	Token* currentToken = tree->token;
	switch (currentToken->type)
	{
	case MUL:
	case DIV:
	case SUB:
	case ADD:
		writeNumericBranch(tree, asmFile);
		break;
	case PRINT:
		writeNumericBranch(tree, asmFile);
		break;
	default:
		break;
	}
}

void writeNumericBranch(ASTNode * branch, FILE * asmFile)
{
	
}
void writeFunctionBranch(ASTNode* branch, FILE* asmFile);