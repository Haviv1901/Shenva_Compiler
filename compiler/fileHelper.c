#include "fileHelper.h"
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include "Flags.h"


/*
fileSize: a function to get the size of a file
input: the file name
output: the file size
*/
long fileSize(char* filename)
{
	FILE* file = openFile(filename, "rb");

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	fclose(file);

	return size;
}

/* open input file and return handler */
FILE* openFile(char* inputFileName, char* mode)
{
	FILE* res = fopen(inputFileName, mode);

	if (res == NULL)
	{
		if (userFlags.printLogs)
		{
			printLog("could not open file: ");
		}
		return NULL;
	}
	if (userFlags.printLogs)
	{
		printLog("successfully opened file: ");
	}
	printLog(inputFileName);
	printLog("\n");

	return res;
}

/* open input file and return handler */
void closeFile(FILE* file, const char* fileName)
{
	if(fclose(file) != 0)
	{
		printf("could not close file: %s\n", fileName);
	}
	else
	{
		printf("successfully closed file: %s\n", fileName);
	}
}

void printFile(const char* filename)
{
	char path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	char* lastBackslash = strrchr(path, '\\');
	lastBackslash[1] = '\0';
	strcat(path, filename);
	FILE* file = fopen(path, "r");
	if (file == NULL) 
	{
		return;
	}

	char buffer[1024]; // Buffer to read lines from file

	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		printf("%s", buffer);
	}

	fclose(file);
}


void printLog(char* msg)
{
	if (userFlags.printLogs)
	{
		printf("%s", msg);
	}
}

char* clearExeExtension(const char* filename)
{
	int len = strlen(filename);
	int dotIndex = -1;

	// Find the index of the last dot in the filename
	for (int i = len - 1; i >= 0; i--) {
		if (filename[i] == '.') {
			dotIndex = i;
			break;
		}
	}

	// If dotIndex is -1, there's no dot in the filename
	if (dotIndex == -1) {
		// Return a copy of the original filename
		return _strdup(filename);
	}

	// Allocate memory for the new string without the extension
	char* newFilename = malloc(dotIndex + 1);
	if (newFilename == NULL) {
		// Memory allocation failed
		return NULL;
	}

	// Copy the characters from the original filename to the new string
	strncpy(newFilename, filename, dotIndex);
	newFilename[dotIndex] = '\0'; // Null-terminate the new string

	return newFilename;
}