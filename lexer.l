%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

%}

%option noyywrap

%%
"hadpasa" { fprintf(yyout, "PRINT\n");}
"print"   { fprintf(yyout, "PRINT\n");}
"veod"    { fprintf(yyout, "ADD\n");}
"+"       { fprintf(yyout, "ADD\n");}
"pahot"   { fprintf(yyout, "SUB\n");}
"-"       { fprintf(yyout, "SUB\n");}
"kaful"   { fprintf(yyout, "MUL\n");}
"*"       { fprintf(yyout, "MUL\n");}
"helkei"  { fprintf(yyout, "DIV\n");}
"/"       { fprintf(yyout, "DIV\n");}
"("       { fprintf(yyout, "LPAREN\n");}
")"       { fprintf(yyout, "RPAREN\n");}
[0-9]+    { fprintf(yyout, "NUM %s\n", yytext);}
[ \t]     ; // Ignore whitespace and newline characters
[\n]      { fprintf(yyout, "ENDL\n");}
.         { fprintf(yyout, "ERROR %s\n", yytext);}
%%

int main(int argc, char** argv) {
    if (argc != 3) {
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        return 1;
    }

    FILE* output_file = fopen(argv[2], "w");
    if (!output_file) {
        fclose(input_file);
        return 1;
    }

    yyin = input_file;
    yyout = output_file;

    yylex(); 

    fclose(input_file);
    fclose(output_file);

    return 0;
}
