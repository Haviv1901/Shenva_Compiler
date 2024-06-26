#ifndef ASTCONDITIONS_H
#define ASTCONDITIONS_H
#endif

#ifndef AST_H
#include "AST.h"
#endif

#ifndef ASTNUMERIC_H
#include "ASTnumeric.h"
#endif

#ifndef ASTMANAGER_H
#include "ASTManager.h"
#endif

ASTNode* buildASTConditionsOrWhileLoops(struct node** curr);
ASTNode* buildASTForLoops(struct node** curr);

struct node* beracketEqualizer(struct node* curr);
