


#include "ASTdeclerations.h"


#include "ASTManager.h"
#include "ASTnumeric.h"




ASTNode* buildASTVariables(struct node** curr)
{
	Token* currentToken = (*curr)->data;
	ASTNode* result = NULL;

	if(currentToken->type == TOKEN_INT || currentToken->type == TOKEN_CHAR || currentToken->type == TOKEN_FLOAT || currentToken->type == TOKEN_BOOL)
	{
		result = buildASTDeclerationsNumeric(curr);
	}
	else
	{
		result = buildASTVariablesAssign(curr);
	}

	return result;
}



ASTNode* buildASTVariablesAssign(node** curr)
{

	struct node* currentNode = (*curr);
	Token* currentToken = currentNode->data;

	ASTNode* result = createNewASTnode(is_assign_line(curr)); // TOKEN_ASSIGN token node

	result->children[0] = parseLast(curr); // ID token node

	// skip current twice
	(*curr) = (*curr)->next;
	result->children[1] = buildASTNumeric(curr); // currentNode->next->next is the number assigned to the variable

	return result;


}


ASTNode* buildASTDeclerationsNumeric(struct node** curr)
{
	struct node* currentNode = (*curr);
	Token* currentToken = currentNode->data;

	ASTNode* result = createNewASTnode(currentToken); // INT token node
	result->children[0] = createNewASTnode(((Token*)currentNode->next->data)); // ID token node

	if(currentNode->next->next != NULL && ((Token*)(currentNode->next->next->data))->type == TOKEN_ASSIGN)
		// currentNode->next->next is the assign token, if exist
	{
		(*curr) = (*curr)->next->next->next;
		result->children[1] = buildASTNumeric(curr); // currentNode->next->next->next is the number assigned to the variable
	}
	else
	{
		result->children[1] = NULL;
		(*curr) = (*curr)->next;
	}

	return result;
}