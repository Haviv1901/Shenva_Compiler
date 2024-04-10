#ifndef ASTFUNCTIONS_H
#define ASTFUNCTIONS_H
#endif

#ifndef AST_H
#include "AST.h"
#endif

#ifndef ASTNUMERIC_H
#include "ASTnumeric.h"
#endif

#ifndef ASTDECLERATIONS_H
#include "ASTdeclerations.h"
#endif

ASTNode* buildASTFunctions(struct node** curr);
ASTNode* buildASTFunctions_functionCall(node** node);
ASTNode* buildASTFunctions_DefFunctions(node** node);

ASTNode* buildASTFunctions_print(struct node** curr);