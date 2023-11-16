#pragma once


#include "llist.h"
struct Token;
#ifndef AST_H
#define AST_H


#define TWO_CHILDREN_NODE 2
#define ONE_CHILD_NODE 1
#define LEAF 0

struct ASTNode
{
	Token* token;
	struct ASTNode** children;
	
} typedef ASTNode;




ASTNode* createNewASTnode(Token* token);
void deleteAST(ASTNode* head);

ASTNode* parseExpression(struct node* curr);
ASTNode* parseTerm(struct node* curr);
ASTNode* parseFactor(struct node* curr);


#endif