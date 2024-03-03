#include "flags.h"
#include <string.h>

flags userFlags = {
	.printLogs = false,
	.runExecutable = false,
	.dontPrintAscii = false,
	.keepAsmFile = false,
	.keepObjectFile = false,
	.keepTokenFile = false,
	.keepTokensErrorFile = false,
	.printTokenList = false,
	.printVariableList = false
};

void parseFlags(char* flagsString)
{
	for (int i = 0; i < strlen(flagsString); i++) 
	{
		parseCharToFlag(flagsString[i]);
	}
}

void parseCharToFlag(char toParse)
{
	switch (toParse)
	{
	case 'r':
		userFlags.runExecutable = 1;
		break;
	case 'l':
		userFlags.printLogs = 1;
		break;
	case 'c':
		userFlags.dontPrintAscii = 1;
		break;
	case 'a':
		userFlags.keepAsmFile = 1;
		break;
	case 'o':
		userFlags.keepObjectFile = 1;
		break;
	case 't':
		userFlags.keepTokenFile = 1;
		break;
	case 'e':
		userFlags.keepTokensErrorFile = 1;
		break;
	case 'p':
		userFlags.printTokenList = 1;
		break;
	case 's':
		userFlags.printVariableList = 1;
		break;
	case 'F':
		userFlags.keepTokensErrorFile = 1;
		userFlags.keepObjectFile = 1;
		userFlags.keepAsmFile = 1;
		userFlags.keepTokenFile = 1;
		break;
	case 'P':
		userFlags.printVariableList = 1;
		userFlags.printTokenList = 1;
		userFlags.dontPrintAscii = 1;
		userFlags.printLogs = 1;
		break;
	case 'X':
		userFlags.printVariableList = 1;
		userFlags.printTokenList = 1;
		userFlags.dontPrintAscii = 1;
		userFlags.printLogs = 1;
		userFlags.keepTokenFile = 1;
		userFlags.keepTokensErrorFile = 1;
		userFlags.keepObjectFile = 1;
		userFlags.keepAsmFile = 1;
		userFlags.runExecutable = 1;

	default:
		break;
	}
}
