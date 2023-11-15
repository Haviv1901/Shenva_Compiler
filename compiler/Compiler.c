#include "Compiler.h"

#include "fileHelper.h"
#include "llist.h"
#include "lexer.h"


void tokenPrint(void* data);

/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName)
{

	if (activateLexer(inputFileName))
	{
		llist* tokenList = extractTokensFromLexResult(LEXER_OUTPUT_FILE_NAME);
		
		llist_print(tokenList, tokenPrint);
		llist_free(tokenList);
	}
	
	// TODO: build AST !!!


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


	fileContent = (char*)calloc(sizeOfFile + 1, 1);
	if (fileContent != NULL)
	{
		fread(fileContent, sizeof(char), sizeOfFile, errFile);
		printf(fileContent);
		free(fileContent);
	}
	fclose(errFile);

}




