
#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#define STRING_OPEN_INPUT_FILE_SUCCESSFULLY "successfully opened input file: "
#define STRING_OPEN_INPUT_FILE_FAILED "Error opening input file: "
#define LOG_FILE_NAME "log.txt"
enum {MAX_LOG_MESSAGE_SIZE=256};

#endif


/* log_open: open log file */
FILE* logOpen();

/* log_close: close log file */
void logClose(FILE* logFile);

/* write char* to log file */
void logWrite(FILE* logFile, char* str);
