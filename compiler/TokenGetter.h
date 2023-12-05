#pragma once
#ifndef TOKENGETTER_H  
#define TOKENGETTER_H
#include <stdio.h>

#define MAX_VARIABLE_SIZE 256

struct node;
typedef struct node* llist;

enum {NEW_LINE_CHARACTER = 10};

enum TokenTypes {ERROR = '0', NUM = '1', ADD = '2',SUB = '3', 
				 MUL = '4', DIV = '5', LPARN = '6', RPARN = '7', 
				 PRINT = '8', ENDL = '9', MOD = '%',
				 ASSIGN = '=', VAR = 'v', TOKEN_INT = 'i',
				TOKEN_CHAR = 'c', TOKEN_STRING = 's', TOKEN_FLOAT = 'f',
				LETTER = 'l'
};

#endif 

struct Token
{
	enum TokenTypes type;
	void* value;
} typedef Token;




llist* extractToken(FILE* file);
void printToken(Token* token);



