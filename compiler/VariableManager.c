#pragma once

#ifndef VARIABLE_MANAGER_H
#include "VariableManager.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int getSizeByType(enum VarTypes type)
{
	switch (type) // in bytes
	{
	case VAR_INT:
		return 4;
	case VAR_STRING:
		return 4;
	case VAR_BOOL:
		return 1;
	case VAR_CHAR:
		return 1;
	case VAR_FLOLAT:
		return 4;
	case VAR_DOUBLE:
		return 8;
	default:
		return 0;
	}

}

void deleteVariableList(VariableList* varList) // deletes allocated memory for the list
{
	if (varList == NULL)
	{
		return;
	}

	if (varList->var != NULL) // if variable have not already been deleted.
	{
		free(varList->var);
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
void createNewVariable(char* identifier, enum VarTypes type, VariableList** list)
{

	// create new veriable

	VariableList* newVarNode = (VariableList*)malloc(sizeof(VariableList));
	VariableList* curr = NULL;
	newVarNode->var = (Variable*)malloc(sizeof(Variable));
	newVarNode->var->Id = identifier;
	newVarNode->var->Type = type;
	newVarNode->var->size = getSizeByType(type);
	reformattedStackPointer += newVarNode->var->size; // update the stack pointer
	newVarNode->var->placeInMemory = reformattedStackPointer;
	
	newVarNode->next = NULL;
	if (*list == NULL)
	{
		*list = newVarNode;
	}
	else
	{
		curr = *list;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = newVarNode;
	}

}


/**
 * \brief check if a var id exist
 * \param varList 
 * \param identifier 
 * \return return 0 if not 1 if exist
 */
int isVariableExist(VariableList* varList, char* identifier)
{
	Variable* var = getVariable(varList, identifier);
	if (var == NULL)
	{
		return 0;
	}
	return 1;

}

/**
 * \brief get a variable from the list
 * \param varList 
 * \param identifier 
 * \return return the variable if exist else return NULL
 */
Variable* getVariable(VariableList* varList, char* identifier)
{
	VariableList* curr = varList;
	while (curr != NULL)
	{
		if (strcmp(curr->var->Id, identifier) == 0)
		{
			return curr->var;
		}
		curr = curr->next;
	}
	return NULL;
}



/*
createVariableListFromToken: this function will produce the var list from the tokens
input; the token list. 
output: a variable list, or NULL if there is a semantic error, or if there are no vars
*/
VariableList* createVariableListFromToken(llist* tokenList)
{
	VariableList* varList = NULL;

	if (tokenList == NULL)
	{
		return NULL;
	}

	struct node* curr = *tokenList;
	char* identifier = NULL;
	while (curr != NULL)// going through the token list
	{
		enum TokenTypes currentToken = ((Token*)(curr->data))->type;
		if (currentToken == TOKEN_INT) // if its an int token
		{
			curr = curr->next;
			identifier = (char*)(((Token*)(curr->data))->value);//getting identifier
			if (isVariableExist(varList, identifier)) // checking if id already exists
			{
				printf("Semantic error: variable %s is already defined\n", identifier);
				deleteVariableList(varList);
				return NULL;
			}
			// identifier has the allocated memory from the token list wich is goint to be deallocated soon -
			// so we are allocating new memory for the id.
			createNewVariable(identifier, VAR_INT, &varList);//adding var
		}
		else if (currentToken == VAR)//if its a variable
		{
			identifier = (char*)(((Token*)(curr->data))->value);
			if (!isVariableExist(varList, identifier)) // checking if variable has been declared before
			{
				printf("Semantic error: '%s' is undefined\n", identifier);
				deleteVariableList(varList);
				return NULL;
			}
		}
		curr = curr->next;
	}

	return varList;

}


/*
isVars: this function will check if there are Variables in the token list
input:the token list
output: true or false
*/
bool isVars(llist* tokenList) // what for ?
{
	struct node* curr = *tokenList;
	enum varTypes type;
	while (curr != NULL)
	{
		type = ((Token*)(curr->data))->type;
		if (type == VAR)// checking for a decleration
		{
			return true;
		}
		curr = curr->next;
	}
	return false;


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




