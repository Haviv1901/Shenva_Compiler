#pragma once
#include <stdlib.h>


// Define the Node structure




typedef struct ScopeTreeNode
{
    int value;
    struct ChildrenNode* children;
} ScopeTreeNode;

typedef struct ChildrenNode
{
    ScopeTreeNode* value;
    struct ChildrenNode* next;
} ChildrenNode;


// Function prototypes
ScopeTreeNode* createTree(int value);
ChildrenNode* createChild();
ScopeTreeNode* createNode(int value);
void deleteScopeTree(ScopeTreeNode* tree);
ScopeTreeNode* getNodeByScope(ScopeTreeNode* treeScopeHead, int scope);
ScopeTreeNode* addChild(ScopeTreeNode* tree, int value);
int isAncestor(ScopeTreeNode* treeScopeHead, int currentNodeValue, int potentialAncestorValue);
int isAncestorByNodes(ScopeTreeNode* descendantNode, ScopeTreeNode* potentialAncestorNode);
