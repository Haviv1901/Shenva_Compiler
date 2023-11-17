#include "ASTManager.h"


ASTNode* buildTree(struct node** FirstNode)
{
	if (*FirstNode == NULL)
	{
		return NULL;
	}


	struct node* currentNode = *FirstNode;
	ASTNode* result = createNewASTnode(NULL);
	// create tokenless node with 2 sons
	// EXPRESSION = 1, NEXT = 0
	// first son ( ->children[EXPRESSION] ) is the next expression.
	// second son ( ->children[NEXT] ) is the current expression.

	Token* firstToken = (Token*)(*FirstNode)->data, *currentToken = NULL;


	if (firstToken->type == NUM || firstToken->type == LPARN) // if numeric expression
	{
		currentToken = ((Token*)currentNode->data);
		while (currentNode != NULL && currentToken->type != ENDL) // while not the end of list nor the end of line
		{
			currentNode = currentNode->next; // take the next node
			if (currentNode != NULL)
			{
				currentToken = ((Token*)currentNode->data); // take the next token
			}
		}
		result->children[EXPRESSION] = buildASTNumeric(FirstNode); // first son: the numeric expresion
		result->children[NEXT] = buildTree(&currentNode); // second son: the continuation of the tree
	}
	else if (firstToken->type == ENDL) // if new line continue
	{
		result = buildTree(&(*FirstNode)->next);
	}
	else if (firstToken->type == PRINT) // if print  , in the future we will add function support
	{
		
		int parenthesesEqualizer = 0;

		currentNode = currentNode->next; // skipping the PRINT token
		currentToken = ((Token*)currentNode->data);
		do
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
		} while (currentNode != NULL && currentToken->type != ENDL && parenthesesEqualizer != 0);
		// while not the end of list nor the end of the parentheses and not end of line


		// first node is first node in the current expression
		// currentNode is the endl that differs between expresions.
		result->children[EXPRESSION] = buildASTFunctions(FirstNode);  
		result->children[NEXT] = buildTree(&currentNode);
	}
	return result;
}