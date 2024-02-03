#pragma once
#include "ASTfunctions.h"

#include "ASTconditions.h"


/**
 * \brief function that will get the first lparn toeken and construct a tree from the inside of the paranthesis
 * \param curr lparn token
 * \return tree from inside the paranthesis
 */
ASTNode* buildASTFunctions(struct node** curr)
{
	struct node* currentNode = (*curr);
	Token* currentToken = currentNode->data; 


	ASTNode* result = NULL;


	if(isPrintToken(*currentToken))
	{
		result = createNewASTnode(currentToken); // PRINT 
		result->children[ONLY_CHILD] = buildASTFunctions_print(&currentNode);
	}
	else if(currentToken->type == TOKEN_FUNCTION_CALL)
	{
		result = createNewASTnode(currentToken); // func call
		result->children[ONLY_CHILD] = buildASTFunctions_functionCall(&currentNode);
	}
	else if(currentToken->type == TOKEN_DEF)
	{
		// in case of function definition
		result = buildASTFunctions_DefFunctions(curr);
	}


	return result;
}

ASTNode* buildASTFunctions_DefFunctions(node** curr)
{
	Token* tok = (*curr)->data;
	struct node* node = NULL;
	ASTNode* result = createNewASTnode((*curr)->data); // Creating the def node

	*curr = (*curr)->next;
	result->children[FUNC_ID] = createNewASTnode((*curr)->data); // Making the condition in child 1 (0)

	while((*curr)->data->type != TOKEN_LBRACK) // skeeping the arguments
	{
		*curr = (*curr)->next;
	}
	node = beracketEqualizer(*curr);

	*curr = (*curr)->next; // Going into the code
	result->children[CODE] = buildTree(curr); // Making the numeric tree there

	*curr = node; // Getting the newline token after the close bracket



	return result;
}


ASTNode* buildASTFunctions_functionCall(node** node)
{
	int parenthesesEqualizer = 1;
	Token* currentToken = (*node)->data;

	ASTNode* result = createNewASTnode(NULL); // create null node
	ASTNode* current = result;

	(*node) = (*node)->next; // skipping the function call token
	(*node) = (*node)->next; // skipping the first parentheses
	while(parenthesesEqualizer > 0)
	{
		currentToken = (*node)->data;

		if (isExpressionToken(*currentToken) || currentToken->type == TOKEN_VAR)
		{
			current->children[EXPRESSION] = buildASTNumeric(node); // build expression tree for arg
			current->children[NEXT] = createNewASTnode(NULL); // create null node
			current = current->children[NEXT]; // go to that null node
		}

		if (currentToken->type == TOKEN_LPARN)
		{
			parenthesesEqualizer++;
		}
		else if (currentToken->type == TOKEN_RPARN)
		{
			parenthesesEqualizer--;
		}
		else if(currentToken->type == TOKEN_ENDL) // should not go in here, but just in case ig
		{
			break;
		}

		(*node) = (*node)->next;
	}
	(*node) = (*node)->next; // skipping the last parentheses

	return result;
}


ASTNode* buildASTFunctions_print(struct node** curr)
{
	Token* currentToken = (*curr)->data;
	struct node* currentNode;
	if (currentToken->type != TOKEN_COMMA)
	{
		currentNode = (*curr)->next->next; // current node = first token inside the parenthesis

	}
	else
	{
		currentNode = (*curr)->next; // current node = first token inside the parenthesis
	}
	currentToken = currentNode->data;
	return buildASTNumeric(&currentNode); // currently only possible to have numeric expression inside the print function

}



