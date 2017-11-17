#include "parse.h"
#include "scanner.h"

void compile(const char *filename)
{
	fp = fopen(filename, "r");
	numLine = 1;
	numColumn = 0;
	isComment = 0;
	numToken = 0;
	begin = 1;
	ch = getChar();
	//token = (token_t *) malloc(sizeof(token_t));
	do
	{
		token = getToken();
		
		if (token != NULL)
		{
			listToken[numToken].type = token->type;
			strcpy(listToken[numToken].name, token->name);
			numToken ++;
		}//*/
		/*
		if (token != NULL)
		{
			printf("%d - %s\n", token->type, token->name);
		}//*/
	} while (token != NULL);

	
	int i;
	for (i = 0; i < numToken; i++)
	{
		if (listToken[i].type == NUMBER)
		{
			printf("\nNUMBER(%s)", listToken[i].name);
		}
		else if (listToken[i].type == IDENT)
		{
			printf("\nIDENT(%s)", listToken[i].name);
		}
		else
		{
			printf("\n%s", listToken[i].name);
		}
	}//*/

	fclose(fp);
}

void error(int id_error)
{
	switch(id_error)
	{
		case 1: 
		{
			printf("\nError: Line:%d, Column:%d ::", numLine, numColumn);
			printf("Number too long\n");
			exit(1);
			break;
		}
		case 2:
		{
			printf("\nError: Line:%d, Column:%d ::", numLine, numColumn);
			printf("Invalid symbol\n");
			exit(1);
			break;
		}
		default:
		{

		}
	}
}