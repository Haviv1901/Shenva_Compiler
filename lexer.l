%{
#include "parser.tab.h"
#include <stdio.h>

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
"hadpasa" { fprintf(outputFile, "PRINT\n"); return PRINT;}
"print"   { fprintf(outputFile, "PRINT\n"); return PRINT;}
"veod"    { fprintf(outputFile, "ADD\n"); return ADD;}
"+"       { fprintf(outputFile, "ADD\n"); return ADD;}
"pahot"   { fprintf(outputFile, "SUB\n"); return SUB;}
"-"       { fprintf(outputFile, "SUB\n"); return SUB;}
"kaful"   { fprintf(outputFile, "MUL\n"); return MUL;}
"*"       { fprintf(outputFile, "MUL\n"); return MUL;}
"helkei"  { fprintf(outputFile, "DIV\n"); return DIV;}
"/"       { fprintf(outputFile, "DIV\n"); return DIV;}
"("       { fprintf(outputFile, "LPAREN\n"); return LPAREN;}
")"       { fprintf(outputFile, "RPAREN\n"); return RPAREN;}
[0-9]+    { fprintf(outputFile, "NUM %s\n", yytext); return NUM;}
[ \t]     ; // Ignore whitespace and newline characters
[\n]      { fprintf(outputFile, "ENDL\n"); return ENDL;}
.         { fprintf(outputFile, "ERROR %s\n", yytext); return ERROR;}

%%


