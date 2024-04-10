#pragma once




#ifndef  ASTDECLERATIONS_H
#define ASTDECLERATIONS_H


#ifndef ASTNUMERIC_H
#include "ASTnumeric.h"
#endif

#ifndef AST_H
#include "AST.h"
#endif


ASTNode* buildASTVariables(struct node** curr);

ASTNode* buildASTDeclerationsNumeric(struct node** curr);

ASTNode* buildASTVariablesAssign(node** node);

ASTNode* buildASTListDeclerationBranch(struct node** curr, Token* decTypeTok);

ASTNode* buildASTPreMadeListDec(struct node** curr);

#endif
