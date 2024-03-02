#include "flags.h"
#include "string.h"


static flags userFlags;

void parseFlags(char* flagsString)
{
	for (int i = 0; i < strlen(flagsString); i++)
	{

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
		userFlags.showLogs = 1;
		break;
	case 'c':
		userFlags.showAscii = 1;
		break;
	case 'a':
		userFlags.showAsm = 1;
		break;
	case 'o':
		userFlags.ShowObj = 1;
		break;
	case 't':
		userFlags.showTokens = 1;
		break;
	case 'e':
		userFlags.showTokensError = 1;
		break;
	case 'p':
		userFlags.showTokenList = 1;
		break;
	case 's':
		userFlags.showVariables = 1;
		break;
	case 'F':
		userFlags.showTokensError = 1;
		userFlags.ShowObj = 1;
		userFlags.showAsm = 1;
		break;
	case 'P':
		userFlags.showVariables = 1;
		userFlags.showTokenList = 1;
		userFlags.showAscii = 1;
		userFlags.showLogs = 1;
		break;
	case 'X':
		userFlags.showVariables = 1;
		userFlags.showTokenList = 1;
		userFlags.showAscii = 1;
		userFlags.showLogs = 1;
		userFlags.showTokensError = 1;
		userFlags.ShowObj = 1;
		userFlags.showAsm = 1;
		userFlags.runExecutable = 1;

	default:
		break;
	}
}
