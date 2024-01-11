#include "TokenGetter.h"
#include "llist.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#ifndef LOGMANAGER_H
#include "logManager.h"
#endif


float extractDecimal(char charFromfile, FILE* file)
{
	float decValue = 0, calcFloat = 0, divisor = 10;

	bool isNegative = false;

	charFromfile = fgetc(file); // skip the space
	charFromfile = fgetc(file);// get the next number from the file
	if (charFromfile == '-')
	{
		isNegative = true;
		charFromfile = fgetc(file);
	}
	charFromfile -= '0';

	calcFloat = charFromfile;
	decValue += calcFloat;
	while (true)
	{
		charFromfile = fgetc(file); // skip the space

		if (charFromfile == DOT_CHARACTER)
		{
			break;
		}

		decValue *= 10;
		calcFloat = charFromfile - '0';
		decValue += calcFloat;
	}
	while (charFromfile = fgetc(file))
	{
		if (charFromfile == NEW_LINE_CHARACTER)
		{
			break;
		}

		calcFloat = charFromfile - '0';
		calcFloat /= divisor;
		divisor *= 10;
		decValue += calcFloat;
	}




	if (isNegative)
	{
		decValue *= -1;
	}


	return decValue;
}


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


	if (specialCharacter)
	{
		if (charFromfile == 'n')
		{
			*character = '\n';
		}
		else if (charFromfile == 'r')
		{
			*character = '\r';
		}
		else if (charFromfile == 't')
		{
			*character = '\t';
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
	enum TokenTypes lastVoidType;
	bool isPrintLine = false, isDecLine = false;
	while ((charFromfile = fgetc(file)) != EOF)
	{
		if (charFromfile == NEW_LINE_CHARACTER) // if newline
		{
			continue;
		}

		Token* token = (Token*)malloc(sizeof(Token));
		if (charFromfile == TOKEN_NUM)
		{
			token->type = TOKEN_NUM;
			token->value = (int*)malloc(sizeof(int));
			*((int*)(token->value)) = extractNumber(charFromfile, file);
		}
		else if (charFromfile == TOKEN_DECIMAL)
		{
			token->type = TOKEN_DECIMAL;
			token->value = (float*)malloc(sizeof(float));
			*((float*)(token->value)) = extractDecimal(charFromfile, file);
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
			lastVoidType = TOKEN_PRINT_INT;
			token->value = NULL;
			isPrintLine = true;
		}
		else if (charFromfile == TOKEN_PRINT_CHAR)
		{
			token->type = TOKEN_PRINT_CHAR;
			lastVoidType = TOKEN_PRINT_CHAR;
			token->value = NULL;
			isPrintLine = true;
		}
		else if (charFromfile == TOKEN_PRINT_FLOAT)
		{
			token->type = TOKEN_PRINT_FLOAT;
			lastVoidType = TOKEN_PRINT_FLOAT;
			token->value = NULL;
			isPrintLine = true;
		}
		else if (charFromfile == TOKEN_INPUT_FLOAT)
		{
			token->type = TOKEN_INPUT_FLOAT;
			lastVoidType = TOKEN_INPUT_FLOAT;
			token->value = NULL;
			charFromfile = fgetc(file); // skip the space
			charFromfile = fgetc(file); // skip the space
			charFromfile = fgetc(file); // skip the space
			charFromfile = fgetc(file); // skip the space
		}
		else if (charFromfile == TOKEN_INPUT_INT)
		{
			token->type = TOKEN_INPUT_INT;
			token->value = NULL;
			charFromfile = fgetc(file); // skip the space
			charFromfile = fgetc(file); // skip the space
			charFromfile = fgetc(file); // skip the space
			charFromfile = fgetc(file); // skip the space
		}
		else if (charFromfile == TOKEN_INPUT_CHAR)
		{
			token->type = TOKEN_INPUT_CHAR;
			token->value = NULL;
			charFromfile = fgetc(file); // skip the space
			charFromfile = fgetc(file); // skip the space
			charFromfile = fgetc(file); // skip the space
			charFromfile = fgetc(file); // skip the space

		}
		else if (charFromfile == TOKEN_ENDL)
		{
			token->type = TOKEN_ENDL;
			token->value = NULL;
			isPrintLine = false;
			isDecLine = false;
		}
		else if (charFromfile == TOKEN_INT)
		{
			token->type = TOKEN_INT;
			token->value = NULL;
			lastVoidType = TOKEN_INT;
			isDecLine = true;
		}
		else if (charFromfile == TOKEN_BOOL)
		{
			token->type = TOKEN_BOOL;
			token->value = NULL;
			lastVoidType = TOKEN_BOOL;
			isDecLine = true;
		}
		else if (charFromfile == TOKEN_FLOAT)
		{
			token->type = TOKEN_FLOAT;
			token->value = NULL;
			lastVoidType = TOKEN_FLOAT;
			isDecLine = true;
		}
		else if (charFromfile == TOKEN_EQUALS)
		{
			token->type = TOKEN_EQUALS;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_NOT_EQUALS)
		{
			token->type = TOKEN_NOT_EQUALS;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_GREATER)
		{
			token->type = TOKEN_GREATER;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_NOT_GREATER)
		{
			token->type = TOKEN_NOT_GREATER;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_LESSER)
		{
			token->type = TOKEN_LESSER;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_NOT_LESSER)
		{
			token->type = TOKEN_NOT_LESSER;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_GREATER_EQUALS)
		{
			token->type = TOKEN_GREATER_EQUALS;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_LESSER_EQUALS)
		{
			token->type = TOKEN_LESSER_EQUALS;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_NOT)
		{
			token->type = TOKEN_NOT;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_OR)
		{
			token->type = TOKEN_OR;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_AND)
		{
			token->type = TOKEN_AND;
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
		else if (charFromfile == TOKEN_CHAR) // char variable type
		{
			token->type = TOKEN_CHAR;
			token->value = NULL;
			lastVoidType = TOKEN_CHAR;
			isDecLine = true;
		}
		else if (charFromfile == TOKEN_LETTER) // single character. ex: 'a'
		{
			token->type = TOKEN_LETTER;
			token->value = extractLetter(charFromfile, file);
		}
		else if (charFromfile == TOKEN_LETTER) // single character. ex: 'a'
		{
			token->type = TOKEN_LETTER;
			token->value = extractLetter(charFromfile, file);
		}
		else if (charFromfile == TOKEN_IF)
		{
			token->type = TOKEN_IF;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_WHILE)
		{
			token->type = TOKEN_WHILE;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_ELSE)
		{
			token->type = TOKEN_ELSE;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_LBRACK)
		{
			token->type = TOKEN_LBRACK;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_RBRACK)
		{
			token->type = TOKEN_RBRACK;
			token->value = NULL;
		}
		else if (charFromfile == TOKEN_COMMA)
		{
			if (isPrintLine)
			{
				token->type = TOKEN_RPARN;
				token->value = NULL;
				llist_append(tokenList, token);
				token = (Token*)malloc(sizeof(Token));
				token->type = token->type = lastVoidType;
				token->value = NULL;
				llist_append(tokenList, token);
				token = (Token*)malloc(sizeof(Token));
				token->type = token->type = TOKEN_LPARN;
				token->value = NULL;
			}
			else if (isDecLine)
			{
				token->type = lastVoidType;
				token->value = NULL;
			}


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
	else if (token->type == TOKEN_DECIMAL)
	{
		printf("%f", *((float*)(token->value)));
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
	else if (token->type == TOKEN_INPUT_CHAR)
	{
		printf("inputChar");
	}
	else if (token->type == TOKEN_INPUT_FLOAT)
	{
		printf("inputFloat");
	}
	else if (token->type == TOKEN_INPUT_INT)
	{
		printf("inputInt");
	}
	else if (token->type == TOKEN_PRINT_INT)
	{
		printf("printInt");
	}
	else if (token->type == TOKEN_PRINT_CHAR)
	{
		printf("printChar");
	}
	else if (token->type == TOKEN_PRINT_FLOAT)
	{
		printf("printFloat");
	}
	else if (token->type == TOKEN_ENDL)
	{
		printf("endl\n");
	}
	else if (token->type == TOKEN_NOT)
	{
		printf("!");
	}
	else if (token->type == TOKEN_EQUALS)
	{
		printf("==");
	}
	else if (token->type == TOKEN_NOT_EQUALS)
	{
		printf("!=");
	}
	else if (token->type == TOKEN_GREATER)
	{
		printf(">");
	}
	else if (token->type == TOKEN_NOT_GREATER)
	{
		printf("!>");
	}
	else if (token->type == TOKEN_LESSER)
	{
		printf("<");
	}
	else if (token->type == TOKEN_NOT_LESSER)
	{
		printf("!<");
	}
	else if (token->type == TOKEN_GREATER_EQUALS)
	{
		printf(">=");
	}
	else if (token->type == TOKEN_LESSER_EQUALS)
	{
		printf("<=");
	}
	else if (token->type == TOKEN_OR)
	{
		printf("or");
	}
	else if (token->type == TOKEN_AND)
	{
		printf("and");
	}
	else if (token->type == TOKEN_INT)
	{
		printf("int");
	}
	else if (token->type == TOKEN_BOOL)
	{
		printf("bool");
	}
	else if (token->type == TOKEN_FLOAT)
	{
		printf("float");
	}
	else if (token->type == TOKEN_ASSIGN)
	{
		printf("=");
	}
	else if (token->type == TOKEN_CHAR)
	{
		printf("char");
	}
	else if (token->type == TOKEN_LETTER)
	{
		printf("%c", *((char*)(token->value)));
	}
	else if (token->type == TOKEN_IF)
	{
		printf("if");
	}
	else if (token->type == TOKEN_ELSE)
	{
		printf("else");
	}
	else if (token->type == TOKEN_LBRACK)
	{
		printf("{");
	}
	else if (token->type == TOKEN_RBRACK)
	{
		printf("}");
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
	else if (token->type == TOKEN_WHILE)
	{
		printf("while");
	}
	else
	{
		printf("TOKEN_ERROR");
	}
}
