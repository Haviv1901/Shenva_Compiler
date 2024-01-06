#include "ASTconditions.h"


/*
buildASTconditions: this function will build a condition branch
input: the token list
output: the condition branch
*/
ASTNode* buildASTConditions(struct node** curr)
{
	Token* tok = (*curr)->data;
	struct node* node = NULL;
	ASTNode* result = createNewASTnode((Token*)(*curr)->data);//creating the IF node
	*curr = (*curr)->next;
	result->children[0] = buildASTNumeric(curr);//making the condition in child 1 (0)
	*curr = (*curr)->next;//going to the openBracket
	node = beracketEqualizer(*curr);
	*curr = (*curr)->next;//going into the code
	result->children[1] = buildTree(curr);//making the numeric tree there
	*curr = node;//getting the newline token after the close bracket
	*curr = (*curr)->next;//going to the next
	if (*curr != NULL && ((Token*)(*curr)->data)->type == TOKEN_ELSE)
	{
		result->children[2] = createNewASTnode((Token*)(*curr)->data);//making else
		*curr = (*curr)->next;
		tok = (*curr)->data;
		if (tok->type == TOKEN_IF)// in case of else if
		{
			result->children[2]->children[0] = buildASTConditions(curr);
		}
		else// in case of a virgin else
		{
			*curr = (*curr)->next;
			tok = (*curr)->data;
			node = beracketEqualizer(*curr);
			*curr = (*curr)->next;
			result->children[2]->children[0] = buildTree(curr);
			*curr = node;

		}
	}
	return result;

}


/*
bracketEqualizer: this function will equalize a bracket on the token list, and return the token after the last one
input: the token list
output: a pointer to the token after the last right bracket
*/
struct node* beracketEqualizer(struct node* curr)
{
	int equalizer = 0;
	struct node* node = curr;
	do
	{
		if (((Token*)node->data)->type == TOKEN_LBRACK)//numeric equalizing
		{
			equalizer += 1;
		}

		if (((Token*)node->data)->type == TOKEN_RBRACK)
		{
			equalizer -= 1;
		}
		node = node->next;
	} while (equalizer != 0);
	return node;
}


