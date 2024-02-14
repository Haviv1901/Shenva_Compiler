#include "TokenGetter.h"
#include "llist.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#ifndef LOGMANAGER_H
#include "logManager.h"
#endif


float extractDecimal(FILE* file)
{
	float decValue = 0, calcFloat = 0, divisor = 10;

	bool isNegative = false;

	char charFromFile = fgetc(file); // skip the spcace
	charFromFile = fgetc(file);// get the next number from the file
	if (charFromFile == '-')
	{
		isNegative = true;
		charFromFile = fgetc(file);
	}
	charFromFile -= '0';

	calcFloat = charFromFile;
	decValue += calcFloat;
	while (true)
	{
		charFromFile = fgetc(file); // skip the space

		if (charFromFile == DOT_CHARACTER)
		{
			break;
		}

		decValue *= 10;
		calcFloat = charFromFile - '0';
		decValue += calcFloat;
	}
	while (charFromFile = fgetc(file))
	{
		if (charFromFile == NEW_LINE_CHARACTER || charFromFile == ' ')
		{
			break;
		}

		calcFloat = charFromFile - '0';
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


int extractNumber(FILE* file)
{
	int numValue = 0;

	bool isNegative = false;

	char charFromFile = fgetc(file); // skip the spcace
	charFromFile = fgetc(file);// get the next number from the file
	if (charFromFile == '-')
	{
		isNegative = true;
		charFromFile = fgetc(file);
	}
	charFromFile -= '0';


	numValue += charFromFile;
	while (charFromFile = fgetc(file))
	{
		if (charFromFile == NEW_LINE_CHARACTER)
		{
			break;
		}

		numValue *= 10;
		numValue += charFromFile - '0';
	}

	if (isNegative)
	{
		numValue *= -1;
	}


	return numValue;
}


char* extractIdentifier(FILE* file)
{
	char charFromFile = fgetc(file); // skip the spcace
	char* identifier = calloc(MAX_VARIABLE_SIZE, sizeof(char));
	while (charFromFile = fgetc(file)) // get the identifier
	{
		if (charFromFile == NEW_LINE_CHARACTER)
		{
			break;
		}

		// add c to id
		strncat(identifier, &charFromFile, 1);
	}

	return identifier;
}

void* extractLetter(FILE* file)
{
	char charFromFile = fgetc(file); // skip the spcace
	charFromFile = fgetc(file); // skip the first '
	charFromFile = fgetc(file);
	bool specialCharacter = false;

	char* character = calloc(1, sizeof(char));


	if (charFromFile == '\\')
	{
		specialCharacter = true;
		charFromFile = fgetc(file);
	}


	if (specialCharacter)
	{
		if (charFromFile == 'n')
		{
			*character = '\n';
		}
		else if (charFromFile == 'r')
		{
			*character = '\r';
		}
		else if (charFromFile == 't')
		{
			*character = '\t';
		}
		else if (charFromFile == '\\')
		{
			*character = '\\';
		}
		else if (charFromFile == '\'')
		{
			*character = '\'';
		}
		else if (charFromFile == '\"')
		{
			*character = '\"';
		}
		else if (charFromFile == 'b')
		{
			*character = '\b';
		}
		else if (charFromFile == 'f')
		{
			*character = '\f';
		}
		else
		{
			*character = charFromFile;
		}
	}
	else
	{
		*character = charFromFile;
	}

	charFromFile = fgetc(file); // skip the last '
	return character;
}

/// <summary>
/// function checks if the next token is a left parenthesis, used for indicating if a var is a function call or a var call.
/// </summary>
/// <param name="file"></param>
/// <returns></returns>
bool checkForFunction(FILE* file)
{
    // Save the current position in the file
    long current_position = ftell(file);

    // Initialize a variable to hold each character
    char c;

    // Loop forwards through the file until we find a newline or end of file
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            break;
        }
    }

    // Check if the next character is '6'
    bool isNextChar6 = false;
    if (fgetc(file) == '6')
    {
        isNextChar6 = true;
    }

    // Restore the file position
    fseek(file, current_position, SEEK_SET);

    return isNextChar6;
}


/*
 * extracting tokens from a file.
 * file: FILE*, an opened file
 * ret: llist*, a linked list of tokens
 */
llist* extractToken(FILE* file)
{
	llist* tokenList = llist_create(NULL);
	enum TokenTypes lastVoidType;
	bool isPrintLine = false, isDecLine = false, isDefLine = false;

	bool isEOF = false;
	char charFromfile = 0;

	while (!isEOF) // untill not end of file
	{
		charFromfile = fgetc(file);

		switch (charFromfile)
		{
			case NEW_LINE_CHARACTER:
			case NOTHING_CHARACTER:
			case SPACE_CHARACTER: // if new line or  0 ascci char or space skip.
				continue;
			default:
				break;
		}

		if(charFromfile == EOF)
		{
			isEOF = true;
			continue; // last token before eof is always \n
		}

		Token* token = (Token*)malloc(sizeof(Token));
		switch (charFromfile)
		{
			case TOKEN_NUM: // num
				token->type = TOKEN_NUM;
				token->value = (int*)malloc(sizeof(int));
				*((int*)(token->value)) = extractNumber(file);
				break;

			case TOKEN_DECIMAL: // float number
				token->type = TOKEN_DECIMAL;
				token->value = (float*)malloc(sizeof(float));
				*((float*)(token->value)) = extractDecimal(file);
				break;

			case TOKEN_ADD: // +
			case TOKEN_SUB: // -
			case TOKEN_MUL: // *
			case TOKEN_DIV: // /
			case TOKEN_MODULO: // %
			case TOKEN_LPARN: // (
			case TOKEN_RPARN: // )
				token->type = charFromfile;
				token->value = NULL;
				break;

			case TOKEN_PRINT_INT: // printInt
			case TOKEN_PRINT_CHAR: // printChar
			case TOKEN_PRINT_FLOAT: // printFloat
				token->type = charFromfile;
				lastVoidType = charFromfile;
				token->value = NULL;
				isPrintLine = true;
				break;

			case TOKEN_INPUT_FLOAT: // inputFloat
				token->type = TOKEN_INPUT_FLOAT;
				lastVoidType = TOKEN_INPUT_FLOAT;
				token->value = NULL;
				charFromfile = fgetc(file); // skip the space
				charFromfile = fgetc(file); // skip the space
				charFromfile = fgetc(file); // skip the space
				charFromfile = fgetc(file); // skip the space
				break;

			case TOKEN_INPUT_INT: // intInput
			case TOKEN_INPUT_CHAR: // charInput
				token->type = charFromfile;
				token->value = NULL;
				break;

			case TOKEN_ENDL: // endl
				token->type = TOKEN_ENDL;
				token->value = NULL;
				isPrintLine = false;
				isDecLine = false;
				isDefLine = false;
				break;

			case TOKEN_INT: // int var
			case TOKEN_BOOL: // bool var
			case TOKEN_FLOAT: // float var
				token->type = charFromfile;
				token->value = NULL;
				lastVoidType = charFromfile;
				isDecLine = true;
				break;

			case TOKEN_EQUALS:  // ==
			case TOKEN_NOT_EQUALS: // !=
			case TOKEN_GREATER: // >
			case TOKEN_NOT_GREATER: // !<
			case TOKEN_LESSER: // <
			case TOKEN_NOT_LESSER: // !<
			case TOKEN_GREATER_EQUALS: // >=
			case TOKEN_LESSER_EQUALS: // <=
			case TOKEN_NOT: // !
			case TOKEN_OR: // ||
			case TOKEN_AND: // &&
			case TOKEN_ASSIGN: // =
				token->type = charFromfile;
				token->value = NULL;
				break;

			case TOKEN_VAR: // var
				if(checkForFunction(file))
				{
					token->type = TOKEN_FUNCTION_CALL;
					isDefLine = true;
				}
				else
				{
					token->type = TOKEN_VAR;
				}
				token->value = extractIdentifier(file);
				break;

			case TOKEN_CHAR: // char variable type
				token->type = TOKEN_CHAR;
				token->value = NULL;
				lastVoidType = TOKEN_CHAR;
				isDecLine = true;
				break;

			case TOKEN_LETTER: // single character. ex: 'a'
				token->type = TOKEN_LETTER;
				token->value = extractLetter(file);
				break;

			case TOKEN_IF: // if
			case TOKEN_WHILE: // while
			case TOKEN_FOR: // for
			case TOKEN_ELSE: // else
			case TOKEN_RETURN: // return
			case TOKEN_LBRACK: // {
			case TOKEN_RBRACK: // }
			case TOKEN_DEF: // def
				token->type = charFromfile;
				token->value = NULL;
				if (charFromfile == TOKEN_DEF)
				{
					isDefLine = true;
				}
				break;

			case TOKEN_REFERENCE:
				if (llist_get_last_tok(tokenList)->type == TOKEN_DEREFERENCE)
				{
					llist_pop(tokenList);
					free(token);
					continue;
				}
				else
				{
					token->type = TOKEN_REFERENCE;
					token->value = NULL;
				}
				break;
			case TOKEN_DEREFERENCE:
				if (llist_get_last_tok(tokenList)->type == TOKEN_REFERENCE)
				{
					llist_pop(tokenList);
					free(token);
					continue;
				}
				else
				{
					token->type = TOKEN_DEREFERENCE;
					token->value = NULL;
				}
				break;
			case TOKEN_LIND:
				token->type = TOKEN_LIND;
				token->value = NULL;
				break;
			case TOKEN_RIND:
				token->type = TOKEN_RIND;
				token->value = NULL;
				break;

			case TOKEN_COMMA: // ,
				if (isDefLine || (!isPrintLine && !isDecLine)) 
				{
					token->type = TOKEN_COMMA;
					token->value = NULL;
				}
				else if (isPrintLine)
				{
					token->type = TOKEN_RPARN;
					token->value = NULL;
					llist_append(tokenList, token);
					token = (Token*)malloc(sizeof(Token));
					token->type = lastVoidType;
					token->value = NULL;
					llist_append(tokenList, token);
					token = (Token*)malloc(sizeof(Token));
					token->type = TOKEN_LPARN;
					token->value = NULL;
				}
				else if (isDecLine)
				{
					token->type = lastVoidType;
					token->value = NULL;
				}
				break;

			default: // ERROR
				token->type = TOKEN_ERROR;
				token->value = NULL;
				break;
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
		printf("(var)%s", (char*)(token->value));
	}
	else if (token->type == TOKEN_FUNCTION_CALL)
	{
		printf("(func)%s", (char*)(token->value));
	}
	else if (token->type == TOKEN_ERROR)
	{
		printf("TOKEN_ERROR");
	}
	else if (token->type == TOKEN_FOR)
	{
		printf("for");
	}
	else if (token->type == TOKEN_MODULO)
	{
		printf("%%");
	}
	else if (token->type == TOKEN_COMMA)
	{
		printf(",");
	}
	else if (token->type == TOKEN_WHILE)
	{
		printf("while");
	}
	else if (token->type == TOKEN_DEF)
	{
		printf("def");
	}
	else if (token->type == TOKEN_RETURN)
	{
		printf("return");
	}
	else if (token->type == TOKEN_REFERENCE)
	{
		printf("&");
	}
	else if (token->type == TOKEN_DEREFERENCE)
	{
		printf("^");
	}
	else if (token->type == TOKEN_LIND)
	{
		printf("[");

	}
	else if (token->type == TOKEN_RIND)
	{
		printf("]");
	}
	else
	{
		printf("TOKEN_ERROR");
	}
}
