

#ifndef COMPILER_H
#define COMPILER_H
#include <stdbool.h>
#endif
struct node;
typedef struct node* llist;
#ifndef TOKENGETTER_H
#include "TokenGetter.h"
#endif
#include "AST.h"





/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName);

/* activate lexer on input code */
int activateLexer(char* inputFileName);



/* extract tokens from lexer result */
llist* extractTokensFromLexResult(char* fileName);

