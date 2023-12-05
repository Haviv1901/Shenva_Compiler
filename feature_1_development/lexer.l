%{
#include "parser.tab.h"
int yylineno = 1; 
#include <stdio.h>
#include <string.h>
FILE* outputFile;
char lastIdentifier[256] = {0};

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
"%"		  { fprintf(outputFile, "%%\n"); return MOD;}
"sheerit"		  { fprintf(outputFile, "%%\n"); return MOD;}
"("       { fprintf(outputFile, "6\n"); return LPAREN;}
")"       { fprintf(outputFile, "7\n"); return RPAREN;}
"="		  { fprintf(outputFile, "=\n"); return ASSIGN;}
"+="	  { fprintf(outputFile, "=\nv %s\n2\n", lastIdentifier); return ADDEQ;}
"veodShave"	  { fprintf(outputFile, "=\nv %s\n2\n", lastIdentifier); return ADDEQ;}
"-="	  { fprintf(outputFile, "=\nv %s\n3\n", lastIdentifier); return SUBEQ;}
"pahotShave"	  { fprintf(outputFile, "=\nv %s\n3\n", lastIdentifier); return SUBEQ;}
"*="	  { fprintf(outputFile, "=\nv %s\n4\n", lastIdentifier); return MULEQ;}
"kafulShave"	  { fprintf(outputFile, "=\nv %s\n4\n", lastIdentifier); return MULEQ;}
"/="	  { fprintf(outputFile, "=\nv %s\n5\n", lastIdentifier); return DIVEQ;}
"helkeiShave"	  { fprintf(outputFile, "=\nv %s\n5\n", lastIdentifier); return DIVEQ;}
"%="	  { fprintf(outputFile, "=\nv %s\n%%\n", lastIdentifier); return MODEQ;}
"sheeritShave"	  { fprintf(outputFile, "=\nv %s\n%%\n", lastIdentifier); return MODEQ;}
"shave"	  { fprintf(outputFile, "=\n"); return ASSIGN;}
"int"	  { fprintf(outputFile, "i\n"); return INT;}
"mispar"	  { fprintf(outputFile, "i\n"); return INT;}
"char"	  { fprintf(outputFile, "c\n"); return CHAR;}
"ot"	  { fprintf(outputFile, "c\n"); return CHAR;}
[a-zA-Z_][a-zA-Z0-9_]* { fprintf(outputFile, "v %s\n", yytext); strcpy(lastIdentifier, yytext); return VAR; }
'([^\\'\n"\r\b\t\f]|\\[\'n"tbrf])'   {fprintf(outputFile, "l %s\n", yytext); return LETTER; }
[-]?[0-9]+    { fprintf(outputFile, "1 %s\n", yytext); return NUM;}
[ \t]     ; // Ignore whitespace and newline characters
[\n]      { fprintf(outputFile, "9\n"); yylineno++; return ENDL;}
.         { yylval.str = yytext; fprintf(outputFile, "0 %s\n", yytext); return ERROR;}

%%


