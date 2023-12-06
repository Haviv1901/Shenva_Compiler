#include "TokenGetter.h"
#include "llist.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#ifndef LOGMANAGER_H
#include "logManager.h"
#endif



int extractNumber(char charFromfile, FILE* file)
{
	int numValue = 0;

	bool isNegative = false;

	charFromfile = fgetc(file); // skip the space
	charFromfile = fgetc(file);// get the next number from the file
	if (charFromfile == '-')
	{
		isNegative = true;
		charFromfile = fgetc(file);
	}
	charFromfile -= '0';


	numValue += charFromfile;
	while (charFromfile = fgetc(file))
	{
		if (charFromfile == NEW_LINE_CHARACTER)
		{
			break;
		}

		numValue *= 10;
		numValue += charFromfile - '0';
	}

	if (isNegative)
	{
		numValue *= -1;
	}


	return numValue;
}


char* extractIdentifier(char charFromfile, FILE* file)
{
	charFromfile = fgetc(file); // skip the space
	char* identifier = calloc(MAX_VARIABLE_SIZE, sizeof(char));
	while (charFromfile = fgetc(file)) // get the identifier
	{
		if (charFromfile == NEW_LINE_CHARACTER)
		{
			break;
		}

		// add c to id
		strncat(identifier, &charFromfile, 1);
	}

	return identifier;
}

/*
 * extracting tokens from a file.
 * file: FILE*, an opened file
 * ret: llist*, a linked list of tokens
 */
llist* extractToken(FILE* file)
{
	llist* tokenList = llist_create(NULL);
	char charFromfile;

	while ((charFromfile = fgetc(file)) != EOF)
	{
		if (charFromfile == NEW_LINE_CHARACTER) // if newline
		{
			continue;
		}

		Token* token = (Token*)malloc(sizeof(Token));
		if( charFromfile == TOKEN_NUM)
		{
			token->type = TOKEN_NUM;
			token->value = (int*)malloc(sizeof(int));
			*((int*)(token->value)) = extractNumber(charFromfile, file);
		}
		else if (charFromfile == TOKEN_ADD)
		{
			token->type = TOKEN_ADD;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_SUB)
		{
			token->type = TOKEN_SUB;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_MUL)
		{
			token->type = TOKEN_MUL;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_DIV)
		{
			token->type = TOKEN_DIV;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_MODULO)
		{
			token->type = TOKEN_MODULO;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_LPARN)
		{
			token->type = TOKEN_LPARN;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_RPARN)
		{
			token->type = TOKEN_RPARN;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_PRINT_INT)
		{
			token->type = TOKEN_PRINT_INT;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_PRINT_CHAR)
		{
			token->type = TOKEN_PRINT_CHAR;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_ENDL)
		{
			token->type = TOKEN_ENDL;
			token->value = NULL;
		}
		else if(charFromfile == TOKEN_INT)
		{
			token->type = TOKEN_INT;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_ASSIGN)
		{
			token->type = TOKEN_ASSIGN;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_VAR)
		{
			token->type = TOKEN_VAR;

			token->value = extractIdentifier(charFromfile, file);
		}
		else if (charFromfile == TOKEN_CHAR)
		{
			token->type = TOKEN_ENDL;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_CHARACTER)
		{
			token->type = TOKEN_ENDL;
			token->value = NULL;
		}
		else
		{
			token->type = TOKEN_ERROR;
			token->value = NULL;
		}

		llist_append(tokenList, token);
		
	}
	fclose(file);
	return tokenList;

}

/*
 * prints a token to the screen
 * token: Token, a token
 * ret: -
 */
void printToken(Token* token)
{
	if (token->type == TOKEN_NUM)
	{
		printf("%d", *((int*)(token->value)));
	}
	else if (token->type == TOKEN_ADD)
	{
		printf("+");
	}
	else if (token->type == TOKEN_SUB)
	{
		printf("-");
	}
	else if (token->type == TOKEN_MUL)
	{
		printf("*");
	}
	else if (token->type == TOKEN_DIV)
	{
		printf("/");
	}
	else if (token->type == TOKEN_LPARN)
	{
		printf("(");
	}
	else if (token->type == TOKEN_RPARN)
	{
		printf(")");
	}
	else if (token->type == TOKEN_PRINT_INT)
	{
		printf("printInt");
	}
	else if (token->type == TOKEN_PRINT_CHAR)
	{
		printf("printChar");
	}
	else if (token->type == TOKEN_ENDL)
	{
		printf("endl\n");
	}
	else if (token->type == TOKEN_INT)
	{
		printf("int");
	}
	else if (token->type == TOKEN_ASSIGN)
	{
		printf("=");
	}
	else if (token->type == TOKEN_VAR)
	{
		printf("%s", (char*)(token->value));
	}
	else if (token->type == TOKEN_ERROR)
	{
		printf("TOKEN_ERROR");
	}
	else if (token->type == TOKEN_MODULO)
	{
		printf("%%");
	}
	else
	{
		printf("TOKEN_ERROR");
	}
}


