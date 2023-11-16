

#ifndef COMPILER_H
#define COMPILER_H
#include <stdbool.h>
#endif

#ifndef TOKENGETTER_H
#include "TokenGetter.h"
#endif






/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName);

/* activate lexer on input code */
int activateLexer(char* inputFileName);



/* extract tokens from lexer result */
llist* extractTokensFromLexResult(char* fileName);

