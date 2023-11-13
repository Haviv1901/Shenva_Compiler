
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

#define LEXER_OUTPUT_FILE_NAME "output.tok"

/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName);

/* activate lexer on input code */
void lex(char* file);

/* extract tokens from lexer result */
llist* extractTokensFromLexResult(char* fileName, FILE* logFile);

/* open input file and return handler */
FILE* openFile(char* inputFileName, FILE* logFile);
