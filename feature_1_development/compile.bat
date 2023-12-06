bison -d parser.y
flex lexer.l
gcc -o lexicalAndSyntaxAnalysis parser.tab.c lex.yy.c 
rm parser.tab.c
rm lex.yy.c 