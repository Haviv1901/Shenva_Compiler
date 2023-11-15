#include "Compiler.h"


FILE* logFile;

void tokenPrint(void* data);

/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName)
{
	logFile = logOpen(); // open log file

	if (lex(inputFileName))
	{
		llist* tokenList = extractTokensFromLexResult(LEXER_OUTPUT_FILE_NAME);
		
		llist_print(tokenList, tokenPrint);
		llist_free(tokenList);
	}
	
	// TODO: build AST !!!



	logClose(logFile);
}

bool lex(char* inputFileName)
{
	int errorSize = 0;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	// Set up the STARTUPINFO structure
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	char* cmdLine = (char*)calloc(41 + strlen(inputFileName), 1);
	if (cmdLine == NULL)
	{
		logWrite(logFile, "error with path allocation\n");
		return false;
	}
	sprintf(cmdLine, "lexicalAndSyntaxAnalysis.exe %s %s", inputFileName, LEXER_OUTPUT_FILE_NAME);

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

		free(cmdLine);
		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		errorSize = fileSize(ERROR_LOG_FILE);
		if (errorSize == 0)
		{
			logWrite(logFile, "Successfully activated lexer\n");
			return true;
		}
		else if (errorSize > 0)
		{
			logWrite(logFile, "Syntax errors were found:\n");
			writeLexErrorsIntoLog(errorSize);
			return false;
		}
	}
	else // did not open file
	{
		free(cmdLine);
		logWrite(logFile, "Could not start lexer\n");
		return false;
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







/*
fileSize: a function to get the size of a file
input: the file name
output: the file size
*/
long fileSize(const char* filename) 
{
	FILE* file = fopen(filename, "r"); 

	if (file == NULL) {
		return -1; // Return -1 to indicate an error
	}
	fseek(file, 0, SEEK_END);
	long size = ftell(file);  

	fclose(file); 

	return size;
}




/*
writeLexErrorsIntoLog: this function will log the errors of the lex
input: non
output: non
*/
void writeLexErrorsIntoLog(int sizeOfFile)
{
	char* fileContent = NULL;
	FILE* errFile = fopen(ERROR_LOG_FILE, "r");
	if (errFile == NULL)
	{
		logWrite(logFile, "couldn't open error file\n");
		return;
	}
	fileContent = (char*)calloc(sizeOfFile + 1, 1);
	if (fileContent != NULL)
	{
		fread(fileContent, sizeof(char), sizeOfFile, errFile);
		logWrite(logFile, fileContent);
		free(fileContent);
	}
	fclose(errFile);





}




