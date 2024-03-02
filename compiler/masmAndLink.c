#include "masmAndLink.h"

#include "flags.h"



void runMasmAndLink(char* outputName)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// open bat file
	FILE* runFile = openFile(BAT_FILE_NAME, "w");
	if (runFile == NULL)
	{
		return;
	}

	char* outputNameNoExtension = clearExeExtension(outputName);
	

	fprintf(runFile, "@echo off\n");

	if(!userFlags.printLogs)
	{
		fprintf(runFile, "ml /c /Zd /coff %s.asm > NUL\n", outputNameNoExtension);
		fprintf(runFile,"link /SUBSYSTEM:CONSOLE /OUT:%s %s.obj > NUL\n", outputName, outputNameNoExtension);
	}
	else
	{
		fprintf(runFile, "ml /c /Zd /coff %s.asm\n", outputNameNoExtension);
		fprintf(runFile, "link /SUBSYSTEM:CONSOLE /OUT:%s %s.obj\n", outputName, outputNameNoExtension);
	}



	if(!userFlags.keepAsmFile)
	{
		// remove asm file
		fprintf(runFile, "del %s.asm\n", outputNameNoExtension);
	}

	if(!userFlags.keepObjectFile)
	{
		// remove obj file
		fprintf(runFile, "del %s.obj\n", outputNameNoExtension);
	}

	if(!userFlags.keepTokensErrorFile)
	{
		// remove tokens file
		fprintf(runFile, "del errors.txt\n");
	}

	if(!userFlags.keepTokenFile)
	{
		// remove tokens file
		fprintf(runFile, "del output.tok\n");
	}

	
	if (userFlags.runExecutable)
	{
		fprintf(runFile, outputNameNoExtension);
		fprintf(runFile, "\n");
	}

	// remove bat file
	fprintf(runFile, "del %s\n", BAT_FILE_NAME);

	closeFile(runFile);
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (CreateProcessA(NULL, BAT_FILE_NAME, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	{

		// Wait until child process exits
		WaitForSingleObject(pi.hProcess, INFINITE);
	}


	free(outputNameNoExtension);

}

