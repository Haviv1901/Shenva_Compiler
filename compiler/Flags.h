#pragma once
#include <stdbool.h>


struct flags
{

	bool showLogs;
	bool runExecutable;
	bool showAscii;
	bool showAsm;
	bool ShowObj;
	bool showTokens;
	bool showTokensError;
	bool showTokenList;
	bool showVariables;
}typedef flags;



void parseFlags(char* flags);
void parseCharToFlag(char toParse);