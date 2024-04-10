bison -d parser.y
flex lexer.l
gcc -o lexicalAndSyntaxAnalysis parser.tab.c lex.yy.c 
del parser.tab.c
del lex.yy.c 