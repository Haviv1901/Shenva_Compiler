
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
     WHILE = 284,
     FOR = 285,
     ERROR = 286,
     PRINTINT = 287,
     PRINTCHAR = 288,
     PRINTFLOAT = 289,
     COMMA = 290,
     INTINPUT = 291,
     FLOATINPUT = 292,
     CHARINPUT = 293,
     TRUE = 294,
     FALSE = 295,
     ENDL = 296,
     ASSIGN = 297,
     INT = 298,
     CHAR = 299,
     FLOAT = 300,
     VAR = 301,
     ADDEQ = 302,
     SUBEQ = 303,
     MULEQ = 304,
     DIVEQ = 305,
     MODEQ = 306,
     DEF = 307,
     RETURN = 308,
     LOWER_THAN_ELSE = 309
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
#line 113 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


