#include "Compiler.h"
#include "Menu.h"
#include <stdio.h>
#include <crtdbg.h>
#include "masmAndLink.h"


#include "flags.h"
#define _CRTDBG_MAP_ALLOC

void printGreenText(const char* text)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // Set text color to green
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); // Reset text color
}

void printRedText(const char* text)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // Set text color to red
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); // Reset text color
}

int main(int argc, char* argv[])
{
    bool isCompilationSucceed = false;
    bool compile = handleCommandLineArguments(argc, argv);
    char* outputFullName = NULL;


    if (!compile)
    {
        return 0;
    }

    isCompilationSucceed = Compile(argv[1], argv[2]);


    if (isCompilationSucceed)
    {
        if (userFlags.dontPrintAscii != 1)
        {
            printFile("Menu_Scripts/ascii_success.txt");
        }
        outputFullName = createOutputFileFullName(argv[2]);
        if (userFlags.runExecutable == 1 && FileExists(outputFullName))
        {
            printf("\n\n");
            runEXEfile(outputFullName);
        }
        free(outputFullName);
    }
    else
    {
        if (userFlags.dontPrintAscii != 1)
        {
            printFile("Menu_Scripts/ascii_failure.txt");
        }
    }
    return 0; // Exit successfully
}