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


void copyBoneFile(FILE* asmFile, bool boneFileNumber);
void convertASTToASM(ASTNode* tree, const char* fileName, VariableList* varList);
void writeIncludes(FILE* asmFile);
void writeBranch(ASTNode* tree, FILE* asmFile, VariableList* varList);
int writeNumericBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
void writeArrayInitWithSize(int size, Token* decTok, FILE* asmFile);
void writeArrayInitWithVals(ASTNode* branch, Token* decTok, FILE* asmFile, VariableList* varList);
void writeNumericInstruction(Token* operand, FILE* asmFile, bool isEAXdecimal, bool isEBXdecimal);
void writeFunctionBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
int isInputToken(Token token);
void writeDeclerationBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
void writeAssignBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
int getIEEE754(float val);
int writeLogicalBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
int writeBooleanBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
void writeJMPcondition(FILE* asmFile, enum TokenTypes type);
void writeIfBranch(ASTNode* branch, FILE* asmFile, VariableList* varList, int endLabel);
void writeLoopBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
void writeConditionBranch(ASTNode* branch, FILE* asmFile, VariableList* varList);
void writeDefs(ASTNode* tree, FILE* asmFile, VariableList* varList);
int ScopeCountGetter(ASTNode* branch);
void writeParams(ASTNode* paramBranch, VariableList* paramPtr, int funcScope, FILE* asmFile, VariableList* varlist);
void startWriting(ASTNode* tree, VariableList* varList, FILE* asmFile);
void writeMain(char* asmFile);

bool isDereferencedPTRpointsToFloat(ASTNode* branch, VariableList* varList);
bool isDereferencedPTRpointsToBoolOrChar(ASTNode* branch, VariableList* varList);




#endif