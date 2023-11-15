#include "fileHelper.h"

#include <string.h>


/*
fileSize: a function to get the size of a file
input: the file name
output: the file size
*/
long fileSize(char* filename)
{
	FILE* file = openFile(filename, "r");

	fseek(file, 0, SEEK_END);
	long size = ftell(file);

	fclose(file);

	return size;
}

/* open input file and return handler */
FILE* openFile(char* inputFileName, char* mode)
{
	FILE* res = fopen(inputFileName, mode);

	if (res == NULL)
	{
		printf("could not open file: ");
		printf("%s\n", inputFileName);
		return NULL;
	}

	printf("successfully opened file: ");
	printf("%s\n", inputFileName);
	return res;
}

/* open input file and return handler */
void closeFile(FILE* file)
{
	if(fclose(file) < 0)
	{
		printf("could not close file\n");
	}
	else
	{
		printf("successfully closed file");
	}
}




