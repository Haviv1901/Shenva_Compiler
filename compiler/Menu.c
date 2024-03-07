#include "Menu.h"

#include <string.h>

#include "fileHelper.h"
#include "Flags.h"


/**
 * \brief function will parse input command and print the correct respond. also will parse and init flags
 * \param argc 
 * \param argv 
 * \return 1 if compile function should run, 0 if not
 */
int handleCommandLineArguments(int argc, char* argv[])
{

	if(argc > 4)
	{
		printUsage();
		return 0;
	}

	// Check if there are enough command line arguments
	if (argc == 1)
	{
		printWelcome();
		printUsage();
		return 0;
	}

	// Check if the first argument is a valid command
	if(argc == 2)
	{
		if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0)
		{
			printHelp();
		}
		return 0;
	}

	if(argc == 3)
	{
		return 1; // no flags
	}

	if(argc == 4)
	{
		// parse flags
		parseFlags(argv[3]);
	}

	return 1;

	


}

void printWelcome()
{
	printFile("Menu_Scripts/Welcome.txt");
}

void printHelp()
{
	printFile("Menu_Scripts/Help.txt");
}


void printUsage()
{
	printFile("Menu_Scripts/Usage.txt");
}



