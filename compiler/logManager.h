
#define LOG_FILE_NAME "log.txt"


/* log_open: open log file */
FILE* log_open();

/* log_close: close log file */
void log_close(FILE* logFile);

/* write char* to log file */
void log_write(FILE* logFile, char* str);
