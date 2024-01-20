#pragma once
#include <stdlib.h>
#include <string.h>


typedef struct FuncNode
{
	char* id;
	int paramNum;
	int paramSize;
	struct FuncNode* next;

} FuncNode;

FuncNode* createNewFuncNode(char* id, int paramNum, int paramSize);
void deleteFuncList(FuncNode* head);
FuncNode* getFuncByName(FuncNode* head, char* id);


