#include "masmAndLink.h"





void runMasmAndLink(const char* outputName)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	FILE* runFile = openFile(BAT_FILE_NAME, "w");
	if (runFile == NULL)
	{
		return;
	}
	fprintf(runFile, "ml /c /Zd /coff %s.asm\nlink /SUBSYSTEM:CONSOLE %s.obj", outputName, outputName);
	closeFile(runFile);
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (CreateProcessA(NULL, BAT_FILE_NAME, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	{

		// Wait until child process exits
		WaitForSingleObject(pi.hProcess, INFINITE);
		printf("\n\n|||compilation complete|||\n\n");
	}
	else
	{
		printf("\nerror while trying to assemble the asm file\n");

	}
	return;
}

