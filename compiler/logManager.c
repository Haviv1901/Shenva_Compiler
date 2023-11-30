#include <stdio.h>
#include "logManager.h"


/* log_open: open log file */
FILE* logOpen()
{
	FILE* logFile = fopen(LOG_FILE_NAME, "w");
	if (logFile == NULL)
	{
		//printf("Error opening file %s\n", LOG_FILE_NAME);
		return NULL;
	}
	return logFile;
}

/* log_close: close log file */
void logClose(FILE* logFile)
{
	if(fclose(logFile) == EOF)
	{
		printf("Error closing log file %s\n", LOG_FILE_NAME);
	}
}

/* write char* to log file */
void logWrite(FILE* logFile, char* str)
{
	if (fprintf(logFile, "%s\n", str) < 0)
	{
		printf("Error writing to log file %s\n", LOG_FILE_NAME);
	}
}