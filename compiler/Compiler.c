#include "Compiler.h"
#include <stdlib.h>
#include "fileHelper.h"
#include "lexer.h"


void tokenPrint(void* data);


/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName)
{

	if (!activateLexer(inputFileName)) // lex inpput file
	{
		return;
	}

	llist* tokenList = extractTokensFromLexResult(LEXER_OUTPUT_FILE_NAME); // extract tokens to c memory
	llist hold = *tokenList;

	llist_print(tokenList, tokenPrint); // print for debugging
	VariableList* varList = createVariableList(tokenList);

	if(isVars(tokenList) && varList == NULL) // checking if there is any undefined variable error.
	{
		token_llist_free(tokenList);
		return;
	}

	

	//ASTNode* tree = buildTree(tokenList); // build AST 

	//convertASTToASM(tree, outputFileName, varList); // convert AST to ASM code.
	//runMasmAndLink(outputFileName);
	//deleteAST(tree); // free alocated memory of AST
	*tokenList = hold;

	token_llist_free(tokenList);
	deleteVariableList(varList);


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




