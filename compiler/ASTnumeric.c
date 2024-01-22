#pragma once
#include "ASTnumeric.h"

#include "ASTfunctions.h"


/**
 * \brief function to build AST from numeric expressions
 * \param curr first token shouuld be the first number from the numeric expression to build ast from
 * \return fully built ast from numeric expressions.
 */
ASTNode* buildASTNumeric(struct node** curr)
{
	return parseLogicalOps(curr);
}

/// <summary>
/// builds AST from the level of logical operators
/// </summary>
/// <param name="curr"></param>
/// <returns></returns>
ASTNode* parseLogicalOps(struct node** curr)
{
	ASTNode* holder = NULL, * node = NULL;
	holder = parseNotOp(curr);
	if (!((*curr) != NULL && ((((Token*)(*curr)->data)->type) == TOKEN_AND || ((Token*)(*curr)->data)->type == TOKEN_OR)))
	{
		return holder;
	}
	while ((*curr) != NULL && ((((Token*)(*curr)->data)->type) == TOKEN_AND || ((Token*)(*curr)->data)->type == TOKEN_OR))
	{
		node = createNewASTnode((Token*)(*curr)->data);
		node->children[0] = holder;
		(*curr) = (*curr)->next;
		node->children[1] = parseLogicalOps(curr);
		holder = node;

	}
	return node;
}

/// <summary>
/// builds AST from the level of boolean operators
/// </summary>
/// <param name="curr"></param>
/// <returns></returns>
ASTNode* parseNotOp(struct node** curr)
{
	ASTNode* holder = NULL, * node = NULL;
	if (((Token*)(*curr)->data)->type == TOKEN_NOT)
	{
		node = createNewASTnode((Token*)(*curr)->data);
		(*curr) = (*curr)->next;
		node->children[0] = parseBooleanOps(curr);
		return node;
	}
	else
	{
		return parseBooleanOps(curr);
	}
}

/// <summary>
/// builds AST from the level of boolean operators
/// </summary>
/// <param name="curr"></param>
/// <returns></returns>
ASTNode* parseBooleanOps(struct node** curr)
{
	ASTNode* holder = parseLast(curr), * node = NULL;
	if (!((*curr) != NULL && isBooleanExpressionToken(((Token*)(*curr)->data)->type)))
	{
		return holder;
	}
	node = createNewASTnode((Token*)(*curr)->data);
	node->children[0] = holder;
	(*curr) = (*curr)->next;
	node->children[1] = parseLast(curr);
	holder = node;
	return node;
}




/// <summary>
/// builds AST from the last level of tokens
/// </summary>
/// <param name="curr"></param>
/// <returns></returns>
ASTNode* parseLast(struct node** curr)
{
	ASTNode* holder = parseSecond(curr), *node = NULL;
	if (!((*curr) != NULL && ((Token*)(*curr)->data)->type != TOKEN_ENDL && (((Token*)(*curr)->data)->type == TOKEN_ADD || ((Token*)(*curr)->data)->type == TOKEN_SUB)))
	{
		return holder;
	}
	while ((*curr) != NULL && ((Token*)(*curr)->data)->type != TOKEN_ENDL && (((Token*)(*curr)->data)->type == TOKEN_ADD || ((Token*)(*curr)->data)->type == TOKEN_SUB))
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
	if (!((*curr) != NULL && ((Token*)(*curr)->data)->type != TOKEN_ENDL && (((Token*)(*curr)->data)->type == TOKEN_DIV || ((Token*)(*curr)->data)->type == TOKEN_MUL || ((Token*)(*curr)->data)->type == TOKEN_MODULO)))
	{
		return holder;
	}
	while ((*curr) != NULL && ((Token*)(*curr)->data)->type != TOKEN_ENDL && (((Token*)(*curr)->data)->type == TOKEN_DIV || ((Token*)(*curr)->data)->type == TOKEN_MUL || ((Token*)(*curr)->data)->type == TOKEN_MODULO))
	{

		node = createNewASTnode((Token*)(*curr)->data);
		if (((Token*)(*curr)->data)->type == TOKEN_MODULO)
		{
			node->children[1] = holder;
			(*curr) = (*curr)->next;
			node->children[0] = parseFirst(curr);
			holder = node;
		}
		else
		{
			node->children[1] = holder;
			(*curr) = (*curr)->next;
			node->children[0] = parseFirst(curr);
			holder = node;
		}
	}
	return node;
}

// Function to parse a factor.
ASTNode* parseFirst(struct node** curr)
{
	Token* tok = NULL;
	if ((*curr) != NULL && ((Token*)(*curr)->data)->type != TOKEN_ENDL)
	{
		if (((Token*)(*curr)->data)->type == TOKEN_LPARN)
		{
			(*curr) = (*curr)->next; // Consume the opening parenthesis.
			ASTNode* node = parseLogicalOps(curr);

			if (((Token*)(*curr)->data)->type == TOKEN_RPARN)
			{
				(*curr) = (*curr)->next; // Consume the closing parenthesis.
				return node;
			}
		}
		else
		{
			// It's a number or var or a function call.
			ASTNode* node;
			if((*curr)->data->type == TOKEN_FUNCTION_CALL)
			{
				node = buildASTFunctions(curr);
				(*curr) = (*curr)->next;
				(*curr) = (*curr)->next;

				int parenthesesEqualizer = 1;
				Token* currentToken;
				while (parenthesesEqualizer > 0)
				{
					currentToken = (*curr)->data;
					if (currentToken->type == TOKEN_LPARN)
					{
						parenthesesEqualizer++;
					}
					else if (currentToken->type == TOKEN_RPARN)
					{
						parenthesesEqualizer--;
					}
					else if (currentToken->type == TOKEN_ENDL) // should not go in here, but just in case ig
					{
						break;
					}

					(*curr) = (*curr)->next;
				}

			}
			else
			{
				node = createNewASTnode((*curr)->data);
				tok = (*curr)->data;
				if (tok->type == TOKEN_INPUT_INT || tok->type == TOKEN_INPUT_CHAR || tok->type == TOKEN_INPUT_FLOAT)
				{
					(*curr) = (*curr)->next;
					(*curr) = (*curr)->next;
				}
				(*curr) = (*curr)->next;
			}


			

			return node;
		}
	}
}