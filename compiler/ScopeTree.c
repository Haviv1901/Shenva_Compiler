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

// get scope tree node from int value and head pointer
ScopeTreeNode* getNodeByScope(ScopeTreeNode* treeScopeHead, int scope)
{
	if (treeScopeHead == NULL)
	{
		return NULL;
	}

	if (treeScopeHead->value == scope)
	{
		return treeScopeHead;
	}

	ChildrenNode* currentChild = treeScopeHead->children;
	while (currentChild != NULL)
	{
		ScopeTreeNode* temp = getNodeByScope(currentChild->value, scope);
		if (temp != NULL)
		{
			return temp;
		}
		currentChild = currentChild->next;
	}
	return NULL;
}

int isAncestorByNodes(ScopeTreeNode* potentialAncestorNode, ScopeTreeNode* childNode)
{
    // If the potential ancestor node is NULL, we've reached the bottom of the tree without finding the child
    if (potentialAncestorNode == NULL)
    {
        return 0;
    }

    // Check the children of the current node
    ChildrenNode* currentChild = potentialAncestorNode->children;
    while (currentChild != NULL)
    {
        // If the current child is the child node, return true
        if (currentChild->value == childNode) 
        {
            return 1;
        }

		// Otherwise, check the children of the current child
		if (isAncestorByNodes(currentChild->value, childNode))
		{
			return 1;
		}

        currentChild = currentChild->next;
    }

    // If we've checked all children and found no match, return false
    return 0;
}



// Function to check if a node is an ancestor of another node or if they are the same node
int isAncestor(ScopeTreeNode* treeScopeHead, int descendantValue, int potentialAncestorValue)
{

    if(descendantValue == potentialAncestorValue || potentialAncestorValue == 0) // 0 is global scope
    {
        return 1;
    }

    ScopeTreeNode* descendantNode = getNodeByScope(treeScopeHead, descendantValue);
    ScopeTreeNode* potentialAncestorNode = getNodeByScope(treeScopeHead, potentialAncestorValue);

    if(descendantNode == NULL || potentialAncestorNode == NULL)
    {
		return -1;
    }
    
    return isAncestorByNodes(potentialAncestorNode, descendantNode);

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

