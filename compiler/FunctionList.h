#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct FuncNode
{
	char* id;
	int paramNum;
	int paramSize;
	int scope;
	struct FuncNode* next;

} FuncNode;

FuncNode* createNewFuncNode(char* id, int paramNum, int paramSize, int scope);
void deleteFuncList(FuncNode* head);
FuncNode* getFuncByName(FuncNode* head, char* id);
int getFuncIndexByName(FuncNode* head, char* id);


