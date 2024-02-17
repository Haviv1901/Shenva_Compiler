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
","					{ fprintf(outputFile, ",\n"); return COMMA;}
"intInput"   { fprintf(outputFile, "j\n"); return INTINPUT;}
"keletShelShalem"   { fprintf(outputFile, "j\n"); return INTINPUT;}
"charInput"   { fprintf(outputFile, "L\n"); return CHARINPUT;}
"keletShelOt"   { fprintf(outputFile, "L\n"); return CHARINPUT;}
"floatInput"   { fprintf(outputFile, "m\n"); return FLOATINPUT;}
"keletShelTzaf"   { fprintf(outputFile, "m\n"); return FLOATINPUT;}
"hadpasaShelMispar" { fprintf(outputFile, "8\n"); return PRINTINT;}
"printInt"   { fprintf(outputFile, "8\n"); return PRINTINT;}
"hadpasaShelOt" { fprintf(outputFile, "h\n"); return PRINTCHAR;}
"printChar"   { fprintf(outputFile, "h\n"); return PRINTCHAR;}
"hadpasaShelTzaf" { fprintf(outputFile, "n\n"); return PRINTFLOAT;}
"printFloat"   { fprintf(outputFile, "n\n"); return PRINTFLOAT;}
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
"=="	  { fprintf(outputFile, "S\n"); return EQUALS;}
"shaveshave"	  { fprintf(outputFile, "S\n"); return EQUALS;}
"!="	  { fprintf(outputFile, "U\n"); return NOTEQUALS;}
"loshave"	  { fprintf(outputFile, "U\n"); return NOTEQUALS;}
">"	  { fprintf(outputFile, "G\n"); return GREATER;}
"gadol"	  { fprintf(outputFile, "G\n"); return GREATER;}
"!>"	  { fprintf(outputFile, "H\n"); return NOTGREATER;}
"logadol"	  { fprintf(outputFile, "H\n"); return NOTGREATER;}
"<"	  { fprintf(outputFile, "K\n"); return LESSER;}
"katan"	  { fprintf(outputFile, "K\n"); return LESSER;}
"!<"	  { fprintf(outputFile, "M\n"); return NOTLESSER;}
"lokatan"	  { fprintf(outputFile, "M\n"); return NOTLESSER;}
"gadolshave"	  { fprintf(outputFile, "N\n"); return GREATEREQUALS;}
">="	  { fprintf(outputFile, "N\n"); return GREATEREQUALS;}
"katanshave"	  { fprintf(outputFile, "O\n"); return LESSEREQUALS;}
"<="	  { fprintf(outputFile, "O\n"); return LESSEREQUALS;}
"!"	  { fprintf(outputFile, "!\n"); return NOT;}
"true"    { fprintf(outputFile, "1 1\n"); return TRUE;}
"emet"    { fprintf(outputFile, "1 1\n"); return TRUE;}
"false"    { fprintf(outputFile, "1 0\n"); return FALSE;}
"sheker"    { fprintf(outputFile, "1 0\n"); return FALSE;}
"or"    { fprintf(outputFile, "o\n"); return OR;}
"oshe"    { fprintf(outputFile, "o\n"); return OR;}
"and"    { fprintf(outputFile, "a\n"); return AND;}
"vegamshe"    { fprintf(outputFile, "a\n"); return AND;}
"shave"	  { fprintf(outputFile, "=\n"); return ASSIGN;}
"int"	  { fprintf(outputFile, "i\n"); return INT;}
"pInt"	  { fprintf(outputFile, "Q\n"); return PINT;}
"mispar"	  { fprintf(outputFile, "i\n"); return INT;}
"mMispar"	  { fprintf(outputFile, "Q\n"); return PINT;}
"char"	  { fprintf(outputFile, "c\n"); return CHAR;}
"pChar"	  { fprintf(outputFile, "T\n"); return PCHAR;}
"ot"	  { fprintf(outputFile, "c\n"); return CHAR;}
"mOt"	  { fprintf(outputFile, "T\n"); return PCHAR;}
"float"	  { fprintf(outputFile, "f\n"); return FLOAT;}
"pFloat"	  { fprintf(outputFile, "X\n"); return PFLOAT;}
"tzaf"	  { fprintf(outputFile, "f\n"); return FLOAT;}
"mTzaf"	  { fprintf(outputFile, "X\n"); return PFLOAT;}
"bool"	  { fprintf(outputFile, "b\n"); return BOOL;}
"pBool"	  { fprintf(outputFile, "W\n"); return PBOOL;}
"meteg"	  { fprintf(outputFile, "b\n"); return BOOL;}
"mMeteg"	  { fprintf(outputFile, "W\n"); return PBOOL;}
"if"	  { fprintf(outputFile, "I\n"); return IF;}
"eam"	  { fprintf(outputFile, "I\n"); return IF;}
"else"	  { fprintf(outputFile, "E\n"); return ELSE;}
"aheret"  { fprintf(outputFile, "E\n"); return ELSE;}
"while"	  { fprintf(outputFile, "w\n"); return WHILE;}
"colOd"	  { fprintf(outputFile, "w\n"); return WHILE;}
"for"	  { fprintf(outputFile, "F\n"); return FOR;}
"avor"	  { fprintf(outputFile, "F\n"); return FOR;}
"{"	  { fprintf(outputFile, "{\n"); return LBRACK;}
"}"	  { fprintf(outputFile, "}\n"); return RBRACK;}
"def" { fprintf(outputFile, "D\n"); return DEF;}
"func" { fprintf(outputFile, "D\n"); return DEF;}
"functzia" { fprintf(outputFile, "D\n"); return DEF;}
"return" { fprintf(outputFile, "r\n"); return RETURN;}
"hahzara" { fprintf(outputFile, "r\n"); return RETURN;}
"&" { fprintf(outputFile, "&\n"); return REFERENCE;}
"^" { fprintf(outputFile, "^\n"); return DEREFERENCE;}
"[" { fprintf(outputFile, "[\n"); return LIND;}
"]" { fprintf(outputFile, "]\n"); return RIND;}






[a-zA-Z_][a-zA-Z0-9_]* { fprintf(outputFile, "v %s\n", yytext); strcpy(lastIdentifier, yytext); return VAR; }
'([^\\'\n"\r\b\t\f]|\\[\\'n"tbrf])'   {fprintf(outputFile, "l %s\n", yytext); return LETTER; }
[-]?[0-9]+   { fprintf(outputFile, "1 %s\n", yytext); return NUM;}
[-]?[0-9]+\.[0-9]+		{ fprintf(outputFile, "d %s\n", yytext); return DECIMAL;}
[ \t]     ; // Ignore whitespace and newline characters
[\n]      { fprintf(outputFile, "9\n"); yylineno++; return ENDL;}
.         { yylval.str = yytext; fprintf(outputFile, "0 %s\n", yytext); return ERROR;}

%%


