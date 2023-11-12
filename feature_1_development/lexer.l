%{
#include "parser.tab.h"
int yylineno = 1; 
#include <stdio.h>
#include <string.h>
FILE* outputFile;

void set_input_file(FILE* file) {
    yyin = file;
}

void set_output_file(FILE* file) {
    outputFile = file;
}

%}
%option noyywrap



%%
"hadpasa" { fprintf(outputFile, "8\n"); return PRINT;}
"print"   { fprintf(outputFile, "8\n"); return PRINT;}
"veod"    { fprintf(outputFile, "2\n"); return ADD;}
"+"       { fprintf(outputFile, "2\n"); return ADD;}
"pahot"   { fprintf(outputFile, "3\n"); return SUB;}
"-"       { fprintf(outputFile, "3\n"); return SUB;}
"kaful"   { fprintf(outputFile, "4\n"); return MUL;}
"*"       { fprintf(outputFile, "4\n"); return MUL;}
"helkei"  { fprintf(outputFile, "5\n"); return DIV;}
"/"       { fprintf(outputFile, "5\n"); return DIV;}
"("       { fprintf(outputFile, "6\n"); return LPAREN;}
")"       { fprintf(outputFile, "7\n"); return RPAREN;}
[0-9]+    { fprintf(outputFile, "1 %s\n", yytext); return NUM;}
[ \t]     ; // Ignore whitespace and newline characters
[\n]      { fprintf(outputFile, "9\n"); yylineno++; return ENDL;}
.         { yylval.str = yytext; fprintf(outputFile, "0 %s\n", yytext); return ERROR;}

%%


