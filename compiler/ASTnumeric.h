#ifndef AST_H
#include "AST.h"
#endif

#ifndef ASTNUMERIC_H
#define ASTNUMERIC_H
#endif



ASTNode* parseLast(struct node** curr);
ASTNode* parseSecond(struct node** curr);
ASTNode* parseFirst(struct node** curr);
ASTNode* buildASTNumeric(struct node** curr);