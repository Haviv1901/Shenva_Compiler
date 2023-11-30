#pragma once

#ifndef TOKENGETTER_H
#include "TokenGetter.h"
#endif


#ifndef VARIABLE_MANAGER_H
#define VARIABLE_MANAGER_H

enum VarTypes {TYPE_INT, TYPE_STRING, TYPE_BOOL, TYPE_CHAR, TYPE_FLOLAT, TYPE_DOUBLE}; // types of variables


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

int reformattedStackPointer = 0; // new stack pointer that works with variables in size of less then 4 bytes

void deleteVariableList(VariableList* varList); // deletes allocated memory for the list

int getSizeByType(enum VarTypes type); // returns the size of the type in bytes
void addNewVariable(VariableList* varList, char* identifier, enum VarTypes type); // call the upper function with placeInMemory = 0
int isVariableExist(VariableList* varList, char* identifier);
Variable* getVariable(VariableList* varList, char* identifier);
void removeVariable(VariableList* varList, char* identifier); // deletes allocated memory for the variable

void printVariable(Variable* var);
void printVariableList(VariableList* varList);

VariableList* createVariableListFromToken(llist tokenList);
// creates a variable list from a token list and run simple checks on the variable declarations









#endif


