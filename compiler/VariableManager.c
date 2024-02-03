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
FuncNode* funcListHead = NULL;
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

void callDeleteFuncList()
{
	deleteFuncList(funcListHead);
}


/**
 * \brief adds new variable to the list
 * \param varList variable list
 * \param identifier id for the new var
 * \param type type of new var
 * \param placeInMemory place in memory of new var
 */
void createNewVariable(char* identifier, enum VarTypes type, VariableList** varList, int varScope, bool isParameter, int parSize)
{

	// create new veriable

	VariableList* newVarNode = (VariableList*)malloc(sizeof(VariableList));
	VariableList* curr = NULL;
	newVarNode->var = (Variable*)malloc(sizeof(Variable));
	newVarNode->var->Id = identifier;
	newVarNode->var->Type = type;
	newVarNode->var->size = getSizeByType(type);
	if (isParameter == false)
	{
		reformattedStackPointer += newVarNode->var->size; // update the stack pointer
		newVarNode->var->placeInMemory = reformattedStackPointer;
	}
	else
	{
		newVarNode->var->placeInMemory = parSize;
	}

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

	Variable* curr = getVariableByScope(varList, identifier, varScope);
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
	else
	{
		return VAR_ERROR;
	}
}









/*
createFunctionList: this function will create a list of functions
input: the tokenList
output: non
*/
FuncNode* createFunctionList(llist* tokenList)
{
	int scopeCounter = 0, paramNum = 0, paramSize = 0, parSize = 0;
	FuncNode* hold = NULL, *currFunc = NULL;
	if (tokenList == NULL)
	{
		return NULL;
	}
	struct node* curr = *tokenList;
	char* id = NULL;
	Token* tok = NULL;

	enum VarTypes type;

	while (curr)// going through the token list
	{
		tok = curr->data;// tok is for convinience
		if (tok->type == TOKEN_LBRACK)// if new scope, then count it
		{
			scopeCounter++;
		}

		if (tok->type == TOKEN_DEF)
		{
			curr = curr->next;
			tok = curr->data;// skipping to name of function
			
			id = tok->value;//getting name
			if (getFuncByName(funcListHead, id) != NULL)
			{
				printf("Semantic error: function with the name %s, is already defined\n", id);
				return NULL;
			}



			curr = curr->next;
			curr = curr->next;
			tok = curr->data;//skipping to first parameters

			parSize = -8;//resetting parameters place in memory
			paramNum = 0;//reseting the number and size of parameters
			paramSize = 0;
			while (tok->type != TOKEN_RPARN)//until the end of the function
			{
				if (tok->type == TOKEN_COMMA)// if comma then skip
				{
					curr = curr->next;
					tok = curr->data;
				}
				type = getVarByTokenType(tok->type);// getting parameter type
				if (type != VAR_ERROR)// if its a type and not an identifier
				{
					createNewVariable((Token*)(curr->next->data)->value, type, &varListHead, scopeCounter + 1, true, parSize);//creating parameter in varList
					parSize -= getSizeByType(type);// reducing parameter place in memory for the next one
					paramNum += 1;//adding 1 to count
					paramSize += getSizeByType(type);// adding to total size
				}
				curr = curr->next;			
				tok = curr->data;
			}
			hold = createNewFuncNode(id, paramNum, paramSize, scopeCounter + 1);// creating new function node
			if (funcListHead == NULL)
			{
				funcListHead = hold;
			}
			else
			{
				currFunc = funcListHead;//appending new function node
				while (currFunc->next)
				{
					currFunc = currFunc->next;
				}
				currFunc->next = hold;
			}
		}
		curr = curr->next;//going to the next token
	}
	return funcListHead;
}

// checks if there are any funcntions in the token list`
bool isFuncs(llist* tokenList)
{
	struct node* curr = *tokenList;
	while (curr)
	{
		if ((curr->data)->type == TOKEN_DEF)
		{
			return true;
		}
		curr = curr->next;
	}
	return false;
}

int callGetFuncIndexByName(char* id)
{
	return getFuncIndexByName(funcListHead, id);
}



/*
getFuncFirstParameterNode: this function will return a pointer to the first parameter in the varlist of a function scope 
inpiut: the var list, and the scope of the function to look for
output: the ptr to the first parameter in the list
*/
VariableList* getFuncFirstParameterNode(VariableList* varList, int funcScope)
{
	VariableList* curr = varList;
	while (curr)
	{
		if (curr->var->scope == funcScope && curr->var->placeInMemory < 0)
		{
			return curr;
		}


		curr = curr->next;
	}
	return NULL;
}




FuncNode* callGetFunction(char* id)
{
	return getFuncByName(funcListHead, id);
}

VariableList* createVariableListFromToken(llist* tokenList)
{
	if (createFunctionList(tokenList) == NULL && isFuncs(tokenList))
	{
		printf("Semantic  analysis failed.\n");
		callDeleteFuncList();
		deleteVariableList(varListHead);
		return NULL;
	}
	if(createVariableListFromScope(tokenList, -1 , scopeTreeHead) == 0)
	{
		printf("Semantic  analysis failed.\n");
		deleteScopeTree(scopeTreeHead);
		callDeleteFuncList();
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
	FuncNode* funcNode = NULL;
	bool isNextScopeFunc = false;
	while (curr != NULL) // going through the token list
	{
		enum TokenTypes currentToken = ((Token*)(curr->data))->type;
		if (currentToken == TOKEN_INT || currentToken == TOKEN_CHAR || currentToken == TOKEN_FLOAT || currentToken == TOKEN_BOOL)
			// if its a decleration token
		{
			curr = curr->next;
			identifier = (char*)(((Token*)(curr->data))->value);//getting identifier
			if(callIsVariablExist(varListHead, identifier, currentScope) || (currentScope == GLOBAL && getVariable(varListHead, identifier) != NULL))
			{
				printf("Semantic error: variable %s is already defined in scope\n", identifier);
				deleteVariableList(varListHead);
				return 0;
			}
			createNewVariable(identifier, getVarByTokenType(currentToken), &varListHead, currentScope, false, 0);//adding var
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
		else if (currentToken == TOKEN_FUNCTION_CALL)
		{
			identifier = (char*)(((Token*)(curr->data))->value);
			funcNode = getFuncByName(funcListHead, identifier);
			if (funcNode == NULL) // checking if function has been declared before
			{
				printf("Semantic error: '%s' is undefined\n", identifier);
				deleteVariableList(varListHead);
				return 0;
			}
			curr = curr->next;
			if (isParamNumValid(curr, funcNode->paramNum) == 0)
			{
				printf("Semantic error: '%s' function call dosen't have enough parameters\n", identifier);
				deleteVariableList(varListHead);
				return 0;
			}
		}
		else if (currentToken == TOKEN_DEF)
		{
			while (currentToken != TOKEN_ENDL)
			{
				curr = curr->next;
				currentToken = ((curr->data))->type;
			}
			isNextScopeFunc = true;
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
			if (isNextScopeFunc)
			{
				reformattedStackPointer = 0;
			}
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
isParamNumValid: this function will check if the function call has enough parameters 
input: the current node and the number of parameters this function is asking for
output: an int indicating validity
*/
int isParamNumValid(struct node* curr, int paramNum)
{
	Token* tok = curr->data;
	int numberOfParams = 0, equalizer = 0;

	curr = curr->next;
	tok = curr->data;// going over the Lparn
	if (tok->type != TOKEN_RPARN)// if there are even any parameters
	{
		numberOfParams++;// at least 1 parameter
		curr = curr->next;
		tok = curr->data;
		while (tok->type != TOKEN_RPARN)
		{
			if (tok->type == TOKEN_COMMA)// comma meaning mor parameters after
			{
				numberOfParams++;
				curr = curr->next;
				tok = curr->data;
			}
			else if (tok->type == TOKEN_LPARN)// equalizing parenthasis because a function call is also an expression
			{
				equalizer = 0;
				do
				{
					if (tok->type == TOKEN_LPARN)
					{
						equalizer++;
					}

					if (tok->type == TOKEN_RPARN)
					{
						equalizer--;
					}
					curr = curr->next;
					tok = curr->data;
				} while (equalizer != 0);
			}
			else
			{
				curr = curr->next;
				tok = curr->data;// going to next if neither
			}
		}
	}
	if (numberOfParams == paramNum)
	{
		return 1;
	}
	else
	{
		return 0;
	}
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




