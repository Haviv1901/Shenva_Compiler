#pragma once
#include "ASTfunctions.h"



/**
 * \brief function that will get the first lparn toeken and construct a tree from the inside of the paranthesis
 * \param curr lparn token
 * \return tree from inside the paranthesis
 */
ASTNode* buildASTFunctions(struct node** curr)
{
	struct node* currentNode = (*curr);
	Token* currentToken = currentNode->data; 


	ASTNode* result = createNewASTnode(currentToken); // PRINT \ DEF \ FUNC token node


	if(isPrintToken(*currentToken))
	{
		result->children[ONLY_CHILD] = buildASTFunctions_print(&currentNode);
	}
	else if(currentToken->type == TOKEN_FUNCTION_CALL)
	{
		result->children[ONLY_CHILD] = buildASTFunctions_functionCall(&currentNode);
	}
	else if(currentToken->type == TOKEN_DEF)
	{
		// in case of function definition

		//result->children[ONLY_CHILD] = createNewASTnode((*curr)->next->data); // first child is the func ID
		//result->children[ARGUMENT_LIST] = extractArgumentList(curr);
	}


	return result;
}




ASTNode* buildASTFunctions_functionCall(node** node)
{
	int parenthesesEqualizer = 1;
	Token* currentToken = (*node)->data;

	ASTNode* result = createNewASTnode(NULL); // create null node
	ASTNode** pResult = &result;

	(*node) = (*node)->next; // skipping the function call token
	(*node) = (*node)->next; // skipping the first parentheses
	while(parenthesesEqualizer > 0)
	{
		currentToken = (*node)->data;

		if (isExpressionToken(*currentToken))
		{
			result->children[EXPRESSION] = buildASTNumeric(node); // build expression tree for arg
			result->children[NEXT] = createNewASTnode(NULL); // create null node
			result = result->children[NEXT]; // go to that null node
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



