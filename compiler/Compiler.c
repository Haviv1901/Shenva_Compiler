#include "Compiler.h"
#include <stdlib.h>
#include "fileHelper.h"
#include "flags.h"
#include "lexer.h"


void tokenPrint(void* data);


void printVariaballsWithScope(VariableList* curr)
{
	while (curr)
	{
		printf("%s: %d\n", curr->var->Id, curr->var->scope);
		curr = curr->next;
	}
}


/* main function, compile a txt file into a .exe file */
int Compile(char* inputFileName, char* outputFileName)
{
	if (userFlags.printLogs)
	{
		printf("Starting compilation...\n");
	}
	if (!activateLexer(inputFileName)) // lex inpput file
	{
		return 0;
	}

	llist* tokenList = extractTokensFromLexResult(LEXER_OUTPUT_FILE_NAME); // extract tokens to c memory
	llist hold = *tokenList;
	printTokenList(tokenList); // print tokens if needed
	

	VariableList* varList = createVariableList(tokenList);

	if(isVars(tokenList) && varList == NULL) // checking if there is any undefined variable error.
	{
		token_llist_free(tokenList);
		if (userFlags.keepTokensErrorFile != 1)
		{
			DeleteFile(ERROR_LOG_FILE);
		}
		if (userFlags.keepTokenFile != 1)
		{
			DeleteFile(LEXER_OUTPUT_FILE_NAME);
		}
		return 0;
	}

	printVariaballsList(varList);

	ASTNode* tree = buildTree(tokenList); // build AST 

	convertASTToASM(tree, outputFileName, varList); // convert AST to ASM code.
	runMasmAndLink(outputFileName);
	deleteAST(tree); // free alocated memory of AST
	*tokenList = hold;
	callDeleteScopeTree();
	token_llist_free(tokenList);
	deleteVariableList(varList);
	callDeleteFuncList();
	return 1;
}

void printVariaballsList(VariableList* varList)
{
	if(userFlags.printVariableList)
	{
		printf("\nVariables List:\n");
		printVariaballsWithScope(varList);
		printf("\n\n");
	}
}

void printTokenList(llist* tokenList)
{
	if(userFlags.printTokenList)
	{
		printf("\nToken List:\n");
		llist_print(tokenList, tokenPrint);
		printf("\n\n");
	}
}



VariableList* createVariableList(llist* tokenList)
{
	return createVariableListFromToken(tokenList);
}

/* lex a txt file into a token list */
int activateLexer(char* inputFileName)
{
	return lex(inputFileName);
}


llist* extractTokensFromLexResult(char* fileName)
{
	FILE* tokenFile = openFile(fileName, "r");
	return extractToken(tokenFile);
}




/* helper function to print tokens */
void tokenPrint(void* data)
{
	Token* token = (Token*)data;
	printToken(token);
}




/*
writeLexErrorsIntoLog: this function will log the errors of the lex
input: non
output: non
*/
void writeLexErrorsIntoLog(int sizeOfFile)
{
	char* fileContent = NULL;
	FILE* errFile = openFile(ERROR_LOG_FILE, "r");


	fileContent = (char*)calloc(sizeOfFile, sizeof(char));
	if (fileContent != NULL)
	{
		fread(fileContent, sizeof(char), sizeOfFile, errFile);
		printf("%s\n", fileContent);
		free(fileContent);
	}
	fclose(errFile);

}




