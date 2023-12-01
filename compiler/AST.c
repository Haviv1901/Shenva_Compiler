
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


	//TODO: CLEAN THIS
	if (token == NULL || token->type == ADD || token->type == SUB ||
		token->type == MUL || token->type == DIV || token->type == MOD ||
		token->type == TOKEN_INT || token->type == ASSIGN)// 2 children types
	{
		result->children = (ASTNode**)malloc(TWO_CHILDREN_NODE * sizeof(ASTNode*));
		if (result->children == NULL)
		{
			free(result);
			return NULL;
		}
		result->children[0] = NULL;//setting children to NULL, the outer function can change that
		result->children[1] = NULL;

	}
	else if (token->type == ENDL || token->type == LPARN || token->type == RPARN || token->type == PRINT)// 1 kid type
	{
		result->children = (ASTNode**)malloc(ONE_CHILD_NODE * sizeof(ASTNode*));
		if (result->children == NULL)
		{
			free(result);
			return NULL;
		}
		result->children[0] = NULL;

	}
	else// if its a raw value, like a number, they dont have children
	{
		result->children = NULL;
	}
	return result;
}


/*
deleteAST: this function will delete an AST
input: the tree
output: non
*/
void deleteAST(ASTNode* head)
{

	if (head->token == NULL || head->token->type == ADD || head->token->type == SUB ||
		head->token->type == MUL || head->token->type == DIV || head->token->type == MOD ||
		head->token->type == TOKEN_INT || head->token->type == ASSIGN)// 2 children types
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
	else if (head->token->type == ENDL || head->token->type == LPARN || head->token->type == RPARN || head->token->type == PRINT)
	{
		// 1 child
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









