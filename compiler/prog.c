#include "TokenGetter.h"

#define FILE_NAME "output.txt"


void tokenPrint(void*);

int main()
{

	FILE* file = fopen(FILE_NAME, "r");
	if (file == NULL)
	{
		printf("Error opening file %s\n", FILE_NAME);
		return 1;
	}
	llist* tokenList = extractToken(file);
	fclose(file);


	llist_print(tokenList, tokenPrint);
	llist_free(tokenList);

}

void tokenPrint(void* data)
{
	Token* token = (Token*)data;
	printToken(token);
}