#pragma once
#include "ASTnumeric.h"


/**
 * \brief function to build AST from numeric expressions
 * \param curr first token shouuld be the first number from the numeric expression to build ast from
 * \return fully built ast from numeric expressions.
 */
ASTNode* buildASTNumeric(struct node** curr)
{
	return parseLast(curr);
}




/// <summary>
/// builds AST from the last level of tokens
/// </summary>
/// <param name="curr"></param>
/// <returns></returns>
ASTNode* parseLast(struct node** curr)
{
	ASTNode* holder = parseSecond(curr), *node = NULL;
	if (!((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL && (((Token*)(*curr)->data)->type == ADD || ((Token*)(*curr)->data)->type == SUB)))
	{
		return holder;
	}
	while ((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL && (((Token*)(*curr)->data)->type == ADD || ((Token*)(*curr)->data)->type == SUB))
	{
		node = createNewASTnode((Token*)(*curr)->data);
		node->children[0] = holder;
		(*curr) = (*curr)->next;
		node->children[1] = parseLast(curr);
		holder = node;

	}
	return node;
}

/**
 * \brief 
 * \param curr 
 * \return 
 */
ASTNode* parseSecond(struct node** curr)
{
	ASTNode* holder = parseFirst(curr), * node = NULL;
	if (!((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL && (((Token*)(*curr)->data)->type == DIV || ((Token*)(*curr)->data)->type == MUL)))
	{
		return holder;
	}
	while ((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL && (((Token*)(*curr)->data)->type == DIV || ((Token*)(*curr)->data)->type == MUL))
	{

		node = createNewASTnode((Token*)(*curr)->data);
		node->children[0] = holder;
		(*curr) = (*curr)->next;
		node->children[1] = parseSecond(curr);
		holder = node;


	}
	return node;
}

// Function to parse a factor.
ASTNode* parseFirst(struct node** curr)
{
	if ((*curr) != NULL && ((Token*)(*curr)->data)->type != ENDL)
	{
		if (((Token*)(*curr)->data)->type == LPARN)
		{
			(*curr) = (*curr)->next; // Consume the opening parenthesis.
			ASTNode* node = parseLast(curr);

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