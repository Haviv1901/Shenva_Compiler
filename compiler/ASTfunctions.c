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


	ASTNode* result = createNewASTnode(currentToken); // PRINT token node


	if(currentToken->type == PRINT)
	{
		result->children[ONLY_CHILD] = buildASTFunctions_print(&currentNode);
	}
	// in the future add support to more built-in functions or custom functions

	return result;
}

ASTNode* buildASTFunctions_print(struct node** curr)
{
	struct node* currentNode = (*curr)->next->next; // current node = first token inside the parenthesis
	Token* currentToken = currentNode->data;

	return buildASTNumeric(&currentNode); // currently only possible to have numeric expression inside the print function

}