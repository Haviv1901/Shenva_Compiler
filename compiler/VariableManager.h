#pragma once


#ifndef VARIABLE_MANAGER_H
#define VARIABLE_MANAGER_H

enum VarTypes {TYPE_INT, TYPE_STRING, TYPE_BOOL, TYPE_CHAR, TYPE_FLOLAT, TYPE_DOUBLE}; // types of variables


struct Variable
{
	char* Id; // identifier
	enum VarTypes Type; 
	int placeInMemory; 
} typedef Variable;

struct VariableList
{
	Variable* var;
	struct VariableList* next;
} typedef VariableList;

void deleteVariableList(VariableList* varList); // deletes allocated memory for the list

void addNewVariableWithMemory(VariableList* varList, char* identifier, enum VarTypes type, int placeInMemory);
void addNewVariable(VariableList* varList, char* identifier, enum VarTypes type); // call the upper function with placeInMemory = 0
int isVariableExist(VariableList* varList, char* identifier);
Variable* getVariable(VariableList* varList, char* identifier);
void removeVariable(VariableList* varList, char* identifier); // deletes allocated memory for the variable

void printVariable(Variable* var);
void printVariableList(VariableList* varList);









#endif


