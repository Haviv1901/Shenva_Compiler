

#ifndef COMPILER_H
#define COMPILER_H
#endif

struct node;
typedef struct node* llist;

#ifndef TOKENGETTER_H
#include "TokenGetter.h"
#endif

#ifndef ASTMANAGER_H
#include "ASTManager.h"
#endif

#ifndef INSTRUCTIONWRITING_H
#include "InstructionWriting.h"
#endif

#ifndef MASMANDLINK_H
#include "masmAndLink.h"
#endif



/* main function, compile a txt file into a .exe file */
void Compile(char* inputFileName, char* outputFileName);

/* activate lexer on input code */
int activateLexer(char* inputFileName);

/* extract tokens from lexer result */
llist* extractTokensFromLexResult(char* fileName);

