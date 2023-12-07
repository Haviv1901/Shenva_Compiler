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
%token NUM LETTER
%token ADD SUB MUL DIV MOD
%token LPAREN RPAREN
%token <str> ERROR
%token PRINTINT PRINTCHAR COMMA
%token ENDL
%token ASSIGN
%token INT CHAR
%token VAR
%token ADDEQ SUBEQ MULEQ DIVEQ MODEQ
%left ADD SUB
%left MUL DIV MOD

%%


program : statements
        ;

statements : statement
           | statements statement
           ;

statement : PRINTINT LPAREN expression_list RPAREN ENDL { /* Handle print statement */ }
		  |  PRINTCHAR LPAREN expression_list RPAREN ENDL { /* Handle print statement */ }
		  | expression ENDL
          | declaration ENDL
          | assignment ENDL
		  | ENDL
          | ERROR {fprintf(errorFile, "syntax error, unrecognized \"%s\" in the code (line %d)\n", $1, yylineno);}
          ;

declaration : INT decleration_list
            | CHAR decleration_list
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

expression : NUM
		   | VAR
		   | LETTER
           | expression ADD expression { /* Handle addition here */ }
           | expression SUB expression { /* Handle subtraction here */ }
           | expression MUL expression { /* Handle multiplication here */ }
           | expression DIV expression { /* Handle division here */ }
		   | expression MOD expression {}
           | LPAREN expression RPAREN   { /* Handle parentheses here */ }
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
		else if (strncmp(msg + i, "LETTER", 6) == 0)
		{
			fprintf(errorFile, "letter");
			i += 5;
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
		else
		{
			fprintf(errorFile, "%c", msg[i]);
		}
		
	}
	fprintf(errorFile, " (line %d)", yylineno);
	fputc('\n', errorFile);
    return 0;
}







