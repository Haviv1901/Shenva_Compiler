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

void* extractLetter(char charFromfile, FILE* file)
{

	charFromfile = fgetc(file); // skip the space
	charFromfile = fgetc(file); // skip the first '
	charFromfile = fgetc(file);
	bool specialCharacter = false;

	char* character = calloc(1, sizeof(char));


	if (charFromfile == '\\')
	{
		specialCharacter = true;
		charFromfile = fgetc(file);
	}


	if(specialCharacter)
	{
		if (charFromfile == 'n')
		{
			*character = '\n';
		}
		else if (charFromfile == 'r')
		{
			*character = '\r';
		}
		else if (charFromfile == '\\')
		{
			*character = '\\';
		}
		else if (charFromfile == '\'')
		{
			*character = '\'';
		}
		else if (charFromfile == '\"')
		{
			*character = '\"';
		}
		else if (charFromfile == 'b')
		{
			*character = '\b';
		}
		else if (charFromfile == 'f')
		{
			*character = '\f';
		}
		else
		{
			*character = charFromfile;
		}
	}
	else
	{
		*character = charFromfile;
	}

	charFromfile = fgetc(file); // skip the last '
	return character;
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
		if( charFromfile == NUM)
		{
			token->type = NUM;
			token->value = (int*)malloc(sizeof(int));
			*((int*)(token->value)) = extractNumber(charFromfile, file);
		}
		else if (charFromfile == ADD)
		{
			token->type = ADD;
			token->value = NULL;
		}
		else if (charFromfile == SUB)
		{
			token->type = SUB;
			token->value = NULL;
		}
		else if (charFromfile == MUL)
		{
			token->type = MUL;
			token->value = NULL;
		}
		else if (charFromfile == DIV)
		{
			token->type = DIV;
			token->value = NULL;
		}
		else if (charFromfile == MOD)
		{
			token->type = MOD;
			token->value = NULL;
		}
		else if (charFromfile == LPARN)
		{
			token->type = LPARN;
			token->value = NULL;
		}
		else if (charFromfile == RPARN)
		{
			token->type = RPARN;
			token->value = NULL;
		}
		else if (charFromfile == PRINT)
		{
			token->type = PRINT;
			token->value = NULL;
		}
		else if (charFromfile == ENDL)
		{
			token->type = ENDL;
			token->value = NULL;
		}
		else if(charFromfile == TOKEN_INT)
		{
			token->type = TOKEN_INT;
			token->value = NULL;
		}
		else if (charFromfile == ASSIGN)
		{
			token->type = ASSIGN;
			token->value = NULL;
		}
		else if (charFromfile == VAR)
		{
			token->type = VAR;
			token->value = extractIdentifier(charFromfile, file);;
		}
		else if (charFromfile == TOKEN_CHAR)
		{
			token->type = TOKEN_CHAR;
			token->value = NULL;
		}
		else if (charFromfile == LETTER)
		{
			token->type = LETTER;
			token->value = extractLetter(charFromfile, file);
		}
		else
		{
			token->type = ERROR;
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
		printf("endl\n");
	}
	else if (token->type == TOKEN_INT)
	{
		printf("int");
	}
	else if (token->type == ASSIGN)
	{
		printf("=");
	}
	else if (token->type == VAR)
	{
		printf("%s", (char*)(token->value));
	}
	else if (token->type == TOKEN_CHAR)
	{
		printf("char");
	}
	else if (token->type == LETTER)
	{
		printf("%c", *((char*)(token->value)));
	}
	else if (token->type == ERROR)
	{
		printf("ERROR");
	}
	else if (token->type == MOD)
	{
		printf("%%");
	}
	else
	{
		printf("ERROR");
	}
}


