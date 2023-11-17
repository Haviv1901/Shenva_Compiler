#include "ASTManager.h"


ASTNode* buildTree(struct node** curr)
{
	if (*curr == NULL)
	{
		return NULL;
	}
	struct node* nodeHolder = *curr;
	ASTNode* result = NULL;
	Token* temp = (Token*)(*curr)->data, * holderTok = NULL;
	if (temp->type == NUM || temp->type == LPARN)
	{
		result = createNewASTnode(NULL);
		holderTok = ((Token*)nodeHolder->data);
		while (nodeHolder != NULL && holderTok->type != ENDL)
		{
			nodeHolder = nodeHolder->next;
			if (nodeHolder != NULL)
			{
				holderTok = ((Token*)nodeHolder->data);
			}
		}
		result->children[1] = buildASTNumeric(curr);
		*curr = nodeHolder;
		result->children[0] = buildTree(curr);
	}
	else if (temp->type == ENDL)
	{
		result = createNewASTnode(temp);
		*curr = (*curr)->next;
		result->children[0] = buildTree(curr);
	}
	else if (temp->type == PRINT)
	{
		int parenthasisEqualizer = 0;
		result = createNewASTnode(temp);
		*curr = (*curr)->next;
		temp = (Token*)(*curr)->data;
		nodeHolder = *curr;
		holderTok = ((Token*)nodeHolder->data);
		result->children[0] = createNewASTnode(temp);
		parenthasisEqualizer--;
		while (holderTok->type != RPARN || parenthasisEqualizer != 0)
		{
			nodeHolder = nodeHolder->next;
			holderTok = ((Token*)nodeHolder->data);
			if (holderTok->type == LPARN)
			{
				parenthasisEqualizer--;
			}
			else if (holderTok->type == RPARN)
			{
				parenthasisEqualizer++;
			}
		}
		holderTok->type = ENDL;
		*curr = (*curr)->next;
		result->children[0]->children[0] = buildTree(curr);
		holderTok->type = RPARN;
		curr = nodeHolder;
		*curr = (*curr)->next;
		result->children[0]->children[0]->children[0]->children[0] = buildTree(curr);
	}

	return result;
}