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

	token = getToken();
	if (token != NULL)
	{
		compileProgram();

		token = getToken();
		if (token != NULL)
			error(38);

		printf("\n");
		printf("                      ......................\n");
		printf("                      :   Compile Success  :\n");
		printf("                      :....................:\n");
	}
	else
	{
		error(35);
	}

	fclose(fp);
}

void error(int id_error)
{
	if (lastColumn == 0)
	{
		lastLine --;
		lastColumn = lastLengthLine;
	}
	int i;
	printf("\n      ");
	for(i = 1; i < lastColumn; i++)
	{
		printf(" ");
	}
	printf("^\n");

	printf("\nError %d: Line:%d, Column:%d ::", id_error, lastLine, lastColumn);
	switch(id_error)
	{
		case 1: 
		{			
			printf("Number too long\n");
			break;
		}
		case 2:
		{
			printf("Invalid symbol\n");
			break;
		}
		case 3:
		{			
			printf("Keyword PROGRAM expected\n");
			break;
		}
		case 4:
		{			
			printf(" IDENT expected after PROGRAM\n");
			break;
		}
		case 5:
		{			
			printf(" SEMICOLON expected after IDENT\n");
			break;
		}
		case 6:
		{			
			printf(" PERIOD expected to end program\n");
			break;
		}
		case 7:
		{
			printf(" BLOCK expected declares\n");
			break;
		}
		case 8:
		{			
			printf(" IDENT expected after CONST keyword\n");
			break;
		}
		case 9:
		{		
			printf(" EQU expected after IDENT\n");
			break;
		}
		case 10:
		{	
			printf(" NUMBER expected after ASSIGN\n");
			break;
		}
		case 11:
		{	
			printf(" SEMICOLON expected to end CONST block\n");
			break;
		}
		case 12:
		{			
			printf(" IDENT expected after COMMA in CONST block\n");
			break;
		}
		case 13:
		{			
			printf(" IDENT expected after VAR keyword\n");
			break;
		}
		case 14:
		{		
			printf(" IDENT expected after COMMA in VAR block\n");
			break;
		}
		case 15:
		{			
			printf(" NUMBER expected after LBRACK in array var\n");
			break;
		}
		case 16:
		{		
			printf(" RBRACK expected after NUMBER in VAR block\n");
			break;
		}
		case 17:
		{			
			printf(" SEMICOLON or LBRACK expected\n");
			break;
		}
		case 18:
		{		
			printf(" VAR or IDENT expected\n");
			break;
		}
		case 19:
		{			
			printf(" RPARENT or SEMICOLON expected\n");
			break;
		}
		case 20:
		{			
			printf(" SEMICOLON expected\n");
			break;
		}
		case 21:
		{			
			printf(" IDENT expected\n");
			break;
		}
		case 22:
		{			
			printf("END expected\n");
			break;
		}
		case 23:
		{			
			printf(" RBRACK expected\n");
			break;
		}
		case 24:
		{			
			printf(" ASSIGN expected\n");
			break;
		}
		case 25:
		{		
			printf(" Factor expected\n");
			break;
		}
		case 26:
		{		
			printf(" THEN expected\n");
			break;
		}
		case 27:
		{			
			printf(" DO expected\n");
			break;
		}
		case 28:
		{			
			printf(" TO expected\n");
			break;
		}
		case 29:
		{		
			printf(" Condition: Syntax unexpected\n");
			break;
		}
		case 35:
		{			
			printf("Invalid file input, PL0 program expected\n");
			break;
		}
		case 30:
		{			
			printf("END expected\n");
			break;
		}
		case 36:
		{		
			printf("Invalid symbol\n");
			break;
		}
		case 37:
		{
			printf("\"%s\" No such file or directory\n", fileNameInput);
			break;
		}
		case 38:
		{
			printf("Character unexpects after program was finished.\n");
			exit(1);
			break;
		}
		default:
		{

		}
	}

	exit(1);
}

void compileProgram()
{
	if ((token == NULL) || (token->type != PROGRAM))
		error(3);

	token = getToken();
	if ((token == NULL) || (token->type != IDENT))
		error(4);

	token = getToken();
	if ((token == NULL) || (token->type != SEMICOLON))
		error(5);
	
	token = getToken();
	compileBlock();

	if ((token == NULL) || (token->type != PERIOD))
		error(6);
}


void compileBlock()
{
	if ((token == NULL) || ((token->type != CONST) && (token->type != VAR) && (token->type != PROCEDURE) && 
			(token->type != BEGIN)))
		error(7);

	if (token->type == CONST)
	{
		token = getToken();
		handleConstBlock();
	}
	
	if (token->type == VAR)
	{
		token = getToken();
		handleVarBlock();
	}
	
	if (token->type == PROCEDURE)
	{
		token = getToken();
		handleProcedureBlock();
	}
	
	if (token->type == BEGIN)
	{
		token = getToken();
		handleBeginEndBlock();
	}
}

void handleConstBlock()
{
	hasBlock = 1;

	if ((token == NULL) || (token->type != IDENT))
		error(8);

	token = getToken();
	if ((token == NULL) || (token->type != EQU))
		error(9);

	token = getToken();
	if ((token == NULL) || (token->type != NUMBER))
		error(10);

	token = getToken();

	while ((token != NULL) && (token->type == COMMA))
	{
		token = getToken();
		if ((token == NULL) || (token->type != IDENT))
			error(12);

		token = getToken();
		if ((token == NULL) || (token->type != EQU))
			error(9);

		token = getToken();
		if ((token == NULL) || (token->type != NUMBER))
			error(10);

		token = getToken();
	}

	if ((token == NULL) || (token->type != SEMICOLON))
		error(11);

	token = getToken();
	
}

void handleVarBlock()
{
	hasBlock = 1;

	if ((token == NULL) || (token->type != IDENT))
		error(13);

	token = getToken();
	if ((token != NULL) && (token->type == LBRACK))
	{
		token = getToken();
		if ((token == NULL) || (token->type != NUMBER))
			error(15);

		token = getToken();
		if ((token == NULL) || (token->type != RBRACK))
			error(16);

		token = getToken();
	}

	while ((token != NULL) && (token->type == COMMA))
	{
		token = getToken();
		if ((token == NULL) || (token->type != IDENT))
			error(14);

		token = getToken();
		if ((token != NULL) && (token->type == LBRACK))
		{
			token = getToken();
			if ((token == NULL) || (token->type != NUMBER))
				error(15);

			token = getToken();
			if ((token == NULL) || (token->type != RBRACK))
				error(16);

			token = getToken();
		}
	}

	if ((token == NULL) || (token->type != SEMICOLON))
		error(17);

	token = getToken();
}

void handleProcedureBlock()
{
	if ((token == NULL) || (token->type != IDENT))
		error(21);

	token = getToken();
	if ((token != NULL) && (token->type == LPARENT))
	{
		token = getToken();
		/* If not VAR or ident => error */

		if ((token == NULL) || ((token->type != VAR) && (token->type != IDENT)))
			error(18);
		if (token->type == VAR)
		{
			token = getToken();
			if ((token == NULL) || (token->type != IDENT))
				error(17);
		}
		/*  certain it is Ident */
		token = getToken();

		while ((token != NULL) && (token->type == SEMICOLON))
		{
			token = getToken();
			/* If not VAR or ident => error */
			if ((token == NULL) || ((token->type != VAR) && (token->type != IDENT)))
				error(18);

			if (token->type == VAR)
			{
				token = getToken();
				if ((token == NULL) || (token->type != IDENT))
					error(17);
			}
			/*  certain it is Ident */
			token = getToken();
		}

		if ((token == NULL) || (token->type != RPARENT))
			error(19);

		token = getToken();
	}
	/* Next is semicolon */
	if ((token == NULL) || (token->type != SEMICOLON))
		error(20);

	token =getToken();
	compileBlock();

	if ((token == NULL) || (token->type != SEMICOLON))
		error(20);
	token = getToken();

	if ((token != NULL) && (token->type == PROCEDURE))
	{
		token = getToken();
		handleProcedureBlock();
	}
}

void handleBeginEndBlock()
{
	compileStatement();

	/* Check token which compileStatement generated */
	while ((token != NULL) && (token->type == SEMICOLON)) /***/
	{
		token = getToken();
		compileStatement();
	}

	if ((token == NULL) || (token->type != END))
		error(22);

	token = getToken();
}

void compileStatement()
{
	if ((token != NULL) && (token->type == IDENT))
	{
		token = getToken();

		if ((token != NULL) && (token->type == LBRACK))
		{
			token = getToken();
			compileExpression();
			if ((token == NULL) || (token->type != RBRACK))
				error(23);

			token = getToken();
		}

		if ((token == NULL) || (token->type != ASSIGN))
			error(24);

		token = getToken();
		compileExpression();
	}
	else if ((token != NULL) && (token->type == CALL))
	{
		token = getToken();
		compileCallStatement();
	}
	else if ((token != NULL) && (token->type == BEGIN))
	{
		token = getToken();
		compileBeginEndStatement();
	}
	else if ((token != NULL) && (token->type == IF))
	{
		token = getToken();
		compileIfElseStatement();
	}
	else if ((token != NULL) && (token->type == WHILE))
	{
		token = getToken();
		compileWhileStatement();
	}
	else if ((token != NULL) && (token->type == FOR))
	{
		token = getToken();
		compileForStatement();
	}
}

void compileCallStatement()
{
	if ((token == NULL) || (token->type != IDENT))
			error(21);

	token = getToken();

	if ((token != NULL) && (token->type == LPARENT))
	{
		token = getToken();
		compileExpression();

		while((token != NULL) && (token->type == COMMA))
		{
			token = getToken();
			compileExpression();
		}

		if ((token == NULL) || (token->type != RPARENT))
			error(19);

		token = getToken();
	}
}

void compileBeginEndStatement()
{
	compileStatement();

	while((token != NULL) && (token->type == SEMICOLON))
	{
		token = getToken();
		compileStatement();
	}

	if ((token == NULL) || (token->type != END))
		error(22);

	token = getToken();
}

void compileIfElseStatement()
{
	compileCondition();

	if ((token == NULL) || (token->type != THEN))
		error(26);

	token = getToken();
	compileStatement();

	if ((token != NULL) && (token->type == ELSE))
	{	
		token = getToken();
		compileStatement();
	}
}

void compileWhileStatement()
{
	compileCondition();

	if ((token == NULL) || (token->type != DO))
		error(27);

	token = getToken();
	compileStatement();
}

void compileForStatement()
{
	if ((token == NULL) || (token->type != IDENT))
		error(21);

	token = getToken();
	if ((token == NULL) || (token->type != ASSIGN))
		error(24);

	token = getToken();
	compileExpression();

	if ((token == NULL) || (token->type != TO))
		error(28);

	token = getToken();
	compileExpression();

	if ((token == NULL) || (token->type != DO))
		error(27);

	token = getToken();
	compileStatement();
}


void compileExpression()
{
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
			token = getToken();
			compileExpression();
			if ((token == NULL) || (token->type != RBRACK))
				error(23);

			token = getToken();
		}
	}
	else if ((token != NULL) && (token->type == NUMBER))
	{
		token = getToken();
	}
	else if ((token != NULL) && (token->type == LPARENT))
	{
		token = getToken();
		compileExpression();
		if ((token == NULL) || (token->type != RPARENT))
			error(19);

		token = getToken();
	}
	else
	{
		error(25);
	}
}

void compileCondition()
{
	if ((token != NULL) && (token->type == ODD))
	{
		token = getToken();
		compileExpression();
		return;
	}

	compileExpression();

	if ((token != NULL) && ( (token->type == EQU) || (token->type == NEQ) ||
		(token->type == LSS) || (token->type == LEQ) || (token->type == GRT) ||
		(token->type == GEQ)))
	{
		token = getToken();
		compileExpression();
	}
	else
	{
		error(29);
	}
}
