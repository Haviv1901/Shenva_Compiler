#pragma once
#include <stdio.h>


/* open input file and return handler */
FILE* openFile(char* inputFileName, char* mode);

/* a helper function for getting the size of a file */
long fileSize(const char* filename);

/* close file */
void closeFile(FILE* file);