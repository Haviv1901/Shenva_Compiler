#include "ASTconditions.h"

#include "ASTdeclerations.h"


/*
buildASTconditions: this function will build a condition branch
input: the token list
output: the condition branch
*/
ASTNode* buildASTConditionsOrWhileLoops(struct node** curr)
{
    Token* tok = (*curr)->data;
    struct node* node = NULL;
    ASTNode* result = createNewASTnode((Token*)(*curr)->data); // Creating the IF node (or while)

    *curr = (*curr)->next;
    result->children[CONDITION] = buildASTNumeric(curr); // Making the condition in child 1 (0)

    *curr = (*curr)->next; // Going to the openBracket
    node = beracketEqualizer(*curr);

    *curr = (*curr)->next; // Going into the code
    result->children[CODE] = buildTree(curr); // Making the numeric tree there

    *curr = node; // Getting the newline token after the close bracket
    *curr = (*curr)->next; // Going to the next

    if (*curr != NULL && ((Token*)(*curr)->data)->type == TOKEN_ELSE)
    {
        result->children[ELSE] = createNewASTnode((Token*)(*curr)->data); // Making else
        *curr = (*curr)->next;
        tok = (*curr)->data;

        if (tok->type == TOKEN_IF) // In case of else if
        {
            result->children[ELSE]->children[NEXT] = buildASTConditionsOrWhileLoops(curr);
        }
        else // In case of a virgin else
        {
            *curr = (*curr)->next;
            tok = (*curr)->data;
            node = beracketEqualizer(*curr);
            *curr = (*curr)->next;
            result->children[ELSE]->children[NEXT] = buildTree(curr);
            *curr = node;
        }
    }
    return result;
}


/*
buildASTconditions: this function will build a condition branch
input: the token list
output: the condition branch
*/
ASTNode* buildASTForLoops(struct node** curr)
{
    Token* tok = (*curr)->data;
    struct node* node = NULL;
    ASTNode* result = createNewASTnode((Token*)(*curr)->data); // Creating the 'for' node

    *curr = (*curr)->next;
    result->children[CONDITION] = buildASTNumeric(curr); // Making the condition in the first child  

    *curr = (*curr)->next; // skeeping the comma
    result->children[OPPERATION_TO_DO_EVERY_ITER] = buildASTVariablesAssign(curr); // Making the assign in the second child


    *curr = (*curr)->next; // Going to the openBracket
    node = beracketEqualizer(*curr);

    *curr = (*curr)->next; // Going into the code
    result->children[CODE] = buildTree(curr); // Making the numeric tree there

    return result;
}

/*
bracketEqualizer: this function will equalize a bracket on the token list, and return the token after the last one
input: the token list
output: a pointer to the token after the last right bracket
*/
struct node* beracketEqualizer(struct node* curr)
{
    int equalizer = 0;
    struct node* node = curr;

    do
    {
        if (((Token*)node->data)->type == TOKEN_LBRACK) // Numeric equalizing
        {
            equalizer += 1;
        }

        if (((Token*)node->data)->type == TOKEN_RBRACK)
        {
            equalizer -= 1;
        }
        node = node->next;
    } while (equalizer != 0);

    return node;
}
