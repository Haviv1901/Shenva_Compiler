


#include "ASTdeclerations.h"


#include "ASTManager.h"
#include "ASTnumeric.h"




ASTNode* buildASTVariables(struct node** curr)
{
	Token* currentToken = (*curr)->data;
	ASTNode* result = NULL;

	if(isVarDeclerationToken(*currentToken))
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

/*
buildASTListDeclerationBranch: this function will build the right side of the decleration in a pointer-list decleration
input: the current token, and the type of the decleration
output: the right side branch
*/
ASTNode* buildASTListDeclerationBranch(struct node** curr, Token* decTypeTok)
{
	ASTNode* result = NULL;
	(*curr)->data->type = TOKEN_LIST_SIZE_DECLERATION;//using a token list size decleration, to be more efficient
	result = createNewASTnode((*curr)->data);
	(*curr) = (*curr)->next;
	result->children[LEAF] = createNewASTnode((*curr)->data);// we know its only ont
	(*curr) = (*curr)->next->next;
	return result;
}



ASTNode* buildASTDeclerationsNumeric(struct node** curr)
{
	struct node* currentNode = (*curr);
	Token* currentToken = currentNode->data;

	ASTNode* result = createNewASTnode(currentToken); // INT token node
	result->children[0] = createNewASTnode((currentNode->next->data)); // ID token node

	if(currentNode->next->next != NULL && ((Token*)(currentNode->next->next->data))->type == TOKEN_ASSIGN)
		// currentNode->next->next is the assign token, if exist
	{
		(*curr) = (*curr)->next->next->next;
		if ((*curr)->data->type == TOKEN_LIND)
		{
			result->children[1] = buildASTListDeclerationBranch(curr, currentToken); // currentNode->next->next->next is the left index of the list
		}
		else
		{
			result->children[1] = buildASTNumeric(curr); // currentNode->next->next->next is the number assigned to the variable
		}
	}
	else
	{
		result->children[1] = NULL;
		(*curr) = (*curr)->next;
	}

	return result;
}