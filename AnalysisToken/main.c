#include "scanner.h"
#include "parse.h"

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
		compile(argv[1]);
	}
	else
	{
		compile(argv[1]);
	}

	printf("\n---Compile Successfully\n");

	return 0;
}
