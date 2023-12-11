
#include "AST.h"

#include <stdio.h>
#include <stdlib.h>


/*
createNewASTnode: this function will create a new node in the tree
input: the token of the node as a ptr
output: the ptr to the new node
*/
ASTNode* createNewASTnode(Token* token)
{
	ASTNode* result = (ASTNode*)malloc(sizeof(ASTNode));//allocating the node
	if (result == NULL)
	{
		return NULL;
	}
	result->token = token;//setting token

	if (token == NULL || isTwoChildNode(token->type)) // checking if the token is a two child type of token
	{
		result->children = (ASTNode**)malloc(TWO_CHILDREN_NODE * sizeof(ASTNode*));
		if (result->children == NULL)
		{
			free(result);
			return NULL;
		}
		result->children[0] = NULL; // setting children to NULL, the outer function can change that
		result->children[1] = NULL;

	}
	else if (isOneChildNode(token->type)) // checking if the token is a one child type of token	
	{
		result->children = (ASTNode**)malloc(ONE_CHILD_NODE * sizeof(ASTNode*));
		if (result->children == NULL)
		{
			free(result);
			return NULL;
		}
		result->children[0] = NULL;

	}
	else // else:   char / int / 
	{
		result->children = NULL;
	}
	return result;
}


void deleteAST(ASTNode* head)
{ 
	if (head->token == NULL || isTwoChildNode(head->token->type)) // checking if the token is a two child type of token
	{
		// 2 child
		if (head->children[0] != NULL)
		{
			deleteAST(head->children[0]);
		}

		if (head->children[1] != NULL)
		{
			deleteAST(head->children[1]);
		}
		free(head->children);
	}
	else if (isOneChildNode(head->token->type)) // checking if the token is a one child type of token
	{
		if (head->children[0] != NULL)
		{
			deleteAST(head->children[0]);
		}
		free(head->children);
	}
	else // no child
	{
		free(head->children);
	}

	free(head);
}

int isTwoChildNode(enum TokenTypes token)
{
	if (token == TOKEN_ADD ||
		token == TOKEN_SUB ||
		token == TOKEN_MUL ||
		token == TOKEN_DIV ||
		token == TOKEN_MODULO ||
		token == TOKEN_INT ||
		token == TOKEN_CHAR ||
		token == TOKEN_FLOAT ||
		token == TOKEN_ASSIGN)
	{
		return 1;
	}
	return 0;
}


int isOneChildNode(enum TokenTypes token)
{
	if (token == TOKEN_ENDL ||
		token == TOKEN_LPARN ||
		token == TOKEN_RPARN ||
		token == TOKEN_PRINT_CHAR ||
		token == TOKEN_PRINT_INT)
	{
		return 1;
	}
	return 0;
}




