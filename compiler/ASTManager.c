#include "ASTManager.h"

#include "ASTdeclerations.h"


ASTNode* buildTree(struct node** FirstNode)
{
	if (*FirstNode == NULL)
	{
		return NULL;
	}
	Token* firstToken = (Token*)(*FirstNode)->data, * currentToken = NULL;
	ASTNode* result = NULL;
	struct node* currentNode = *FirstNode;
	if (((Token*)currentNode->data)->type != ENDL)
	{
		result = createNewASTnode(NULL);
	}

	// create tokenless node with 2 sons
	// EXPRESSION = 1, NEXT = 0
	// first son ( ->children[EXPRESSION] ) is the next expression.
	// second son ( ->children[NEXT] ) is the current expression.




	if (firstToken->type == NUM ||
		firstToken->type == LPARN || // if numeric expression
		(firstToken->type == VAR && ((Token*)currentNode->next->data)->type != ASSIGN)) // or a variable
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
		*FirstNode = (*FirstNode)->next;
		result = buildTree(FirstNode);
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
	else if (firstToken->type == TOKEN_INT || firstToken->type == TOKEN_CHAR)
	{
		result->children[EXPRESSION] = buildASTVariables(FirstNode);
		if(result->children[EXPRESSION]->children[1] == NULL)
		{
			*FirstNode = (*FirstNode)->next;
			result->children[NEXT] = buildTree(FirstNode);
		}
		else
		{
			result->children[NEXT] = buildTree(FirstNode);
		}
	}
	else if (firstToken->type == VAR)
	{

		result->children[EXPRESSION] = buildASTVariables(FirstNode);


		result->children[NEXT] = buildTree(FirstNode);



	}
	return result;
}


