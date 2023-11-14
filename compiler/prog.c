#include "Compiler.h"
#include <stdio.h>


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

    return 0; // Exit successfully
}
