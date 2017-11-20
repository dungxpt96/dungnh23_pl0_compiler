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
				lastColumn = lastLengthLine;
			}
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" SEMICOLON or LBRACK expected\n");
			exit(1);
			break;
		}
		case 18:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" VAR or IDENT expected\n");
			exit(1);
			break;
		}
		case 19:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" RPARENT expected\n");
			exit(1);
			break;
		}
		case 20:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" SEMICOLON expected\n");
			exit(1);
			break;
		}
		case 21:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" IDENT expected\n");
			exit(1);
			break;
		}
		case 22:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" END expected\n");
			exit(1);
			break;
		}
		case 23:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" RBRACK expected\n");
			exit(1);
			break;
		}
		case 24:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" ASSIGN expected\n");
			exit(1);
			break;
		}
		case 25:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" Factor expected\n");
			exit(1);
			break;
		}
		case 26:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" THEN expected\n");
			exit(1);
			break;
		}
		case 27:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" DO expected\n");
			exit(1);
			break;
		}
		case 28:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" TO expected\n");
			exit(1);
			break;
		}
		case 29:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
			}
			printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
			printf(" Condition: Syntax unexpected\n");
			exit(1);
			break;
		}
		case 35:
		{
			if (lastColumn == 0)
			{
				lastLine --;
				lastColumn = lastLengthLine;
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
				lastColumn = lastLengthLine;
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
	
	if ((token != NULL) && (token->type == VAR))
	{
		handleVarBlock();
	}
	
	if ((token != NULL) && (token->type == PROCEDURE))
	{
		handleProcedureBlock();
	}
	
	if ((token != NULL) && (token->type == BEGIN))
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
		if ((token != NULL) && (token->type == EQU))
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
}

void handleProcedureBlock()
{
	token = getToken();
	if ((token != NULL) && (token->type == IDENT))
	{
		token = getToken();
		if ((token != NULL) && (token->type == LPARENT))
		{
			token = getToken();
			if ((token != NULL) && (token->type == VAR))
			{
				token = getToken();
				if ((token != NULL) && (token->type == IDENT))
				{
					token = getToken();
				}
			}
			else if ((token != NULL) && (token->type == IDENT))
			{
				token = getToken();
			}
			else
			{
				error(18);
			}

			while ((token != NULL) && (token->type == SEMICOLON))
			{
				token = getToken();
				if ((token != NULL) && (token->type == VAR))
				{
					token = getToken();
					if ((token != NULL) && (token->type == IDENT))
					{
						token = getToken();
					}
					else
					{
						error(21);
					}
				}
				else if ((token != NULL) && (token->type == IDENT))
				{
					token = getToken();
				}
				else
				{
					error(18);
				}
			}

			if ((token != NULL) && (token->type == RPARENT))
			{
				token = getToken();
			}
			else
			{
				error(19);
			}
		}

		if ((token != NULL) && (token->type == SEMICOLON))
		{
			token = getToken();
			compileBlock();
			if ((token != NULL) && (token->type == SEMICOLON))
			{
				token = getToken();
				if ((token != NULL) && (token->type == PROCEDURE))
				{
					handleProcedureBlock();
				}
			}
			else
			{
				error(20);
			}
		}
		else
		{
			error(20);
		}
	}
	else
	{
		error(21);
	}
	compileBlock();
}

void handleBeginEndBlock()
{
	compileStatement();

	while ((token != NULL) && (token->type == SEMICOLON)) /***/
	{
		compileStatement();
	}

	if ((token != NULL) && (token->type == END))
	{
		token = getToken();
	}
	else
	{
		error(22);
	}
}

void compileStatement()
{
	token = getToken();
	if ((token != NULL) && (token->type == IDENT))
	{
		token = getToken();

		if ((token != NULL) && (token->type == LBRACK))
		{
			compileExpression();
			if ((token != NULL) && (token->type == RBRACK))
			{
				token = getToken();
			}
			else
			{
				error(23);
			}
		}

		if ((token != NULL) && (token->type == ASSIGN))
		{
			compileExpression();
		}
		else
		{
			error(24);
		}
	}
	else if ((token != NULL) && (token->type == CALL))
	{
		token = getToken();
		if ((token != NULL) && (token->type == IDENT))
		{
			token = getToken();

			if ((token != NULL) && (token->type == LPARENT))
			{
				compileExpression();
				while((token != NULL) && (token->type == COMMA))
					compileExpression();
				if ((token != NULL) && (token->type == RPARENT))
				{
					token = getToken();
				}
				else
					error(19);
			}
		}
		else{
			error(21);
		}
	}
	else if ((token != NULL) && (token->type == BEGIN))
	{
		compileStatement();
		while((token != NULL) && (token->type == SEMICOLON))
		{
			compileStatement();
		}

		if ((token != NULL) && (token->type == END))
		{
			token = getToken();
		}
		else
		{
			error(22);
		}
	}
	else if ((token != NULL) && (token->type == IF))
	{
		compileCondition();
		if ((token != NULL) && (token->type == THEN))
		{
			compileStatement();

			if ((token != NULL) && (token->type == ELSE))
			{
				compileStatement();
			}
		}
		else
		{
			error(26); // thieu THEN
		}
	}
	else if ((token != NULL) && (token->type == WHILE))
	{
		compileCondition();

		if ((token != NULL) && (token->type == DO))
		{
			compileStatement();
		}
		else
		{
			error(27); // thieu DO
		}
	}
	else if ((token != NULL) && (token->type == FOR))
	{
		token = getToken();
		if ((token == NULL) || (token->type != IDENT))
			error(21);

		token = getToken();
		if ((token == NULL) || (token->type != ASSIGN))
			error(21);

		compileExpression();

		if ((token == NULL) || (token->type != TO))
			error(28);

		compileExpression();

		if ((token == NULL) || (token->type != DO))
			error(27);

		compileStatement();
	}
}

void compileExpression()
{
	token = getToken();
	if ((token != NULL) && ((token->type == PLUS) || (token->type == MINUS)))
	{
		token = getToken();
	}

	compileTerm();

	while ((token != NULL) && ((token->type == PLUS) || (token->type == MINUS)))
	{
		token = getToken();
		compileTerm();
	}
}

void compileTerm()
{
	compileFactor();
	while ((token != NULL) && ((token->type == TIMES) || (token->type == SLASH) || (token->type == PERCENT)))
	{
		token = getToken();
		compileFactor();
	}
}

void compileFactor()
{
	if ((token != NULL) && (token->type == IDENT))
	{
		token = getToken();
		if ((token != NULL) && (token->type == LBRACK))
		{
			compileExpression();
			if ((token != NULL) && (token->type == RBRACK))
			{
				token = getToken();
			}
			else
			{
				error(23);
			}
		}
	}
	else if ((token != NULL) && (token->type == NUMBER))
	{
		token = getToken();
	}
	else if ((token != NULL) && (token->type == LPARENT))
	{
		compileExpression();
		if ((token != NULL) && (token->type == RPARENT))
		{
			token = getToken();
		}
		else
		{
			error(19);
		}
	}
	else
	{
		error(25);
	}
}

void compileCondition()
{
	compileExpression();

	if ((token != NULL) && ( (token->type == EQU) || (token->type == NEQ) ||
		(token->type == LSS) || (token->type == LEQ) || (token->type == GRT) ||
		(token->type == GEQ)))
	{
		compileExpression();
	}
	else
	{
		error(29);
	}
}
