


#include "ASTdeclerations.h"


#include "ASTManager.h"
#include "ASTnumeric.h"


ASTNode* buildASTDeclerations(struct node** curr)
{
	Token* currentToken = (*curr)->data;
	ASTNode* result = NULL;

	if(currentToken->type == TOKEN_INT)
	{
		result = buildASTDeclerationsInt(curr);
		currentToken = (*curr)->data;
	}




	return result;
}

ASTNode* buildASTDeclerationsInt(struct node** curr)
{
	struct node* currentNode = (*curr);
	Token* currentToken = currentNode->data;

	ASTNode* result = createNewASTnode(currentToken); // INT token node
	result->children[0] = createNewASTnode(((Token*)currentNode->next->data)); // ID token node

	if(currentNode->next->next != NULL && ((Token*)(currentNode->next->next->data))->type == ASSIGN)
		// currentNode->next->next is the assign token, if exist
	{
		(*curr) = (*curr)->next->next->next;
		currentToken = (*curr)->data;
		result->children[1] = buildASTNumeric(curr); // currentNode->next->next->next is the number assigned to the variable
		currentToken = (*curr)->data;
	}
	else
	{
		result->children[1] = NULL;
		(*curr) = (*curr)->next;
	}

	return result;
}