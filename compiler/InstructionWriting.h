#pragma once

#ifndef INSTRUCTIONWRITING_H
#define INSTRUCTIONWRITING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "VariableManager.h"

#define FIRST_BONE_FILE "boneFile1.asm"
#define SECOND_BONE_FILE "boneFile2.asm"

#define FIRST false
#define SECOND true

static unsigned long lableNum = 0;

void copyBoneFile(FILE* asmFile, bool boneFileNumber);
void convertASTToASM(ASTNode* tree, const char* fileName, VariableList* varList);

void writeBranch(ASTNode* tree, FILE* asmFile, VariableList* varList);
int writeNumericBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
void writeNumericInstruction(Token* operand, FILE* asmFile, bool isEAXdecimal, bool isEBXdecimal);
void writeFunctionBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
int isInputToken(Token token);
void writeDeclerationBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
void writeAssignBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
int getIEEE754(float val);
int writeLogicalBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
int writeBooleanBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
void writeJMPcondition(FILE* asmFile, enum TokenTypes type);


#endif