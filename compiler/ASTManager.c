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
	if (((Token*)currentNode->data)->type != TOKEN_ENDL && ((Token*)currentNode->data)->type != TOKEN_RBRACK && ((Token*)currentNode->data)->type != TOKEN_RPARN)
	{
		result = createNewASTnode(NULL);
	}

	// create tokenless node with 2 sons
	// EXPRESSION = 1, NEXT = 0
	// first son ( ->children[EXPRESSION] ) is the next expression.
	// second son ( ->children[NEXT] ) is the current expression.





	if (isExpressionToken(*firstToken) || // numeric value, or a variable 
		(firstToken->type == TOKEN_VAR && ((Token*)currentNode->next->data)->type != TOKEN_ASSIGN))
	{

		currentToken = ((Token*)currentNode->data);
		while (currentNode != NULL && currentToken->type != TOKEN_ENDL) // while not the end of list nor the end of line
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
	else if (firstToken->type == TOKEN_ENDL) // if new line continue
	{
		*FirstNode = (*FirstNode)->next;
		result = buildTree(FirstNode);
	}
	else if(firstToken->type == TOKEN_DEF) // function tokens
	{
		result->children[EXPRESSION] = buildASTFunctions(FirstNode);
		result->children[NEXT] = buildTree(FirstNode);
	}
	else if (firstToken->type == TOKEN_RETURN)
	{
		result->children[EXPRESSION] = createNewASTnode(firstToken);
		*FirstNode = (*FirstNode)->next; 
		result->children[EXPRESSION]->children[LEAF] = buildASTNumeric(FirstNode);// only son: the numeric expresion
		result->children[NEXT] = buildTree(FirstNode);
	}
	else if (isPrintToken(*firstToken)) // if printToken  , in the future we will add function support
	{
		
		int parenthesesEqualizer = 0;

		currentNode = currentNode->next; // skipping the PRINT token
		currentToken = ((Token*)currentNode->data);
		do
		{

			if(currentToken->type == TOKEN_LPARN)
			{
				parenthesesEqualizer++;
			}
			else if (currentToken->type == TOKEN_RPARN)
			{
				parenthesesEqualizer--;
			}


			currentNode = currentNode->next; // take the next node
			if (currentNode != NULL)
			{
				currentToken = ((Token*)currentNode->data); // take the next token
			}
		} while (currentNode != NULL && currentToken->type != TOKEN_ENDL && parenthesesEqualizer != 0);
		// while not the end of list nor the end of the parentheses and not end of line


		// first node is first node in the current expression
		// currentNode is the endl that differs between expressions.
		result->children[EXPRESSION] = buildASTFunctions(FirstNode);  
		result->children[NEXT] = buildTree(&currentNode);
	}
	else if (isVariableToken(*firstToken)) // if variable decleration ie: int , char , float
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
	else if (isConditionOrLoopToken(*firstToken))
	{
		int parenthesesEqualizer = 0;

		currentNode = currentNode->next; 
		currentToken = (currentNode->data);

		if(firstToken->type == TOKEN_FOR)
		{
			result->children[EXPRESSION] = buildASTForLoops(FirstNode);
		}
		else
		{
			result->children[EXPRESSION] = buildASTConditionsOrWhileLoops(FirstNode);
		}

		
		result->children[NEXT] = buildTree(FirstNode);
	}
	else if (firstToken->type == TOKEN_VAR) // if variable id
	{

		result->children[EXPRESSION] = buildASTVariables(FirstNode);


		result->children[NEXT] = buildTree(FirstNode);

	}
	return result;
}


