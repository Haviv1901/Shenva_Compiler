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
	if (token == NULL || token->type == ADD || token->type == SUB || token->type == MUL || token->type == DIV)// 2 children types
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
	else if (token->type == ENDL || token->type == PRINT || token->type == LPARN || token->type == RPARN)// 1 kid type
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
	if (head->token == NULL || head->token->type == ADD || head->token->type == SUB || head->token->type == MUL || head->token->type == DIV)
	{//2 child scenario
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
	else if (head->token->type == ENDL || head->token->type == PRINT || head->token->type == LPARN || head->token->type == RPARN)
	{//1 child scenario
		if (head->children[0] != NULL)
		{
			deleteAST(head->children[0]);
		}
		free(head->children);
	}
	else
	{
		free(head->children);
	}

	free(head);


}


// Function to parse an expression.
ASTNode* parseExpression(struct node** curr)
{
	ASTNode* holder = parseTerm(curr), * node = NULL;
	if (!((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL && (((Token*)(*curr)->data)->type == ADD || ((Token*)(*curr)->data)->type == SUB)))
	{
		return holder;
	}
	while ((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL && (((Token*)(*curr)->data)->type == ADD || ((Token*)(*curr)->data)->type == SUB))
	{
		
		 node = createNewASTnode((Token*)(*curr)->data);
		 node->children[1] = holder;
		 (*curr) = (*curr)->next;
		 node->children[0] = parseTerm(curr);
		 holder = node;
		
	}
	return node;
}

// Function to parse a term.
ASTNode* parseTerm(struct node** curr)
{
	ASTNode* holder = parseFactor(curr), * node = NULL;
	if (!((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL && (((Token*)(*curr)->data)->type == DIV || ((Token*)(*curr)->data)->type == MUL)))
	{
		return holder;
	}
	while ((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL && (((Token*)(*curr)->data)->type == DIV || ((Token*)(*curr)->data)->type == MUL))
	{

		node = createNewASTnode((Token*)(*curr)->data);
		node->children[1] = holder;
		(*curr) = (*curr)->next;
		node->children[0] = parseFactor(curr);


	}
	return node;
}

// Function to parse a factor.
ASTNode* parseFactor(struct node** curr)
{
	if ((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL)
	{
		if (((Token*)(*curr)->data)->type ==  LPARN)
		{
			(*curr) = (*curr)->next; // Consume the opening parenthesis.
			ASTNode* node = parseExpression(curr);

			if (((Token*)(*curr)->data)->type == RPARN)
			{
				(*curr) = (*curr)->next; // Consume the closing parenthesis.
				return node;
			}
		}
		else
		{
			// It's a number.
			ASTNode* node = createNewASTnode((Token*)(*curr)->data);
			(*curr) = (*curr)->next;
			return node;
		}
	}
}


ASTNode* makeTree(struct node** curr)
{
	if (*curr == NULL)
	{
		return NULL;
	}
	struct node* nodeHolder = *curr;
	ASTNode* result = NULL;
	Token* temp = (Token*)(*curr)->data, *holderTok = NULL;
	if (temp->type == NUM || temp->type == LPARN)
	{
		result = createNewASTnode(NULL);
		holderTok = ((Token*)nodeHolder->data);
		while (nodeHolder != NULL && holderTok->type != ENDL)
		{
			nodeHolder = nodeHolder->next;
			if (nodeHolder != NULL)
			{
				holderTok = ((Token*)nodeHolder->data);
			}
		}
		result->children[1] = parseExpression(curr);
		*curr = nodeHolder;
		result->children[0] = makeTree(curr);
	}
	else if (temp->type == ENDL)
	{
		result = createNewASTnode(temp);
		*curr = (*curr)->next;
		result->children[0] = makeTree(curr);
	}
	else if (temp->type == PRINT)
	{
		int parenthasisEqualizer = 0;
		result = createNewASTnode(temp);
		*curr = (*curr)->next;
		temp = (Token*)(*curr)->data;
		nodeHolder = *curr;
		holderTok = ((Token*)nodeHolder->data);
		result->children[0] = createNewASTnode(temp);
		parenthasisEqualizer--;
		while (holderTok->type != RPARN || parenthasisEqualizer != 0)
		{
			nodeHolder = nodeHolder->next;
			holderTok = ((Token*)nodeHolder->data);
			if (holderTok->type == LPARN)
			{
				parenthasisEqualizer--;
			}
			else if (holderTok->type == RPARN)
			{
				parenthasisEqualizer++;
			}
		}
		holderTok->type = ENDL;
		*curr = (*curr)->next;
		result->children[0]->children[0] = makeTree(curr);
		holderTok->type = RPARN;
		curr = nodeHolder;
		*curr = (*curr)->next;
		result->children[0]->children[0]->children[0]->children[0] = makeTree(curr);
	}

	return result;




}





