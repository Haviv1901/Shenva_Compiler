


#include "ASTdeclerations.h"


#include "ASTManager.h"
#include "ASTnumeric.h"




ASTNode* buildASTVariables(struct node** curr)
{
	Token* currentToken = (*curr)->data;
	ASTNode* result = NULL;

	if(currentToken->type == TOKEN_INT || currentToken->type == TOKEN_CHAR || currentToken->type == TOKEN_FLOAT)
	{
		result = buildASTDeclerationsNumeric(curr);
	}
	else if (currentToken->type == TOKEN_VAR)
	{
		result = buildASTVariablesAssign(curr);
	}

	return result;
}



ASTNode* buildASTVariablesAssign(node** curr)
{

	struct node* currentNode = (*curr);
	Token* currentToken = currentNode->data;

	ASTNode* result = createNewASTnode(currentNode->next->data); // TOKEN_ASSIGN token node

	result->children[0] = createNewASTnode(currentNode->data); // ID token node

	// skip current twice
	(*curr) = (*curr)->next->next;
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