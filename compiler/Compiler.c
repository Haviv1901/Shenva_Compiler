#include "Compiler.h"

#include <stdbool.h>

FILE* logFile;

void tokenPrint(void* data);

/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName)
{
	logFile = logOpen(); // open log file

	lex(inputFileName);

	llist* tokenList = extractTokensFromLexResult(LEXER_OUTPUT_FILE_NAME, logFile);


	//llist_print(tokenList, tokenPrint);
	llist_free(tokenList);
	
	// TODO: build AST !!!



	logClose(logFile);
}

void lex(char* inputFileName)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// Set up the STARTUPINFO structure
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	char cmdLine[MAX_PATH] = "lexicalAndSyntaxAnalysis.exe ";
	strcat(cmdLine, inputFileName);
	strcat(cmdLine, " ");
	strcat(cmdLine, LEXER_OUTPUT_FILE_NAME);

	if(CreateProcessA(NULL,
		cmdLine,
		NULL,
		NULL,
		false,
		0,
		NULL,
		NULL,
		&si,
		&pi))
	{
		// Wait until child process exits.
		WaitForSingleObject(pi.hProcess, INFINITE);

		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		logWrite(logFile, "Successfully activated lexer\n");
	}
	else // did not open file
	{
		logWrite(logFile, "Could not start lexer\n");
	}

}


llist* extractTokensFromLexResult(char* fileName)
{
	FILE* tokenFile = openFile(fileName, logFile);
	return extractToken(tokenFile, logFile);
}

/* open input file and return handler */
FILE* openFile(char* inputFileName)
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