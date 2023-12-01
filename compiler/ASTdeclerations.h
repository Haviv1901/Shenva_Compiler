#pragma once




#ifndef  ASTDECLERATIONS_H
#define ASTDECLERATIONS_H


#ifndef ASTNUMERIC_H
#include "ASTnumeric.h"
#endif

#ifndef AST_H
#include "AST.h"
#endif


ASTNode* buildASTDeclerations(struct node** curr);

ASTNode* buildASTDeclerationsInt(struct node** curr);




#endif
