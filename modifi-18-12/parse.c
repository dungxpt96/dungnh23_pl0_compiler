#include "parse.h"
#include "scanner.h"
#include "sematics.h"

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
	countSymbolTable = 1;
	cur_level = 1;
	cur_numTable = 1;
	checkExpressionIsIdent = 0;
	sTb[0].parentSymbolTable = -1; // Bang goc khong co CHA
	sTb[0].levelOfTable = cur_level;
	location_id = (location_t *) malloc(sizeof(location_t));
	code_size = 0;

	/* ------------------------------------------ */
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

		print_code();
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
			printf(" IDENT expected after CONST keyword or COMMA in CONST block\n");
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
			printf(" IDENT expected after VAR keyword or after COMMA in VAR block\n");
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
		case 31:
		{			
			printf("Ident undeclared (first use in this function)\n");
			break;
		}
		case 32:
		{			
			printf("Previous declaration of this ident was here\n");
			break;
		}
		case 33:
		{			
			printf("Incompatible types when assigning to type, Ident must be Variable or Array type\n");
			break;
		}
		case 40:
		{			
			printf("BEGIN-END block expected\n");
			break;
		}
		case 41:
		{			
			printf("Assignment of read-only CONST variable\n");
			break;
		}
		case 42:
		{			
			printf("Incompatible types when assigning to type, ident is Array\n");
			break;
		}
		case 43:
		{			
			printf("Ident must be PROCEDURE types in Call statement\n");
			break;
		}
		case 44:
		{			
			printf("Ident undeclared or must be VARIABLE types in For statement\n");
			break;
		}
		case 45:
		{			
			printf("Incompatible types, argument in procedure must be VAR_TYPE or CONST_TYPE\n");
			break;
		}
		case 46:
		{			
			printf("Incompatible Argument types, TYPE must be VAR_TYPE\n");
			break;
		}
		case 47:
		{			
			printf("Factor is not procedure type\n");
			break;
		}
		case 48:
		{			
			printf("Argument expected in Call procedure\n");
			break;
		}
		case 49:
		{			
			printf("Invalid number Arguments in Call procedure, check number Argument\n");
			break;
		}
		case 50:
		{			
			printf("SEMICOLON expected between statements\n");
			break;
		}
		case 51:
		{			
			printf("Index of array is too low or too big\n");
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

	if ((token != NULL) && token->type == CONST)
	{
		token = getToken();
		handleConstBlock();
	}
	
	if ((token != NULL) && token->type == VAR)
	{
		token = getToken();
		handleVarBlock();
	}
	
	if ((token != NULL) && token->type == PROCEDURE)
	{
		token = getToken();
		handleProcedureBlock();
	}
	
	if ((token != NULL) && (token->type == BEGIN))
	{
		token = getToken();
		handleBeginEndBlock();
		cur_level--;
		cur_numTable--;
	}
	else
		error(40);
}

void handleConstBlock()
{
	hasBlock = 1;

	compileDeclareConst();

	while ((token != NULL) && (token->type == COMMA))
	{
		token = getToken();
		compileDeclareConst();
	}

	if ((token == NULL) || (token->type != SEMICOLON))
		error(11);

	token = getToken();
	
}

void handleVarBlock()
{
	hasBlock = 1;

	compileDeclareVar();

	while ((token != NULL) && (token->type == COMMA))
	{
		token = getToken();
		compileDeclareVar();
	}

	if ((token == NULL) || (token->type != SEMICOLON))
		error(17);

	token = getToken();
}

void handleProcedureBlock()
{
	compileDeclareProcedure();
	if ((token != NULL) && (token->type == LPARENT))
	{
		token = getToken();
		/* If not VAR or ident => error */

		if ((token == NULL) || ((token->type != VAR) && (token->type != IDENT)))
			error(18);
		if (token->type == IDENT)
		{
			addDeclareVariableInProcedure();
			int curOb = sTb[countSymbolTable - 1].numArguments;
			sTb[countSymbolTable - 1].ot[curOb] = ARG_VALUE;
			strcpy(sTb[countSymbolTable - 1].otString[curOb], token->name);
			sTb[countSymbolTable - 1].numArguments ++;
			printf("\nIdent:%s==Number:%d==\n", token->name, sTb[countSymbolTable - 1].numArguments);
		}

		if (token->type == VAR)
		{
			token = getToken();
			addDeclareVariableInProcedure();
			int curOb = sTb[countSymbolTable - 1].numArguments;
			sTb[countSymbolTable - 1].ot[curOb] = VAR_TYPE;
			strcpy(sTb[countSymbolTable - 1].otString[curOb], token->name);
			sTb[countSymbolTable - 1].numArguments ++;
			printf("\nIdent:%s==Number:%d==\n", token->name, sTb[countSymbolTable - 1].numArguments);
		}
		/*  certain it is Ident */
		token = getToken();

		while ((token != NULL) && (token->type == SEMICOLON))
		{
			token = getToken();
			/* If not VAR or ident => error */
			if ((token == NULL) || ((token->type != VAR) && (token->type != IDENT)))
				error(18);
			if (token->type == IDENT)
			{
				addDeclareVariableInProcedure();
				int curOb = sTb[countSymbolTable - 1].numArguments;
				sTb[countSymbolTable - 1].ot[curOb] = ARG_VALUE;
				strcpy(sTb[countSymbolTable - 1].otString[curOb], token->name);
				sTb[countSymbolTable - 1].numArguments ++;
				printf("\nIdent:%s==Number:%d==\n", token->name, sTb[countSymbolTable - 1].numArguments);

			}
			if (token->type == VAR)
			{
				token = getToken();
				addDeclareVariableInProcedure();
				int curOb = sTb[countSymbolTable - 1].numArguments;
				sTb[countSymbolTable - 1].ot[curOb] = VAR_TYPE;
				strcpy(sTb[countSymbolTable - 1].otString[curOb], token->name);
				sTb[countSymbolTable - 1].numArguments ++;
				printf("\nIdent:%s==Number:%d==\n", token->name, sTb[countSymbolTable - 1].numArguments);
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

	if ((token != NULL) && ((token->type == IDENT) || (token->type == CALL)|| (token->type == BEGIN)
		|| (token->type == IF)|| (token->type == WHILE)|| (token->type == FOR)))
	{
		error(50);
	}
	if ((token == NULL) || (token->type != END))
		error(22);

	token = getToken();
}

void compileStatement()
{
	if ((token != NULL) && (token->type == IDENT))
	{
		int token_value = getValue(token->name);

		char temp_name[100];
		strcpy(temp_name, token->name);

		handleIdentStatement();

		location_id = location_ident(temp_name);

		printf("\n Find %d - %d \n", location_id->base, location_id->offset);

		to_code(OP_LA, location_id->base, location_id->offset);
		if ((token != NULL) && (token->type == LBRACK))
		{
			to_code(OP_LC, 1, 0);
		}

		if ((token != NULL) && (token->type == LBRACK))
		{
			token = getToken();
			if((token != NULL) && (token->type == NUMBER))
			{
				int value = atoi(token->name);
				if (value < 0 || value >=  token_value)
				{
					error(51);
				}
			}
			compileExpression();
			to_code(OP_MUL, 0, 0);
			to_code(OP_ADD, 0, 0);
			to_code(OP_LI, 0, 0);

			if ((token == NULL) || (token->type != RBRACK))
				error(23);

			token = getToken();
		}

		if ((token == NULL) || (token->type != ASSIGN))
			error(24);

		token = getToken();
		compileExpression();
		to_code(OP_ST, 0, 0);
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
	int index = getTable(token->name);

	handleIdentCallStatement();
	if (((token != NULL) && (token->type != LPARENT)) && sTb[index].numArguments > 0)
	{
		error(48);
	}
	int countArg = 0;

	if ((token != NULL) && (token->type == LPARENT))
	{
		token = getToken();
		char temp_name[100];
		strcpy(temp_name, token->name);

		checkExpressionIsIdent = 0;
		
		/* Kiem tra token co phai ident hay khong */
		compileExpression();
		if (checkExpressionIsIdent == 0)
		{
			/* is ident */
			if (sTb[index].ot[countArg] == VAR_TYPE)
			{
				objectType t = getKind(temp_name);

				if (t != VAR_TYPE)
				{
					error(46);
				}
			}

		}
		countArg ++;
		while((token != NULL) && (token->type == COMMA))
		{
			token = getToken();
			char temp_name[100];
			strcpy(temp_name, token->name);
			checkExpressionIsIdent = 0;
			compileExpression();
			if (checkExpressionIsIdent == 0)
			{
				/* is ident */
				if (sTb[index].ot[countArg] == VAR_TYPE)
				{
					objectType t = getKind(temp_name);

					if (t != VAR_TYPE)
					{
						error(46);
					}
				}

			}
			countArg ++;
		}

		if ((token == NULL) || (token->type != RPARENT))
			error(19);

		token = getToken();

		printf("\n==%d==%d==\n", countArg, sTb[index].numArguments);
		if (countArg != sTb[index].numArguments)
		{
			error(49);
		}
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

	if ((token != NULL) && ((token->type == IDENT) || (token->type == CALL)|| (token->type == BEGIN)
		|| (token->type == IF)|| (token->type == WHILE)|| (token->type == FOR)))
	{
		error(50);
	}

	if ((token == NULL) || (token->type != END) )
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
	handleIdentForStatement();
	
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
	objectType ob;
	if ((token != NULL) && ((token->type == PLUS) || (token->type == MINUS)))
	{
		ob = token->type;
		checkExpressionIsIdent = 1;
		token = getToken();
	}

	compileTerm();

	if (ob == PLUS)
	{
		to_code(OP_ADD, 0, 0);
	}
	else if (ob == MINUS)
	{
		to_code(OP_SUB, 0, 0);
	}

	while ((token != NULL) && ((token->type == PLUS) || (token->type == MINUS)))
	{
		ob = token->type;
		token = getToken();
		compileTerm();

		if (ob == PLUS)
		{
			to_code(OP_ADD, 0, 0);
		}
		else if (ob == MINUS)
		{
			to_code(OP_SUB, 0, 0);
		}
	}
}

void compileTerm()
{
	compileFactor();
	while ((token != NULL) && ((token->type == TIMES) || (token->type == SLASH) || (token->type == PERCENT)))
	{
		objectType ob = token->type;
		checkExpressionIsIdent = 1;
		token = getToken();
		compileFactor();

		if (ob == TIMES)
		{
			to_code(OP_MUL, 0, 0);
		}
		else if (ob == SLASH)
		{
			to_code(OP_DIV, 0, 0);
		}
	}
}

void compileFactor()
{
	if ((token != NULL) && (token->type == IDENT))
	{
		int token_value = getValue(token->name);

		char temp_name[100];
		strcpy(temp_name, token->name);

		handleFactorIdent();

		/* Gen code if ident is var or array */
		location_id = location_ident(temp_name);
		printf("\n Factor %d - %d \n", location_id->base, location_id->offset);
		
		if ((token != NULL) && (token->type == LBRACK))
		{
			to_code(OP_LA, location_id->base, location_id->offset);
			to_code(OP_LC, 1, 0);
		}
		else
		{
			to_code(OP_LV, location_id->base, location_id->offset);
		}

		if ((token != NULL) && (token->type == LBRACK))
		{
			token = getToken();
			if((token != NULL) && (token->type == NUMBER))
			{
				int value = atoi(token->name);
				if (value < 0 || value >=  token_value)
				{
					error(51);
				}
			}
			compileExpression();
			to_code(OP_MUL, 0, 0);
			to_code(OP_ADD, 0, 0);
			to_code(OP_LI, 0, 0);
			if ((token == NULL) || (token->type != RBRACK))
				error(23);

			token = getToken();
		}
	}
	else if ((token != NULL) && (token->type == NUMBER))
	{
		int num = atoi(token->name);
		to_code(OP_LC, num, 0);

		checkExpressionIsIdent = 1;
		token = getToken();
	}
	else if ((token != NULL) && (token->type == LPARENT))
	{
		checkExpressionIsIdent = 1;
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

/* ------------------------------------------------- */
void to_code(OpCode op, int p, int q)
{
	m_code[code_size].op = op;
	m_code[code_size].p = p;
	m_code[code_size].q = q;
	code_size ++;
}

void print_code()
{
	int i;
	printf("\n-----------------------------------------------------------\n");
	printf("\n---------------------- Machine Code -----------------------\n");
	for (i = 0; i < code_size; i++)
	{
		switch (m_code[i].op)
		{
			case OP_LA:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_LV:
			{
				printf("%-5s%-5d%-5d\n", "LV", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_LC:
			{
				printf("%-5s%-5d\n", "LC", m_code[i].p);
				break;
			}
			case OP_LI:
			{
				printf("%-5s\n", "LI");
				break;
			}
			case OP_INT:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			} 
			case OP_DCT:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_J:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_FJ:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_HL:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_ST:
			{
				printf("%-5s\n", "ST");
				break;
			}
			case OP_CALL:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_EP:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_EF:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_RC:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_RI:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_WRC:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_WRI:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_WLN:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_ADD:
			{
				printf("%-5s\n", "ADD");
				break;
			}
			case OP_SUB:
			{
				printf("%-5s\n", "SUB");
				break;
			}
			case OP_MUL:
			{
				printf("%-5s\n", "MUL");
				break;
			}
			case OP_DIV:
			{
				printf("%-5s\n", "DIV");
				break;
			}
			case OP_NEG:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_CV:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_EQ:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_NE:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_GT:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_LT:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_GE:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_LE:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_BP:
			{
				printf("%-5s%-5d%-5d\n", "LA", m_code[i].p, m_code[i].q);
				break;
			}

			default:
			{

			} 
		}
	}
}