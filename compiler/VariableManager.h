#pragma once

#ifndef TOKENGETTER_H
#include "TokenGetter.h"
#endif


#ifndef VARIABLE_MANAGER_H
#define VARIABLE_MANAGER_H
#include "llist.h"
#include "ScopeTree.h"

#include <stdbool.h>
#include "FunctionList.h"
enum VarTypes {VAR_INT, VAR_STRING, VAR_BOOL, VAR_CHAR, VAR_FLOAT, VAR_DOUBLE , VAR_ERROR = -1}; // types of variables


struct Variable
{
	char* Id; // identifier
	enum VarTypes Type;
	int size; // size in bytes
	int scope;
	int placeInMemory; 
} typedef Variable;

struct VariableList
{
	Variable* var;
	struct VariableList* next;
} typedef VariableList;


void deleteVariableList(VariableList* varList); // deletes allocated memory for the list

int getSizeByType(enum VarTypes type); // returns the size of the type in bytes
void createNewVariable(char* identifier, enum VarTypes type, VariableList** varList, int varScope, bool isParameter, int parSize);
int isVariableExistInScope(VariableList* varList, char* identifier, int varScope);
int getVariableScope(VariableList* varList, char* identifier);
bool callIsVariablExist(VariableList* varList, char* identifier, int currentScope);
Variable* getVariable(VariableList* varList, char* identifier);
void appendVariableList(VariableList** list1, VariableList* list2);
Variable* getVariableByScope(VariableList* varList, char* identifier, int scope);

int getSizeOfScope(VariableList* list, int scope);
void printVariable(Variable* var);
void printVariableList(VariableList* varList);
void callDeleteScopeTree();

VariableList* createVariableListFromToken(llist* tokenList);
int createVariableListFromScope(llist* tokenList, int currentScope, ScopeTreeNode* currentScopeNode);
bool isVars(llist* tokenList);
FuncNode* createFunctionList(llist* tokenList);
void callDeleteFuncList();
int isParamNumValid(struct node* curr, int paramNum);
bool isFunctionsInTheCode(llist* tokenList);
// creates a variable list from a token list and run simple checks on the variable declarations









#endif


