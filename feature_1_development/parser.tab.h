
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     LETTER = 259,
     DECIMAL = 260,
     BOOL = 261,
     ADD = 262,
     SUB = 263,
     MUL = 264,
     DIV = 265,
     MOD = 266,
     LPAREN = 267,
     RPAREN = 268,
     EQUALS = 269,
     NOTEQUALS = 270,
     GREATER = 271,
     NOTGREATER = 272,
     LESSER = 273,
     NOTLESSER = 274,
     GREATEREQUALS = 275,
     LESSEREQUALS = 276,
     NOT = 277,
     OR = 278,
     AND = 279,
     IF = 280,
     ELSE = 281,
     LBRACK = 282,
     RBRACK = 283,
     ERROR = 284,
     PRINTINT = 285,
     PRINTCHAR = 286,
     PRINTFLOAT = 287,
     COMMA = 288,
     INTINPUT = 289,
     FLOATINPUT = 290,
     CHARINPUT = 291,
     TRUE = 292,
     FALSE = 293,
     ENDL = 294,
     ASSIGN = 295,
     INT = 296,
     CHAR = 297,
     FLOAT = 298,
     VAR = 299,
     ADDEQ = 300,
     SUBEQ = 301,
     MULEQ = 302,
     DIVEQ = 303,
     MODEQ = 304,
     LOWER_THAN_ELSE = 305
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 10 "parser.y"

    int num;
    char *str;  // Add a string field



/* Line 1676 of yacc.c  */
#line 109 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


