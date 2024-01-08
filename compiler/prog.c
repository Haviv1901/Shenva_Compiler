#include "Compiler.h"
#include <stdio.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

void printGreenText(const char* text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // Set text color to green
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); // Reset text color
}

void printRedText(const char* text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // Set text color to red
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); // Reset text color
}

int main(int argc, char* argv[])
{
    // Check if there are enough command line arguments
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1; // Exit with an error code
    }

    // Pass the input and output file names to the Compile function


    Compile(argv[1], argv[2]);

    if (_CrtDumpMemoryLeaks() == 0)
    {
        printGreenText(" ________   ________          ___       _______   ________  ___  __    ________              \n");
        printGreenText("|\\   ___  \\|\\   __  \\        |\\  \\     |\\  ___ \\ |\\   __  \\|\\  \\|\\  \\ |\\   ____\\             \n");
        printGreenText("\\ \\  \\\\ \\  \\ \\  \\|\\  \\       \\ \\  \\    \\ \\   __/|\\ \\  \\|\\  \\ \\  \\/  /|\\ \\  \\___|_            \n");
        printGreenText(" \\ \\  \\\\ \\  \\ \\  \\\\\\  \\       \\ \\  \\    \\ \\  \\_|/_\\ \\   __  \\ \\   ___  \\ \\_____  \\           \n");
        printGreenText("  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\       \\ \\  \\____\\ \\  \\_|\ \\\\ \\  \\ \\  \\ \\  \\\\ \\  \\|____|\\  \\          \n");
        printGreenText("   \\ \\__\\\\ \\__\\ \\_______\\       \\ \\_______\\ \\_______\\\\ \\__\\ \\__\\ \\__\\\\ \\__\\____\\_\\  \\         \n");
        printGreenText("    \\|__| \\|__|\\|_______|        \\|_______|\\|_______| \\|__|\\|__|\\|__| \\|__|\\_________\\        \n");
        printGreenText("                                                                                   \\|_________|        \n");
        printGreenText("                                                                                             \n");
        printGreenText(" ___       _______  _________  ________           ________  ________          ___  ___       \n");
        printGreenText("|\\  \\     |\\  ___ \\|\\___   ___\\\\   ____\\         |\\   ____\\|\\   __  \\        |\\  \\|\\  \\      \n");
        printGreenText("\\ \\  \\    \\ \\   __/\\|___ \\  \\_\\ \\  \\___|_        \\ \\  \\___|\\ \\  \\|\\  \\       \\ \\  \\ \\  \\     \n");
        printGreenText(" \\ \\  \\    \\ \\  \\_|/__  \\ \\  \\ \\ \\_____  \\        \\ \\  \\  __\\ \\  \\\\\\  \\       \\ \\  \\ \\  \\    \n");
        printGreenText("  \\ \\  \\____\\ \\  \\_|\ \\  \\ \\  \\ \\|____|\\  \\        \\ \\  \\|\\  \\ \\  \\\\\\  \\       \\ \\__\\ \\__\\   \n");
        printGreenText("   \\ \\_______\\ \\_______\\  \\ \\__\\  ____\\_\\  \\        \\ \\_______\\ \\_______\\       \\|__|\\|__|   \n");
        printGreenText("    \\|_______|\\|_______|   \\|__| |\\_________\\        \\|_______|\\|_______|           ___  ___ \n");
        printGreenText("                                 \\|_________|                                      |\\__\\|\\__\\\n");
        printGreenText("                                                                                   \\|__|\\|__|\n");
        printGreenText("                                                                                             \n");

    }
    else
    {
        printRedText("  ___    ___ _______   ________           ___       _______   ________  ___  __    ________      \n");
        printRedText(" |\\  \\  /  /|\\  ___ \\ |\\   ____\\         |\\  \\     |\\  ___ \\ |\\   __  \\|\\  \\|\\  \\ |\\   ____\\     \n");
        printRedText(" \\ \\  \\/  / | \\   __/|\\ \\  \\___|_        \\ \\  \\    \\ \\   __/|\\ \\  \\|\\  \\ \\  \\/  /|\\ \\  \\___|_    \n");
        printRedText("  \\ \\    / / \\ \\  \\_|/_\\ \\_____  \\        \\ \\  \\    \\ \\  \\_|/_\\ \\   __  \\ \\   ___  \\ \\_____  \\   \n");
        printRedText("   \\/  /  /   \\ \\  \\_|\ \|____|\\  \\        \\ \\  \\____\\ \\  \\_|\ \|\\ \\  \\ \\  \\ \\  \\\\ \\  \\|____|\\  \\  \n");
        printRedText(" __/  / /      \\ \\_______\\____\\_\\  \\        \\ \\_______\\ \\_______\\ \\__\\ \\__\\ \\__\\\\ \\__\\____\\_\\  \\ \n");
        printRedText("|\\___/ /        \\|_______|\_________\\        \\|_______|\\|_______|\\|__|\\|__|\\|__| \\|__|\\_________\\\n");
        printRedText("\\|___|/                  \\|_________|                                                \\|_________|\n");
        printRedText("                                                                                                 \n");
        printRedText("                                                                                                 \n");
        printRedText("  ________  ________  ________  ___  ___  ________  ________          ________                    \n");
        printRedText(" |\\   __  \\|\\   __  \\|\\   __  \\|\\  \\|\\  \\|\\   __  \\|\\   __  \\        |\\   ___ \\  ___              \n");
        printRedText(" \\ \\  \\|\\ /\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\|\\  \\       \\ \\  \\_|\ \\|\\__\\             \n");
        printRedText("  \\ \\   __  \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\   __  \\ \\  \\\\\\  \\ \\  \\\\\\  \\       \\ \\  \\ \\ \\|__|             \n");
        printRedText("   \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\ \\  \\\\\\  \\ \\  \\\\\\  \\       \\ \\  \\_\\ \\  ___           \n");
        printRedText("    \\ \\_______\\ \\_______\\ \\_______\\ \\__\\ \\__\\ \\_______\\ \\_______\\       \\ \\_______\\|\\__\\          \n");
        printRedText("     \\|_______|\\|_______|\\|_______|\\|__|\\|__|\\|_______|\\|_______|        \\|_______|\\|__|          \n");
        printRedText("                                                                                                 \n");
        printRedText("                                                                                                 \n");
    }

    return 0; // Exit successfully
}