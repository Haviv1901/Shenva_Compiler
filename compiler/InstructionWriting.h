#pragma once
#ifndef INSTRUCTIONWRITING_H
#define INSTRUCTIONWRITING_H
#include <stdio.h>
#include "AST.h"
FILE* makeASMBoneFile(const char* fileName);
void writeInstructions(ASTNode* tree);
void writeNumericBranch(ASTNode* branch);
void writeFunctionBranch(ASTNode* branch);


#endif