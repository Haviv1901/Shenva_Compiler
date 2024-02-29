
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
     STRING = 262,
     ADD = 263,
     SUB = 264,
     MUL = 265,
     DIV = 266,
     MOD = 267,
     LPAREN = 268,
     RPAREN = 269,
     EQUALS = 270,
     NOTEQUALS = 271,
     GREATER = 272,
     NOTGREATER = 273,
     LESSER = 274,
     NOTLESSER = 275,
     GREATEREQUALS = 276,
     LESSEREQUALS = 277,
     NOT = 278,
     OR = 279,
     AND = 280,
     IF = 281,
     ELSE = 282,
     LBRACK = 283,
     RBRACK = 284,
     WHILE = 285,
     FOR = 286,
     ERROR = 287,
     PRINTINT = 288,
     PRINTCHAR = 289,
     PRINTFLOAT = 290,
     COMMA = 291,
     INTINPUT = 292,
     FLOATINPUT = 293,
     CHARINPUT = 294,
     TRUE = 295,
     FALSE = 296,
     ENDL = 297,
     ASSIGN = 298,
     LIST = 299,
     INT = 300,
     CHAR = 301,
     FLOAT = 302,
     PINT = 303,
     PCHAR = 304,
     PFLOAT = 305,
     PBOOL = 306,
     VAR = 307,
     ADDEQ = 308,
     SUBEQ = 309,
     MULEQ = 310,
     DIVEQ = 311,
     MODEQ = 312,
     DEF = 313,
     RETURN = 314,
     REFERENCE = 315,
     DEREFERENCE = 316,
     LIND = 317,
     RIND = 318,
     LOWER_THAN_ELSE = 319
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
#line 123 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


