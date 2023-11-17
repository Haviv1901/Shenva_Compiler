#include "ASTManager.h"


ASTNode* buildTree(struct node** FirstNode)
{
	if (*FirstNode == NULL)
	{
		return NULL;
	}


	struct node* currentNode = *FirstNode;
	ASTNode* result = NULL;
	Token* firstToken = (Token*)(*FirstNode)->data, *currentToken = NULL;


	if (firstToken->type == NUM || firstToken->type == LPARN) // if numeric expression
	{
		result = createNewASTnode(NULL); // create tokenless head with 2 sons
		currentToken = ((Token*)currentNode->data);
		while (currentNode != NULL && currentToken->type != ENDL) // while not the end of list nor the end of line
		{
			currentNode = currentNode->next; // take the next node
			if (currentNode != NULL)
			{
				currentToken = ((Token*)currentNode->data); // take the next token
			}
		}
		result->children[1] = buildASTNumeric(FirstNode); // first son: the numeric expresion
		*FirstNode = currentNode;
		result->children[0] = buildTree(FirstNode); // second son: the continuation of the tree
	}
	else if (firstToken->type == ENDL) // if new line
	{
		result = createNewASTnode(firstToken);
		*FirstNode = (*FirstNode)->next;
		result->children[0] = buildTree(FirstNode);
	}
	else if (firstToken->type == PRINT) // if print  , in the future we will add function support
	{
		int parenthesesEqualizer = 0;
		result = createNewASTnode(firstToken); // create first node with PRINT token

		currentToken = ((Token*)currentNode->data);
		while (currentNode != NULL && currentToken->type != RPARN) // while not the end of list nor the end of the parentheses
		{

			if(currentToken->type == LPARN)
			{
				parenthesesEqualizer++;
			}
			else if (currentToken->type == RPARN)
			{
				parenthesesEqualizer--;
			}

			currentNode = currentNode->next; // take the next node
			if (currentNode != NULL)
			{
				currentToken = ((Token*)currentNode->data); // take the next token
			}
		}

		if(currentNode != NULL && parenthesesEqualizer == 0) // current node is the end of the parentheses and make sure that the parentheses are balanced
		{
			result->children[1] = buildASTNumeric(FirstNode); // first son: the function expresion
			*FirstNode = currentNode;
			result->children[0] = buildASTFunction(FirstNode); // second son: the continuation of the tree
		}
		else // end of list or paranthesis unbalanceed (Error)
		{
			return NULL;
		}










		//*FirstNode = (*FirstNode)->next;
		//firstToken = (Token*)(*FirstNode)->data;
		//currentNode = *FirstNode;
		//currentToken = ((Token*)currentNode->data);
		//result->children[0] = createNewASTnode(firstToken);
		//parenthesesEqualizer--;
		//while (currentToken->type != RPARN || parenthesesEqualizer != 0)
		//{
		//	currentNode = currentNode->next;
		//	currentToken = ((Token*)currentNode->data);
		//	if (currentToken->type == LPARN)
		//	{
		//		parenthesesEqualizer--;
		//	}
		//	else if (currentToken->type == RPARN)
		//	{
		//		parenthesesEqualizer++;
		//	}
		//}
		//currentToken->type = ENDL;
		//*FirstNode = (*FirstNode)->next;
		//result->children[0]->children[0] = buildTree(FirstNode);
		//currentToken->type = RPARN;
		//FirstNode = currentNode;
		//*FirstNode = (*FirstNode)->next;
		//result->children[0]->children[0]->children[0]->children[0] = buildTree(FirstNode);
	}

	return result;
}