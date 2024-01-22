
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
	ASTNode* result = (ASTNode*)malloc(sizeof(ASTNode)); //allocating the node
	if (result == NULL)
	{
		return NULL;
	}
	result->token = token; //setting token

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
	else if (isThreeChildNode(token->type))
	{
		result->children = (ASTNode**)malloc((TWO_CHILDREN_NODE + 1) * sizeof(ASTNode*));
		if (result->children == NULL)
		{
			free(result);
			return NULL;
		}
		result->children[0] = NULL; // setting children to NULL, the outer function can change that
		result->children[1] = NULL;
		result->children[2] = NULL;

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
	else // else:   char / int / decimal / input functions
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
	else if (isThreeChildNode(head->token->type))
	{
		// 3 child
		if (head->children[0] != NULL)
		{
			deleteAST(head->children[0]);
		}
		if (head->children[1] != NULL)
		{
			deleteAST(head->children[1]);
		}
		if (head->children[2] != NULL)
		{
			deleteAST(head->children[2]);
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
	else // else:   char / int / decimal / input functions
	{
		free(head->children);
	}

	free(head);
}


int isThreeChildNode(enum TokenTypes token)
{
	if (token == TOKEN_IF  ||
		token == TOKEN_FOR )
	{
		return 1;
	}
	return 0;
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
		token == TOKEN_ASSIGN ||
		token == TOKEN_OR ||
		token == TOKEN_AND || 
		token == TOKEN_EQUALS || 
		token == TOKEN_NOT_EQUALS || 
		token == TOKEN_GREATER ||
		token == TOKEN_DEF ||
		token == TOKEN_NOT_GREATER || 
		token == TOKEN_LESSER || 
		token == TOKEN_NOT_LESSER || 
		token == TOKEN_GREATER_EQUALS || 
		token == TOKEN_LESSER_EQUALS ||
		token == TOKEN_BOOL ||
		token == TOKEN_WHILE)
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
		token == TOKEN_PRINT_FLOAT ||
		token == TOKEN_PRINT_INT ||
		token == TOKEN_NOT ||
		token == TOKEN_FUNCTION_CALL ||
		token == TOKEN_ELSE)
	{
		return 1;
	}
	return 0;
}


int isConditionOrLoopToken(Token token)
{
	if (token.type == TOKEN_IF ||
		token.type == TOKEN_FOR ||
		token.type == TOKEN_WHILE)
	{
		return 1;
	}
	return 0;
}


int isPrintToken(Token token)
{
	if (token.type == TOKEN_PRINT_INT ||
		token.type == TOKEN_PRINT_CHAR ||
		token.type == TOKEN_PRINT_FLOAT)
	{
		return 1;
	}
	return 0;
}

int isVariableToken(Token token)
{
	if (token.type == TOKEN_INT ||
		token.type == TOKEN_CHAR ||
		token.type == TOKEN_FLOAT ||
		token.type == TOKEN_BOOL)
	{
		return 1;
	}
	return 0;
}

int isExpressionToken(Token token)
{
	if (token.type == TOKEN_NUM ||
		token.type == TOKEN_DECIMAL || // if numeric expression
		token.type == TOKEN_LETTER ||
		token.type == TOKEN_INPUT_CHAR ||
		token.type == TOKEN_INPUT_FLOAT ||
		token.type == TOKEN_INPUT_INT ||
		token.type == TOKEN_LPARN ||
		token.type == TOKEN_NOT || // if numeric expression
		token.type == TOKEN_ADD ||
		token.type == TOKEN_SUB ||
		token.type == TOKEN_MUL ||
		token.type == TOKEN_DIV ||
		token.type == TOKEN_FUNCTION_CALL ||
		token.type == TOKEN_MODULO)
	{
		return 1;
	}
	return 0;
}


int isBooleanExpressionToken(enum TokenTypes token)
{
	if (token == TOKEN_EQUALS ||
		token == TOKEN_NOT_EQUALS ||
		token == TOKEN_GREATER ||
		token == TOKEN_NOT_GREATER ||
		token == TOKEN_LESSER ||
		token == TOKEN_NOT_LESSER ||
		token == TOKEN_GREATER_EQUALS ||
		token == TOKEN_LESSER_EQUALS)
	{
		return 1;
	}
	return 0;
}



