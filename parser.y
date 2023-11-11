%error-verbose
%{
#include <stdio.h>
%}


%token NUM
%token ADD SUB MUL DIV
%token LPAREN RPAREN
%token ERROR
%token PRINT
%token ENDL
%left ADD SUB
%left MUL DIV

%%


program : statements
        ;

statements : statement
           | statements statement
           ;

statement : PRINT LPAREN expression RPAREN  { /* Handle print statement */ }
		  | ENDL
		  | expression
          | ERROR { yyerror("Syntax error: unrecognized expression in the code!"); }
          ;

expression : NUM
           | expression ADD expression { /* Handle addition here */ }
           | expression SUB expression { /* Handle subtraction here */ }
           | expression MUL expression { /* Handle multiplication here */ }
           | expression DIV expression { /* Handle division here */ }
           | LPAREN expression RPAREN   { /* Handle parentheses here */ }
		   | error {yyerror("Syntax error: unexpected phrase in the code! please follow the grammer rules!")}
           ;


%%

int main(int argc, char *argv[]) {
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
	FILE* errorFile = fopen("errors.log", "w");
    if (!errorFile) 
	{
        perror("Error opening error file");
        fclose(inputFile);
		fclose(outputFile);
        return 1;
    }
	fclose(errorFile);
    set_input_file(inputFile);
    set_output_file(outputFile);

    yyparse();

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

int yyerror(const char *msg) 
{
	FILE* errorFile = fopen("errors.log", "a");
    if (!errorFile) 
	{
        perror("Error opening error file");
        return 1;
    }
	if (msg[0] == 'S')
	{
		fprintf(errorFile, msg);
		fprintf(errorFile, "\n");
	}
	fclose(errorFile);
    return 0;
}
