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
	if(currentToken->type == TOKEN_FUNCTION_CALL)
	{
		result->children[ONLY_CHILD] = buildASTFunctions_functionCall(&currentNode);
	}
	// in the future add support to more built-in functions or custom functions

	return result;
}


ASTNode* buildASTFunctions_functionCall(node** node)
{
	
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



