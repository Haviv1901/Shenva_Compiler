#include "FunctionList.h"



/*
createNewFuncNode: this function will create a new function node
input: the id, number of parameters and their size
output: the new node
*/
FuncNode* createNewFuncNode(char* id, int paramNum, int paramSize)
{
	FuncNode* result = (FuncNode*)malloc(sizeof(FuncNode));
	if (result == NULL)
	{
		return NULL;
	}
	result->id = id;
	result->paramNum = paramNum;
	result->paramSize = paramSize;
	result->next = NULL;
	return result;
}

/*
deleteFuncList: this function will delete a list of functions
input: the head of the list
output: non
*/
void deleteFuncList(FuncNode* head)
{
	FuncNode* curr = head, * temp = NULL;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
}

FuncNode* getFuncByName(FuncNode* head, char* id)
{
	FuncNode* curr = head;
	while (curr)
	{
		if (strcmp(curr->id, id) == 0)
		{
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

