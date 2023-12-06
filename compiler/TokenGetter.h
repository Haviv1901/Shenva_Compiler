#pragma once
#ifndef TOKENGETTER_H  
#define TOKENGETTER_H
#include <stdio.h>

#define MAX_VARIABLE_SIZE 256

struct node;
typedef struct node* llist;

enum {NEW_LINE_CHARACTER = 10};

enum TokenTypes {TOKEN_ERROR = '0', TOKEN_NUM = '1', TOKEN_ADD = '2',TOKEN_SUB = '3', 
				 TOKEN_MUL = '4', TOKEN_DIV = '5', TOKEN_LPARN = '6', TOKEN_RPARN = '7', 
				 TOKEN_PRINT_INT = '8', TOKEN_ENDL = '9', TOKEN_MODULO = '%',
				 TOKEN_ASSIGN = '=', TOKEN_VAR = 'v', TOKEN_INT = 'i',
				TOKEN_CHAR = 'c', TOKEN_STRING = 's', TOKEN_FLOAT = 'f',
				TOKEN_CHARACTER = 'l', TOKEN_PRINT_CHAR = 'h'
};

#endif 

struct Token
{
	enum TokenTypes type;
	void* value;
} typedef Token;




llist* extractToken(FILE* file);
void printToken(Token* token);



