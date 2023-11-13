#include "Compiler.h"

#include <string.h>

#ifndef TOKENGETTER_H
#include "TokenGetter.h"
#endif

#ifndef LOGMANAGER_H	
#include "logManager.h"
#endif


void tokenPrint(void* data);

/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName)
{
	FILE* logFile = logOpen(); // open log file


	FILE* file = openInputFile(inputFileName, logFile);

	llist* tokenList = extractToken(file, logFile);
	fclose(file);


	llist_print(tokenList, tokenPrint);
	llist_free(tokenList);
}


FILE* openInputFile(char* inputFileName, FILE* logFile)
{
	FILE* res = fopen(inputFileName, "r");
	char message[MAX_LOG_MESSAGE_SIZE];

	if (res == NULL)
	{
		strcat(message, STRING_OPEN_INPUT_FILE_FAILED);
	}
	else
	{
		strcat(message, STRING_OPEN_INPUT_FILE_SUCCESSFULLY);
	}
	strcat(message, inputFileName);
	logWrite(logFile, message);

	return res;
}


/* helper function to print tokens */
void tokenPrint(void* data)
{
	Token* token = (Token*)data;
	printToken(token);
}