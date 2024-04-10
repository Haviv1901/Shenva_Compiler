


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
		else if ((*curr)->data->type == TOKEN_LIST)
		{
			result->children[1] = buildASTPreMadeListDec(curr);
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


/*
buildASTPreMadeListDec: this function will make a NULL list of the values in the list
input: the token list
output: the branch to the first NULL in the NULL list
*/
ASTNode* buildASTPreMadeListDec(struct node** curr)
{
	ASTNode* result = createNewASTnode(NULL);
	ASTNode* currentNode = result;
	(*curr) = (*curr)->next;
	while ((*curr)->data->type != TOKEN_LIST)//looking for the end
	{
		currentNode->children[ONE_CHILD_NODE] = buildASTNumeric(curr);
		currentNode->children[LEAF] = NULL;
		if ((*curr)->data->type == TOKEN_COMMA)// if there is another expression
		{
			currentNode->children[LEAF] = createNewASTnode(NULL);
			currentNode = currentNode->children[LEAF];
			(*curr) = (*curr)->next;
		}
	}
	(*curr) = (*curr)->next;// going to the next one

	return result;

}






