#include "scanner.h"
#include "parse.h"
#include "sematics.h"

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		printf("Error: Expected input file correctly!\n");
		showHelpCommand();
		exit(-1);
	}
	else if (argc > 2)
	{
		printf("Warning: Too many input arguments!\n");
		showHelpCommand();
		fileNameInput = argv[1];
		compile(argv[1]);
	}
	else
	{
		fileNameInput = argv[1];
		compile(argv[1]);
	}

	return 0;
}
