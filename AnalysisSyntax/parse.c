#include "parse.h"
#include "scanner.h"

void compile(const char *filename)
{
	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		error(37);
	}
	numLine = lastLine = 1;
	numColumn = lastColumn = 0;
	isComment = 0;
	numToken = 0;
	lastLengthLine = 0;
	begin = 1;
	hasBlock = 0;
	ch = getChar();
	//token = (token_t *) malloc(sizeof(token_t));
	/*
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
		}
	} while (token != NULL); //*/

	token = getToken();
	if (token != NULL)
	{
		compileProgram();
	}
	else
	{
		error(35);
	}

	/*
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
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf("Number too long\n");
			exit(1);
			break;
		}
		case 2:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf("Invalid symbol\n");
			exit(1);
			break;
		}
		case 3:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf("Keyword PROGRAM expected\n");
			exit(1);
			break;
		}
		case 4:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" IDENT expected after PROGRAM\n");
			exit(1);
			break;
		}
		case 5:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" SEMICOLON expected after IDENT\n");
			exit(1);
			break;
		}
		case 6:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" PERIOD expected to end program\n");
			exit(1);
			break;
		}
		case 7:
		{
			printf("\nWarning %d: Line:%d, Column:%d ::", id_error, numLine, numColumn);
			printf(" BLOCK expected declares Program\n");

			break;
		}
		case 8:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" IDENT expected after CONST keyword\n");
			exit(1);
			break;
		}
		case 9:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" ASSIGN expected after IDENT\n");
			exit(1);
			break;
		}
		case 10:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" NUMBER expected after ASSIGN\n");
			exit(1);
			break;
		}
		case 11:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" SEMICOLON expected to end CONST block\n");
			exit(1);
			break;
		}
		case 12:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" IDENT expected after COMMA in CONST block\n");
			exit(1);
			break;
		}
		case 13:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" IDENT expected after VAR keyword\n");
			exit(1);
			break;
		}
		case 14:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" IDENT expected after COMMA in VAR block\n");
			exit(1);
			break;
		}
		case 15:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" NUMBER expected after LBRACK in array var\n");
			exit(1);
			break;
		}
		case 16:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" RBRACK expected after NUMBER in VAR block\n");
			exit(1);
			break;
		}
		case 17:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" SEMICOLON or LBRACK expected\n");
			exit(1);
			break;
		}
		case 35:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf("Invalid file input, PL0 program expected\n");
			exit(1);
			break;
		}
		case 36:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine - 1;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf("Invalid symbol\n");
			exit(1);
			break;
		}
		case 37:
		{
			printf("No such file or directory\n");
			exit(1);
			break;
		}
		default:
		{

		}
	}
}


/*
typedef enum {
	NONE = 0,
	IDENT,
	NUMBER,
	BEGIN, 
	END, 
	IF, 
	THEN, 
	WHILE,
	DO, 
	CALL, 
	ODD, 
	TO,
	CONST,
	VAR, 
	PROCEDURE, 
	PROGRAM,
	ELSE, 
	FOR, 
	PLUS,	
	MINUS, 	
	TIMES, 	
	SLASH,
	EQU, 
	NEQ, 
	LSS,	
	LEQ,		
	GRT,		
	GEQ, 		
	LPARENT, 
	RPARENT,
	LBRACK, 
	RBRACK, 
	PERIOD, 	
	COMMA, 	
	SEMICOLON, 
	ASSIGN, 
	PERCENT
} TokenType;
*/
void compileProgram()
{
	if ((token != NULL) && (token->type == PROGRAM))
	{
		token = getToken();
		if ((token != NULL) && (token->type == IDENT))
		{
			token = getToken();
			if ((token != NULL) && (token->type == SEMICOLON))
			{
				token = getToken();
				compileBlock();
				if ((token != NULL) && (token->type == PERIOD))
				{
					printf("\nCompile Sucessfully\n");
				}
				else
				{
					error(6);
				}
			}
			else
			{
				error(5);
			}
			
		}
		else
		{
			error(4);
		}
	}
	else
	{
		error(3);
	}
}

void compileBlock()
{
	if ((token != NULL) && (token->type == CONST))
	{
		handleConstBlock();
	}
	else if ((token != NULL) && (token->type == VAR))
	{
		handleVarBlock();
	}
	else if ((token != NULL) && (token->type == PROCEDURE))
	{
		handleProcedureBlock();
	}
	else if ((token != NULL) && (token->type == BEGIN))
	{
		handleBeginEndBlock();
	}
	if (hasBlock == 0)
		error(7);
}

void handleConstBlock()
{
	hasBlock = 1;
	token = getToken();
	if ((token != NULL) && (token->type == IDENT))
	{
		token = getToken();
		if ((token != NULL) && (token->type == ASSIGN))
		{
			token = getToken();
			if ((token != NULL) && (token->type == NUMBER))
			{
				token = getToken();

				/* Check comma */
				while ((token != NULL) && (token->type == COMMA))
				{
					token = getToken();
					if ((token != NULL) && (token->type == IDENT))
					{
						token = getToken();
						if ((token != NULL) && (token->type == ASSIGN))
						{
							token = getToken();
							if ((token != NULL) && (token->type == NUMBER))
							{
								token = getToken();
							}
							else
								error(10);
						}
						else
							error(9);
					}
					else
						error(12);
				}

				/* check Semicolon */
				if ((token != NULL) && (token->type == SEMICOLON))
				{
					token = getToken();
				}
				else
					error(11);

			}
			else
				error(10);
		}
		else
			error(9);
	}
	else
		error(8);

	compileBlock();
}

void handleVarBlock()
{
	hasBlock = 1;
	token = getToken();
	if ((token != NULL) && (token->type == IDENT))
	{
		token = getToken();
		if ((token != NULL) && (token->type == LBRACK))
		{
			while ((token != NULL) && (token->type == LBRACK))
			{
				token = getToken();
				if ((token != NULL) && (token->type == NUMBER))
				{
					token = getToken();
					if ((token != NULL) && (token->type == RBRACK))
					{
						token = getToken();
					}
					else
						error(16);
				}
				else
					error(15);
			}
		}
		
		if ((token != NULL) && (token->type == COMMA))
		{
			while ((token != NULL) && (token->type == COMMA))
			{
				token = getToken();
				if ((token != NULL) && (token->type == IDENT))
				{
					token = getToken();
					if ((token != NULL) && (token->type == LBRACK))
					{
						while ((token != NULL) && (token->type == LBRACK))
						{
							token = getToken();
							if ((token != NULL) && (token->type == NUMBER))
							{
								token = getToken();
								if ((token != NULL) && (token->type == RBRACK))
								{
									token = getToken();
								}
								else
									error(16);
							}
							else
								error(15);
						}
					}
				}
				else
					error(14);
			}
		}

		/* check Semicolon */
		if ((token != NULL) && (token->type == SEMICOLON))
		{
			token = getToken();
		}
		else
			error(17);
	}
	else
		error(13);

	compileBlock();
}
void handleProcedureBlock()
{
	compileBlock();
}
void handleBeginEndBlock()
{
	compileBlock();
}
