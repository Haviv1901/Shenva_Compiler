#pragma once
#include <stdbool.h>

#ifndef FLAG_H
#define FLAG_H

#include <stdbool.h>

typedef struct {
    bool printLogs;
    bool runExecutable;
    bool dontPrintAscii;
    bool keepAsmFile;
    bool keepObjectFile;
    bool keepTokenFile;
    bool keepTokensErrorFile;
    bool printTokenList;
    bool printVariableList;
} flags;

extern flags userFlags;

void parseFlags(char* flagsString);
void parseCharToFlag(char toParse);

#endif /* FLAG_H */
