#pragma once

#ifndef TOKENGETTER_H
#include "TokenGetter.h"
#endif


#ifndef VARIABLE_MANAGER_H
#define VARIABLE_MANAGER_H
#include "llist.h"

#include <stdbool.h>
enum VarTypes {TYPE_INT = 'i', TYPE_STRING, TYPE_BOOL, TYPE_CHAR, TYPE_FLOLAT, TYPE_DOUBLE }; // types of variables


struct Variable
{
	char* Id; // identifier
	enum VarTypes Type;
	int size; // size in bytes
	int placeInMemory; 
} typedef Variable;

struct VariableList
{
	Variable* var;
	struct VariableList* next;
} typedef VariableList;

static int reformattedStackPointer = 0; // new stack pointer that works with variables in size of less then 4 bytes

void deleteVariableList(VariableList* varList); // deletes allocated memory for the list

int getSizeByType(enum VarTypes type); // returns the size of the type in bytes
void createNewVariable(char* identifier, enum VarTypes type, VariableList** list);
int isVariableExist(VariableList* varList, char* identifier);
Variable* getVariable(VariableList* varList, char* identifier);

void printVariable(Variable* var);
void printVariableList(VariableList* varList);

VariableList* createVariableListFromToken(llist* tokenList);
bool isVars(llist* tokenList);
// creates a variable list from a token list and run simple checks on the variable declarations









#endif


