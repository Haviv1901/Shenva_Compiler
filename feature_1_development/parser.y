%error-verbose
%{
#include <stdio.h>
int yylineno;  
FILE* errorFile;
%}


%union 
{
    int num;
    char *str;  // Add a string field
}
%token NUM LETTER DECIMAL BOOL
%token ADD SUB MUL DIV MOD
%token LPAREN RPAREN
%token EQUALS NOTEQUALS GREATER NOTGREATER LESSER NOTLESSER GREATEREQUALS LESSEREQUALS NOT OR AND
%token IF ELSE LBRACK RBRACK WHILE FOR
%token <str> ERROR
%token PRINTINT PRINTCHAR PRINTFLOAT COMMA INTINPUT FLOATINPUT CHARINPUT
%token TRUE FALSE
%token ENDL
%token ASSIGN
%token INT CHAR FLOAT
%token VAR
%token ADDEQ SUBEQ MULEQ DIVEQ MODEQ
%left ADD SUB
%left MUL DIV MOD
%left EQUALS NOTEQUALS GREATER NOTGREATER LESSER NOTLESSER GREATEREQUALS LESSEREQUALS OR AND
%nonassoc NOT ELSE
%nonassoc LOWER_THAN_ELSE
%%


program : blocks
        ;

blocks : block
        | blocks block
        ;
		   
block : statement
		| condition
		;

condition : IF LPAREN expression RPAREN empty_space LBRACK blocks RBRACK ENDL else_part
		  |	WHILE LPAREN expression RPAREN empty_space LBRACK blocks RBRACK ENDL
		  | FOR LPAREN boolean_expression COMMA decleration_list RPAREN empty_space LBRACK blocks RBRACK ENDL
          ;

else_part : ELSE empty_space LBRACK blocks RBRACK ENDL
          | ELSE condition %prec LOWER_THAN_ELSE
          | /* empty, if there's no else part */
          ;

empty_space : ENDL
            | empty_space ENDL
            ;
		
statement : PRINTINT LPAREN expression_list RPAREN ENDL { /* Handle print statement */ }
		  |  PRINTCHAR LPAREN expression_list RPAREN  ENDL { /* Handle print statement */ }
		  |  PRINTFLOAT LPAREN expression_list RPAREN ENDL { /* Handle print statement */ }
		  | expression ENDL
          | declaration ENDL
          | assignment ENDL
		  | ENDL
          | ERROR {fprintf(errorFile, "syntax error, unrecognized \"%s\" in the code (line %d)\n", $1, yylineno);}
          ;
		
declaration : INT decleration_list
            | CHAR decleration_list
			| FLOAT decleration_list
			| BOOL decleration_list
            ;

decleration_list : VAR
                 | VAR ASSIGN expression 
                 | decleration_list COMMA VAR
                 | decleration_list COMMA VAR ASSIGN expression
                 ;

expression_list : expression
               | expression_list COMMA expression
               ;
			   
			   
assignment : VAR ASSIGN expression
			| VAR ADDEQ expression
			| VAR SUBEQ expression
			| VAR MULEQ expression
			| VAR DIVEQ expression
			| VAR MODEQ expression
           ;

input : INTINPUT 
	  | FLOATINPUT 
	  | CHARINPUT 
	  ;


expression: boolean_expression
	| numeric_expression
	;



boolean_expression : numeric_expression EQUALS numeric_expression
	| numeric_expression NOTEQUALS numeric_expression
	| numeric_expression GREATER numeric_expression
	| numeric_expression NOTGREATER numeric_expression
	| numeric_expression LESSER numeric_expression
	| numeric_expression NOTLESSER numeric_expression
	| numeric_expression GREATEREQUALS numeric_expression
	| numeric_expression LESSEREQUALS numeric_expression
	| LPAREN boolean_expression RPAREN
	| boolean_expression OR boolean_expression
	| boolean_expression AND boolean_expression
	| NOT boolean_expression
	;



numeric_expression : NUM
		   | VAR
		   | TRUE
		   | FALSE
		   | LETTER
		   | DECIMAL
		   | input LPAREN RPAREN
           | numeric_expression ADD numeric_expression { /* Handle addition here */ }
           | numeric_expression SUB numeric_expression { /* Handle subtraction here */ }
           | numeric_expression MUL numeric_expression { /* Handle multiplication here */ }
           | numeric_expression DIV numeric_expression { /* Handle division here */ }
		   | numeric_expression MOD numeric_expression {}
           | LPAREN numeric_expression RPAREN   { /* Handle parentheses here */ }
		   | error 
           ;


%%

int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_code_file output_file\n", argv[0]);
        return 1;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    FILE* outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }
	errorFile = fopen("errors.txt", "w");
    if (!errorFile) 
	{
        perror("Error opening error file");
        fclose(inputFile);
		fclose(outputFile);
        return 1;
    }
	yylineno = 1;
    set_input_file(inputFile);
    set_output_file(outputFile);
	
    yyparse();

    fclose(inputFile);
    fclose(outputFile);
	fclose(errorFile);
    return 0;
}

int yyerror(char *msg) 
{
	int i = 0;
	for (i = 0; i < strlen(msg); i++)
	{
		if (strncmp(msg + i, "ASSIGN", 6) == 0)
		{
			fprintf(errorFile, "\"=\"");
			i += 5;
		}
		else if (strncmp(msg + i, "CHAR", 4) == 0)
		{
			fprintf(errorFile, "char");
			i += 3;
		}
				else if (strncmp(msg + i, "FLOAT", 5) == 0)
		{
			fprintf(errorFile, "float");
			i += 4;
		}
		else if (strncmp(msg + i, "LETTER", 6) == 0)
		{
			fprintf(errorFile, "letter");
			i += 5;
		}
		else if (strncmp(msg + i, "FOR", 3) == 0)
		{
			fprintf(errorFile, "for");
			i += 2;
		}
		else if (strncmp(msg + i, "ADDEQ", 5) == 0)
		{
			fprintf(errorFile, "\"+=\"");
			i += 4;
		}
		else if (strncmp(msg + i, "SUBEQ", 5) == 0)
		{
			fprintf(errorFile, "\"-=\"");
			i += 4;
		}
		else if (strncmp(msg + i, "INTINPUT", 8) == 0)
		{
			fprintf(errorFile, "\"-=\"");
			i += 7;
		}
		else if (strncmp(msg + i, "FLOATINPUT",10) == 0)
		{
			fprintf(errorFile, "\"-=\"");
			i += 9;
		}
		else if (strncmp(msg + i, "CHARINPUT", 9) == 0)
		{
			fprintf(errorFile, "\"-=\"");
			i += 8;
		}
		else if (strncmp(msg + i, "MULEQ", 5) == 0)
		{
			fprintf(errorFile, "\"*=\"");
			i += 4;
		}
		else if (strncmp(msg + i, "DIVEQ", 5) == 0)
		{
			fprintf(errorFile, "\"//=\"");
			i += 4;
		}
		else if (strncmp(msg + i, "MODEQ", 5) == 0)
		{
			fprintf(errorFile, "\"%%=\"");
			i += 4;
		}
		else if (strncmp(msg + i, "ADD", 3) == 0)
		{
			fprintf(errorFile, "\"+\"");
			i += 2;
		}
		else if (strncmp(msg + i, "SUB", 3) == 0)
		{
			fprintf(errorFile, "\"-\"");
			i += 2;
		}
		else if (strncmp(msg + i, "MUL", 3) == 0)
		{
			fprintf(errorFile, "\"*\"");
			i += 2;
		}
		else if (strncmp(msg + i, "DIV", 3) == 0)
		{
			fprintf(errorFile, "\"//\"");
			i += 2;
		}
		else if (strncmp(msg + i, "MOD", 3) == 0)
		{
			fprintf(errorFile, "\"%%\"");
			i += 2;
		}
		else if (strncmp(msg + i, "NUM", 3) == 0)
		{
			fprintf(errorFile, "number");
			i += 2;
		}
		else if (strncmp(msg + i, "PRINTFLOAT", 10) == 0)
		{
			fprintf(errorFile, "int");
			i += 9;
		}
		else if (strncmp(msg + i, "INT", 3) == 0)
		{
			fprintf(errorFile, "int");
			i += 2;
		}
		else if (strncmp(msg + i, "VAR", 3) == 0)
		{
			fprintf(errorFile, "variable");
			i += 2;
		}
		else if (strncmp(msg + i, "INT", 3) == 0)
		{
			fprintf(errorFile, "int");
			i += 2;
		}
		else if (strncmp(msg + i, "PRINTINT", 8) == 0)
		{
			fprintf(errorFile, "printInt");
			i += 7;
		}
		else if (strncmp(msg + i, "PRINTCHAR", 8) == 0)
		{
			fprintf(errorFile, "printChar");
			i += 7;
		}
		else if (strncmp(msg + i, "ENDL", 4) == 0)
		{
			fprintf(errorFile, "newline");
			i += 3;
		}
		else if (strncmp(msg + i, "LPAREN", 6) == 0)
		{
			fprintf(errorFile, "\"(\"");
			i += 5;
		}
		else if (strncmp(msg + i, "RPAREN", 6) == 0)
		{
			fprintf(errorFile, "\")\"");
			i += 5;
		}
		else if (strncmp(msg + i, "COMMA", 5) == 0)
		{
			fprintf(errorFile, "\",\"");
			i += 4;
		}
		else if (strncmp(msg + i, "ERROR", 6) == 0)
		{
			fprintf(errorFile, "\"character\"");
			i += 5;
		}
		else if (strncmp(msg + i, "DECIMAL", 7) == 0)
		{
			fprintf(errorFile, "floating point number");
			i += 6;
		}
		else if (strncmp(msg + i, "NOT", 3) == 0)
		{
			fprintf(errorFile, "!");
			i += 2;
		}
		else if (strncmp(msg + i, "EQUALS", 6) == 0)
		{
			fprintf(errorFile, "==");
			i += 5;
		}
		else if (strncmp(msg + i, "NOTEQUALS", 9) == 0)
		{
			fprintf(errorFile, "!=");
			i += 8;
		}
		else if (strncmp(msg + i, "GREATER", 7) == 0)
		{
			fprintf(errorFile, ">");
			i += 6;
		}
		else if (strncmp(msg + i, "NOTGREATER", 10) == 0)
		{
			fprintf(errorFile, "!>");
			i += 9;
		}
		else if (strncmp(msg + i, "LESSER", 6) == 0)
		{
			fprintf(errorFile, "<");
			i += 5;
		}
		else if (strncmp(msg + i, "NOTLESSER", 9) == 0)
		{
			fprintf(errorFile, "!<");
			i += 8;
		}
		else if (strncmp(msg + i, "GREATEREQUALS", 13) == 0)
		{
			fprintf(errorFile, ">=");
			i += 12;
		}
		else if (strncmp(msg + i, "LESSEREQUALS", 12) == 0)
		{
			fprintf(errorFile, "<=");
			i += 11;
		}
		else if (strncmp(msg + i, "TRUE", 4) == 0)
		{
			fprintf(errorFile, "True");
			i += 3;
		}
		else if (strncmp(msg + i, "FALSE", 5) == 0)
		{
			fprintf(errorFile, "False");
			i += 4;
		}
		else if (strncmp(msg + i, "OR", 2) == 0)
		{
			fprintf(errorFile, "\"or\"");
			i += 1;
		}
		else if (strncmp(msg + i, "AND", 3) == 0)
		{
			fprintf(errorFile, "\"and\"");
			i += 2;
		}
		else if (strncmp(msg + i, "BOOL", 4) == 0)
		{
			fprintf(errorFile, "bool");
			i += 3;
		}
		else if (strncmp(msg + i, "WHILE", 5) == 0)
		{
			fprintf(errorFile, "while");
			i += 4;
		}
		else
		{
			fprintf(errorFile, "%c", msg[i]);
		}
		
	}
	fprintf(errorFile, " (line %d)", yylineno);
	fputc('\n', errorFile);
    return 0;
}







