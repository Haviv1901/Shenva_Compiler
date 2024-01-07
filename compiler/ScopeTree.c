#include "ScopeTree.h"

// Function to create a new tree
ScopeTreeNode* createTree(int value)
{
    ScopeTreeNode* tree = (ScopeTreeNode*)malloc(sizeof(ScopeTreeNode));
    tree->value = value;
    tree->children = NULL;
    return tree;
}

// Function to create a new node
ScopeTreeNode* createNode(int value)
{
    ScopeTreeNode* node = (ScopeTreeNode*)malloc(sizeof(ScopeTreeNode));
    node->value = value;
    node->children = NULL;
    return node;
}

ChildrenNode* createChild()
{
    ChildrenNode* node = (ChildrenNode*)malloc(sizeof(ChildrenNode));
	node->value = NULL;
    node->next = NULL;
    return node;
}
ScopeTreeNode* addChild(ScopeTreeNode* tree, int value)
{
    if (tree == NULL)
    {
        return NULL;
    }

    ChildrenNode* child = createChild();
    child->value = createNode(value);

    ChildrenNode* temp = tree->children;

    if (temp == NULL)
    {
        tree->children = child;
        return child->value;
    }

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = child;

    return child->value;
}

// Function to check if a node is an ancestor of another node or if they are the same node
int isAncestor(ScopeTreeNode* tree, int descendantValue, int potentialAncestorValue)
{
    // If the tree is NULL, return 0
    if (tree == NULL) 
    {
        return 0;
    }
    // If the value of the current node is equal to the potential ancestor value
    if (tree->value == potentialAncestorValue) {
        // If the potential ancestor value is equal to the descendant value, return 1
        if (potentialAncestorValue == descendantValue) {
            return 1;
        }
        // Check if the descendant node is in the children of the current node
        ChildrenNode* currentChild = tree->children;
        while (currentChild != NULL) {
            if (currentChild->value->value == descendantValue) {
                return 1;
            }
            currentChild = currentChild->next;
        }
    }
    // Recursively call the function for each child of the current node
    ChildrenNode* currentChild = tree->children;
    while (currentChild != NULL) {
        if (isAncestor(currentChild->value, descendantValue, potentialAncestorValue)) {
            return 1;
        }
        currentChild = currentChild->next;
    }
    // If the descendant node is not found in the tree rooted at the potential ancestor node, return 0
    return 0;
}




// Function to delete a scope tree
void deleteScopeTree(ScopeTreeNode* tree)
{
    // If the tree is NULL, return
    if (tree == NULL) 
    {
        return;
    }
    // Recursively delete all the children of the current node
    ChildrenNode* currentChild = tree->children;
    while (currentChild != NULL)
    {
        ChildrenNode* temp = currentChild;
        currentChild = currentChild->next;
        deleteScopeTree(temp->value); // delete the ScopeTreeNode
        free(temp); // then delete the ChildrenNode
    }
    // Delete the current node
    free(tree);
}

