#pragma once
#ifndef TOKENGETTER_H  
#define TOKENGETTER_H
#include <stdbool.h>
#include <stdio.h>

#define MAX_VARIABLE_SIZE 256

struct node;
typedef struct node* llist;

enum {NEW_LINE_CHARACTER = 10, DOT_CHARACTER = '.' , SPACE_CHARACTER = ' ', NOTHING_CHARACTER = 0 };

enum TokenTypes {TOKEN_ERROR = '0', TOKEN_NUM = '1', TOKEN_DECIMAL = 'd', TOKEN_ADD = '2', TOKEN_SUB = '3',
				 TOKEN_MUL = '4', TOKEN_DIV = '5', TOKEN_LPARN = '6', TOKEN_RPARN = '7', 
				 TOKEN_PRINT_INT = '8', TOKEN_ENDL = '9', TOKEN_MODULO = '%',
				 TOKEN_ASSIGN = '=', TOKEN_VAR = 'v', TOKEN_INT = 'i',
				 TOKEN_CHAR = 'c', TOKEN_STRING = 's', TOKEN_FLOAT = 'f',
				 TOKEN_LETTER = 'l', TOKEN_PRINT_CHAR = 'h', TOKEN_COMMA = ',',
				 TOKEN_BOOL = 'b', TOKEN_PRINT_FLOAT = 'n', TOKEN_INPUT_INT = 'j', TOKEN_INPUT_FLOAT = 'm',
				 TOKEN_INPUT_CHAR = 'L', TOKEN_EQUALS = 'S', TOKEN_NOT_EQUALS = 'U', TOKEN_GREATER = 'G', TOKEN_NOT_GREATER = 'H',
				 TOKEN_LESSER = 'K', TOKEN_NOT_LESSER = 'M', TOKEN_GREATER_EQUALS = 'N', TOKEN_LESSER_EQUALS = 'O',
				 TOKEN_NOT = '!', TOKEN_OR = 'o', TOKEN_AND = 'a', TOKEN_IF = 'I', TOKEN_ELSE = 'E', TOKEN_LBRACK = '{',
				 TOKEN_RBRACK = '}', TOKEN_WHILE = 'w', TOKEN_FOR = 'F', TOKEN_DEF = 'D', TOKEN_RETURN = 'r',
				 TOKEN_FUNCTION_CALL = 'v'
};

#endif 

struct Token
{
	enum TokenTypes type;
	void* value;
} typedef Token;




llist* extractToken(FILE* file);
void printToken(Token* token);

int extractNumber(FILE* file);
bool checkForFunction(FILE* file);
char* extractIdentifier(FILE* file);
void* extractLetter(FILE* file);



