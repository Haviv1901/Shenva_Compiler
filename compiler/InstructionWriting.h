#pragma once

#ifndef INSTRUCTIONWRITING_H
#define INSTRUCTIONWRITING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

#define FIRST_BONE_FILE "boneFile1.asm"
#define SECOND_BONE_FILE "boneFile2.asm"

#define FIRST false
#define SECOND true

void copyBoneFile(FILE* asmFile, bool boneFileNumber);
void convertASTToASM(ASTNode* tree, const char* fileName);

void writeBranch(ASTNode* tree, FILE* asmFile);
void writeNumericBranch(ASTNode* branch, FILE* asmFile);
void writeNumericInstruction(Token* operand, FILE* asmFile);
void writeFunctionBranch(ASTNode* branch, FILE* asmFile);


#endif