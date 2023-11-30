#pragma once

#ifndef VARIABLE_MANAGER_H
#include "VariableManager.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void deleteVariableList(VariableList* varList) // deletes allocated memory for the list
{
	if (varList == NULL)
	{
		return;
	}

	if (varList->var != NULL) // if variable have not already been deleted.
	{
		removeVariable(varList, varList->var->Id);
	}

	deleteVariableList(varList->next); // cal on next node
	free(varList); // free current node
}

/**
 * \brief adds new variable to the list
 * \param varList variable list
 * \param identifier id for the new var
 * \param type type of new var
 * \param placeInMemory place in memory of new var
 */
void addNewVariableWithMemory(VariableList* varList, char* identifier, enum VarTypes type, int placeInMemory)
{
	if (isVariableExist(varList, identifier))
	{
		printf("Error: variable %s already exist\n", identifier);
		return;
	}

	// create new veriable
	VariableList* newVarNode = (VariableList*)malloc(sizeof(VariableList));
	newVarNode->var = (Variable*)malloc(sizeof(Variable));
	newVarNode->var->Id = (char*)malloc(sizeof(char) * (strlen(identifier) + 1));
	strcpy(newVarNode->var->Id, identifier);
	newVarNode->var->Type = type;
	newVarNode->var->placeInMemory = placeInMemory;
	newVarNode->next = NULL;

	// finding the next empty place in the list
	while (varList->next != NULL)
	{
		varList = varList->next;
	}

	// assiging the new value to the list
	varList->next = newVarNode;

}
// call the upper function with placeInMemory = 0
void addNewVariable(VariableList* varList, char* identifier, enum VarTypes type) 
{
	addNewVariableWithMemory(varList, identifier, type, 0);
}


/**
 * \brief check if a var id exist
 * \param varList 
 * \param identifier 
 * \return return 0 if not 1 if exist
 */
int isVariableExist(VariableList* varList, char* identifier)
{
	if (varList == NULL)
	{
		return 0;
	}

	if (varList->var != NULL && strcmp(varList->var->Id, identifier) == 0) // if the variable is the first in the list
	{
		return 1;
	}

	return isVariableExist(varList->next, identifier);
}

/**
 * \brief get a variable from the list
 * \param varList 
 * \param identifier 
 * \return return the variable if exist else return NULL
 */
Variable* getVariable(VariableList* varList, char* identifier)
{
	if (varList == NULL)
	{
		return NULL;
	}

	if (varList->var != NULL && strcmp(varList->var->Id, identifier) == 0) // if the variable is the first in the list
	{
		return varList->var;
	}

	return getVariable(varList->next, identifier);
}

void removeVariable(VariableList* varList, char* identifier) // deletes allocated memory for the variable
{
	if (varList == NULL)
	{
		return;
	}

	if (varList->var != NULL && strcmp(varList->var->Id, identifier) == 0) // if the variable is the first in the list
	{
		free(varList->var->Id);
		free(varList->var);
		return;
	}

	removeVariable(varList->next, identifier);
}

void printVariable(Variable* var)
{
	if (var == NULL)
	{
		return;
	}

	printf("Id: %s, Type: %d, place in memory: %d\n", var->Id, var->Type, var->placeInMemory);
}
void printVariableList(VariableList* varList)
{
	if (varList == NULL)
	{
		return;
	}

	printVariable(varList->var);
	printVariableList(varList->next);
}