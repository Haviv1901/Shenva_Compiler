
#ifndef COMPILER_H
#define COMPILER_H
#include <stdio.h>
#endif



/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName);

/* open input file and return handler */
FILE* openInputFile(char* inputFileName, FILE* logFile);
