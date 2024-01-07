#pragma once

#ifndef VARIABLE_MANAGER_H
#include "VariableManager.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reformattedStackPointer = 0; // new stack pointer that works with variables in size of less then 4 bytes
ScopeTreeNode* scopeTreeHead = NULL;
VariableList* varListHead = NULL;
int nextScope = -1;

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
	case VAR_FLOAT:
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

	free(varList->var); // its ok to free(null)
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
void createNewVariable(char* identifier, enum VarTypes type, VariableList** varList, int varScope)
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
	newVarNode->var->scope = varScope;
	
	newVarNode->next = NULL;
	if (*varList == NULL)
	{
		*varList = newVarNode;
	}
	else
	{
		curr = *varList;
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
int isVariableExistInScope(VariableList* varList, char* identifier, int varScope)
{

	VariableList* curr = getVariableByScope(varList, identifier, varScope);
	if (curr)
	{
		return 1;
	}

	return 0;

}

// function to get a variable's scope by name
int getVariableScope(VariableList* varList, char* identifier)
{
	Variable* var = getVariable(varList, identifier);
	if (var == NULL)
	{
		return -1;
	}
	return var->scope;
}

/*
 * get variable by scope
 * return: variable in  scope inputed
 */
Variable* getVariableByScope(VariableList* varList, char* identifier, int scope)
{
	VariableList* curr = varList;
	while (curr != NULL)
	{
		if (strcmp(curr->var->Id, identifier) == 0 && isAncestor(scopeTreeHead, scope, curr->var->scope))
		{
			return curr->var;
		}
		curr = curr->next;
	}
	return NULL;
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


bool callIsVariablExist(VariableList* varList, char* identifier, int currentScope)
{
	return isVariableExistInScope(varList, identifier, currentScope); // checking if id already exists
}

enum VarTypes getVarByTokenType(enum TokenTypes currentToken)
{
	if (currentToken == TOKEN_INT)
	{
		return VAR_INT;
	}
	else if (currentToken == TOKEN_CHAR)
	{
		return VAR_CHAR;
	}
	else if (currentToken == TOKEN_FLOAT)
	{
		return VAR_FLOAT;
	}
	else if (currentToken == TOKEN_STRING)
	{
		return VAR_STRING;
	}
	else if (currentToken == TOKEN_BOOL)
	{
		return VAR_BOOL;
	}
}


VariableList* createVariableListFromToken(llist* tokenList)
{

	if(createVariableListFromScope(tokenList, -1 , scopeTreeHead) == 0)
	{
		printf("Semantic  analysis failed.\n");
		deleteScopeTree(scopeTreeHead);
		return NULL;
	}
	return varListHead;
}


void callDeleteScopeTree()
{
	deleteScopeTree(scopeTreeHead);
}



/*
createVariableListFromScope: this function will produce the var list from the tokens
input; the token list. 
output: a variable list, or NULL if there is a semantic error, or if there are no vars
*/
int createVariableListFromScope(llist* tokenList, int currentScope, ScopeTreeNode* currentScopeNode)
{

	nextScope++;
	currentScope = nextScope;
	if (scopeTreeHead == NULL)
	{
		scopeTreeHead = createNode(currentScope);
		currentScopeNode = scopeTreeHead;
	}
	else
	{
		currentScopeNode = addChild(currentScopeNode, currentScope);
	}
	

	int holderForPlacceInMemory;
	int outerBracketBalance = 1;


	if (tokenList == NULL)
	{
		return 0;
	}

	struct node* curr = *tokenList;
	char* identifier = NULL;
	while (curr != NULL) // going through the token list
	{
		enum TokenTypes currentToken = ((Token*)(curr->data))->type;
		if (currentToken == TOKEN_INT || currentToken == TOKEN_CHAR || currentToken == TOKEN_FLOAT || currentToken == TOKEN_BOOL)
			// if its a decleration token
		{
			curr = curr->next;
			identifier = (char*)(((Token*)(curr->data))->value);//getting identifier
			if(callIsVariablExist(varListHead, identifier, currentScope))
			{
				printf("Semantic error: variable %s is already defined in scope\n", identifier);
				deleteVariableList(varListHead);
				return 0;
			}
			createNewVariable(identifier, getVarByTokenType(currentToken), &varListHead, currentScope);//adding var
		}
		else if (currentToken == TOKEN_VAR)//if its a variable
		{
			identifier = (char*)(((Token*)(curr->data))->value);
			if (!callIsVariablExist(varListHead, identifier, currentScope)) // checking if variable has been declared before
			{
				printf("Semantic error: '%s' is undefined\n", identifier);
				deleteVariableList(varListHead);
				return 0;
			}
		}
		else if (currentToken == TOKEN_ERROR)
		{
			printf("Error occurred.\n");
			deleteVariableList(varListHead);
			return 0;
		}
		else if (currentToken == TOKEN_LBRACK)
		{
			outerBracketBalance++;
			holderForPlacceInMemory = reformattedStackPointer;
			curr = curr->next; // skipping the left bracket token


			if(createVariableListFromScope(&curr, currentScope, currentScopeNode) == 0)
			{
				return 0;
			}
			

			// skip all tokens until after the right bracket.
			int bracketBalance = 1;
			while (bracketBalance != 0)
			{

				if (((Token*)(curr->data))->type == TOKEN_LBRACK)
				{
					bracketBalance++;
				}


				if(((Token*)(curr->data))->type == TOKEN_RBRACK)
				{
					bracketBalance--;
				}

				curr = curr->next;
			}

			reformattedStackPointer = holderForPlacceInMemory;
		}
		else if (currentToken == TOKEN_RBRACK)
		{
			//outerBracketBalance--;
			//if(outerBracketBalance == 0)
			//{
			//	return 1;
			//}

			return 1;

		}
		curr = curr->next;
	}

	return 1;

}

/*
getSizeOfScope: this function will count the size of a given scope
input: the list of vars and the scope
output: the combined size of all of the variables in the scope
*/
int getSizeOfScope(VariableList* list, int scope)
{
	int result = 0;
	VariableList* curr = list;
	while (curr)
	{
		if (curr->var->scope == scope)
		{
			result += curr->var->size;//gettuing size

		}
		curr = curr->next;
	}

	return result;
}



void appendVariableList(VariableList** list1, VariableList* list2)
{
	if (*list1 == NULL) 
	{
		*list1 = list2;
	}
	else 
	{
		VariableList* temp = *list1;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = list2;
	}
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
		if (type == TOKEN_VAR)// checking for a decleration
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




