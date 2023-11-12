#include "TokenGetter.h"

#include <stdlib.h>



/*
 * extracting tokens from a file.
 * file: FILE*, an opened file
 * ret: llist*, a linked list of tokens
 */
llist* extractToken(FILE* file)
{
	llist tokenList = llist_create(NULL);
	char c;

	while ((c = fgetc(file)) != EOF)
	{
		if (c == 10) // if newline
		{
			continue;
		}

		Token* token = (Token*)malloc(sizeof(Token));
		if( c == NUM)
		{
			token->type = NUM;

			c = fgetc(file);
			c = fgetc(file);// get the next number from the file
			c -= '0';

			token->value = (int*)malloc(sizeof(int));
			*((int*)(token->value)) = c;
		}
		else if (c == ADD)
		{
			token->type = ADD;
			token->value = NULL;
		}
		else if (c == SUB)
		{
			token->type = SUB;
			token->value = NULL;
		}
		else if (c == MUL)
		{
			token->type = MUL;
			token->value = NULL;
		}
		else if (c == DIV)
		{
			token->type = DIV;
			token->value = NULL;
		}
		else if (c == LPARN)
		{
			token->type = LPARN;
			token->value = NULL;
		}
		else if (c == RPARN)
		{
			token->type = RPARN;
			token->value = NULL;
		}
		else if (c == PRINT)
		{
			token->type = PRINT;
			token->value = NULL;
		}
		else if (c == ENDL)
		{
			token->type = ENDL;
			token->value = NULL;
		}
		else
		{
			token->type = ERROR;
			token->value = NULL;
		}
		



		llist_append(tokenList, token);
		//llist_add_inorder((void*)(numbers + i), my_list, numcmp);
	}

	return tokenList;

}

/*
 * prints a token to the screen
 * token: Token, a token
 * ret: -
 */
void printToken(Token* token)
{
	if (token->type == NUM)
	{
		printf("%d", *((int*)(token->value)));
	}
	else if (token->type == ADD)
	{
		printf("+");
	}
	else if (token->type == SUB)
	{
		printf("-");
	}
	else if (token->type == MUL)
	{
		printf("*");
	}
	else if (token->type == DIV)
	{
		printf("/");
	}
	else if (token->type == LPARN)
	{
		printf("(");
	}
	else if (token->type == RPARN)
	{
		printf(")");
	}
	else if (token->type == PRINT)
	{
		printf("print");
	}
	else if (token->type == ENDL)
	{
		printf("endl");
	}
	else
	{
		printf("ERROR");
	}
}
