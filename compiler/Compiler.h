
#ifndef COMPILER_H
#define COMPILER_H
#include <stdio.h>
#endif
#include <string.h>

#ifndef TOKENGETTER_H
#include "TokenGetter.h"
#endif

#ifndef LOGMANAGER_H	
#include "logManager.h"
#endif

#ifndef WIN_API
#include <Windows.h>
#endif
#include <stdbool.h>

#define LEXER_OUTPUT_FILE_NAME "output.tok"
#define ERROR_LOG_FILE "errors.log"

/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName);

/* activate lexer on input code */
bool lex(char* file);

/* writing lex errors into log */
void writeLexErrorsIntoLog(int fileSize);

/* a helper function for getting the size of a file */
long fileSize(const char* filename);

/* extract tokens from lexer result */
llist* extractTokensFromLexResult(char* fileName);

/* open input file and return handler */
FILE* openFile(char* inputFileName);
