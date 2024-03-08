#include "masmAndLink.h"

#include "flags.h"

bool FileExists(const char* fileName) 
{
	DWORD fileAttributes = GetFileAttributesA(fileName);
	return (fileAttributes != INVALID_FILE_ATTRIBUTES &&!(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

void runMasmAndLink(char* outputName)
{

	// open bat file
	FILE* runFile = openFile(BAT_FILE_NAME, "w");
	if (runFile == NULL)
	{
		return;
	}

	char* outputNameNoExtension = clearExeExtension(outputName), *path = getCompilerPath();
	

	fprintf(runFile, "@echo off\n");

	if(!userFlags.printLogs)
	{
		fprintf(runFile, "%s\\masm32\\bin\\ml /c /Zd /coff /nologo %s.asm > NUL\n", path, outputNameNoExtension);
		fprintf(runFile,"%s\\masm32\\bin\\link /SUBSYSTEM:CONSOLE /NOLOGO %s.obj\n", path, outputNameNoExtension);
	}
	else
	{
		fprintf(runFile, "%s\\masm32\\bin\\ml /c /Zd /coff %s.asm > NUL\n", path, outputNameNoExtension);
		fprintf(runFile, "%s\\masm32\\bin\\link /SUBSYSTEM:CONSOLE %s.obj\n", path, outputNameNoExtension);
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


	// remove bat file
	fclose(runFile);

	// run the run file
	runEXEfile(BAT_FILE_NAME);

	DeleteFileA(BAT_FILE_NAME);


	free(outputNameNoExtension);
	free(path);
}


char* createOutputFileFullName(char* outputName)
{
	char* outputNameNoExtension = clearExeExtension(outputName);
	int len = strlen(outputNameNoExtension);
	outputNameNoExtension = (char*)realloc(outputNameNoExtension, len + 5);
	if (outputNameNoExtension == NULL)
	{
		return NULL;
	}
	outputNameNoExtension[len] = '.';
	outputNameNoExtension[len + 1] = 'e';
	outputNameNoExtension[len+2] = 'x';
	outputNameNoExtension[len+3] = 'e';
	outputNameNoExtension[len+4] = '\0';

	return outputNameNoExtension;
}


void runEXEfile(char* path)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (CreateProcessA(NULL, path, NULL, NULL, false, 0, NULL, NULL, &si, &pi))
	{

		// Wait until child process exits
		WaitForSingleObject(pi.hProcess, INFINITE);
	}

}


