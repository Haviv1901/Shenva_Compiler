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
ASTNode* parseBooleanOps(struct node** curr);
ASTNode* parseLogicalOps(struct node** curr);
ASTNode* parseNotOp(struct node** curr);
ASTNode* parseIndex(struct node** curr, ASTNode* var);