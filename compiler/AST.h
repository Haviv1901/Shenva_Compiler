#pragma once


#include "llist.h"
struct Token;
#ifndef AST_H


#define AST_H

enum { LEAF=0,ONE_CHILD_NODE=1,TWO_CHILDREN_NODE=2};


// when handling with tokenless nodes
enum {NEXT=0, EXPRESSION};

struct ASTNode
{
	Token* token;
	struct ASTNode** children;
	
} typedef ASTNode;


ASTNode* createNewASTnode(Token* token);
void deleteAST(ASTNode* head);






#endif