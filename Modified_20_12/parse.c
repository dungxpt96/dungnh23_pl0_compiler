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
	label_size = 0;

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

		intepreter();
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
			printf("Incompatible Argument types, argument must be VAR_TYPE\n");
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
		case 52:
		{			
			printf("LPARENT expected in WRITE statement\n");
			break;
		}
		case 53:
		{			
			printf("RPARENT expected in WRITE statement\n");
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

	to_code(OP_HL, 0, 0);
}


void compileBlock()
{
	int label_begin_end_block = code_size;
	to_code(OP_J, 0, 0);
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
	
	m_code[label_begin_end_block].q = code_size;
	int numVC = getNumVC();
	to_code(OP_INT, 0, 4 + numVC);

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
			addDeclareVariableInProcedure(0);
			int curOb = sTb[countSymbolTable - 1].numArguments;
			sTb[countSymbolTable - 1].ot[curOb] = ARG_VALUE;
			strcpy(sTb[countSymbolTable - 1].otString[curOb], token->name);
			sTb[countSymbolTable - 1].numArguments ++;
			//printf("\nIdent:%s==Number:%d==\n", token->name, sTb[countSymbolTable - 1].numArguments);
		}

		if (token->type == VAR)
		{
			token = getToken();
			addDeclareVariableInProcedure(1);
			int curOb = sTb[countSymbolTable - 1].numArguments;
			sTb[countSymbolTable - 1].ot[curOb] = VAR_TYPE;
			strcpy(sTb[countSymbolTable - 1].otString[curOb], token->name);
			sTb[countSymbolTable - 1].numArguments ++;
			//printf("\nIdent:%s==Number:%d==\n", token->name, sTb[countSymbolTable - 1].numArguments);
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
				addDeclareVariableInProcedure(0);
				int curOb = sTb[countSymbolTable - 1].numArguments;
				sTb[countSymbolTable - 1].ot[curOb] = ARG_VALUE;
				strcpy(sTb[countSymbolTable - 1].otString[curOb], token->name);
				sTb[countSymbolTable - 1].numArguments ++;
				//printf("\nIdent:%s==Number:%d==\n", token->name, sTb[countSymbolTable - 1].numArguments);

			}
			if (token->type == VAR)
			{
				token = getToken();
				addDeclareVariableInProcedure(1);
				int curOb = sTb[countSymbolTable - 1].numArguments;
				sTb[countSymbolTable - 1].ot[curOb] = VAR_TYPE;
				strcpy(sTb[countSymbolTable - 1].otString[curOb], token->name);
				sTb[countSymbolTable - 1].numArguments ++;
				//printf("\nIdent:%s==Number:%d==\n", token->name, sTb[countSymbolTable - 1].numArguments);
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
	to_code(OP_EP, 0, 0);
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

		//printf("\n Find %d - %d \n", location_id->base, location_id->offset);

		to_code(OP_LA, location_id->base, location_id->offset);
		int isVarArg = isVarArgument(temp_name);
		if (isVarArg == 1)
		{
			to_code(OP_LI, 0, 0);
		}
		if ((token != NULL) && (token->type == LBRACK))
		{
			to_code(OP_LC, 0, 1);
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
	else if ((token != NULL) && (token->type == WRITE))
	{
		token = getToken();
		compileWriteStatement();
	}
}

void compileWriteStatement()
{
	if ((token == NULL) || (token->type != LPARENT))
		error(52);

	token = getToken();

	compileExpression();
	to_code(OP_WRI, 0, 0); 

	if ((token == NULL) || (token->type != RPARENT))
		error(53);

	token = getToken();
}

void compileCallStatement()
{
	to_code(OP_INT, 0, 4);

	if ((token == NULL) || (token->type != IDENT))
		error(21);

	char temp_name_pro[100];
	strcpy(temp_name_pro, token->name);	
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
		if ((token != NULL) && (token->type != IDENT))
		{
			if (sTb[index].ot[countArg] == VAR_TYPE)
			{
				error(46);
			}
		}
		/* Kiem tra token co phai ident hay khong */
		compileExpression();
		printf("checkExpressionIsIdent = %d\n", checkExpressionIsIdent);
		//printf("after compileExpression: checkExpressionIsIdent = %d\n", checkExpressionIsIdent);
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

				code_size --;
				printf("-------code_size-var in procedure-%d-----\n", code_size);
				location_id = location_ident(temp_name);
				to_code(OP_LA, location_id->base, location_id->offset);
			}
		}
		else
		{
			if (sTb[index].ot[countArg] == VAR_TYPE)
			{
				error(46);
			}
		}
		countArg ++;
		while((token != NULL) && (token->type == COMMA))
		{
			token = getToken();
			char temp_name[100];
			strcpy(temp_name, token->name);
			checkExpressionIsIdent = 0;
			/*			
			if ((token != NULL) && (token->type != IDENT))
			{
				if (sTb[index].ot[countArg] == VAR_TYPE)
				{
					error(46);
				}
			}//*/
			compileExpression();
			printf("checkExpressionIsIdent = %d\n", checkExpressionIsIdent);
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

					code_size --;
					printf("-------code_size-var in procedure-%d-----\n", code_size);
					location_id = location_ident(temp_name);
					to_code(OP_LA, location_id->base, location_id->offset);
				}
			}
			
			countArg ++;
		}

		if ((token == NULL) || (token->type != RPARENT))
			error(19);

		printf("\n==%d==%d==\n", countArg, sTb[index].numArguments);
		if (countArg != sTb[index].numArguments)
		{
			error(49);
		}

		/* Gen machine code for CONST */
		to_code(OP_DCT, 0, 4 + countArg);
		location_id = location_ident(temp_name_pro);
		to_code(OP_CALL, location_id->base, location_id->offset);

		token = getToken();
	}
	else
	{	
		to_code(OP_DCT, 0, 4 + countArg);
		location_id = location_ident(temp_name_pro);
		to_code(OP_CALL, location_id->base, location_id->offset);

		//token = getToken(); //*/
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

	if ((token != NULL) && (token->type != ELSE))
	{
		/* Khong co cau lenh else */
		update_lastest_label(code_size);
	}
	else
	{
		update_lastest_label(code_size + 1);
		to_code(OP_J, 0, UNKNOW);
	}

	if ((token != NULL) && (token->type == ELSE))
	{	
		token = getToken();
		compileStatement();
		update_lastest_label(code_size);
	}
}

void compileWhileStatement()
{
	int label_while = code_size;

	compileCondition();

	if ((token == NULL) || (token->type != DO))
		error(27);

	token = getToken();
	compileStatement();

	to_code(OP_J, 0, label_while);
	printf("\n------------code_size=%d\n", code_size);
	update_lastest_label(code_size);
	printf("\n---------Updated\n");
}

void compileForStatement()
{
	handleIdentForStatement();
	/* Day dia chi cua ident len tren stack */
	to_code(OP_LA, location_id->base, location_id->offset);
	/* Nhan doi dia chi cua ident */
	to_code(OP_CV, 0, 0);

	if ((token == NULL) || (token->type != ASSIGN))
		error(24);

	token = getToken();
	compileExpression();
	/* Dat gia tri bieu thuc 1 len stack */
	to_code(OP_ST, 0, 0);
	/* Sinh ra dia chi cho nhan L1 trong vong lap FOR */
	int label1_for = code_size;
	/* Nhan doi gia tri bieu thuc so 2 */
	to_code(OP_CV, 0, 0);
	/* Lay gia tri cua ident va luu vao dinh stack, dinh stack co gia tri ident */
	to_code(OP_LI, 0, 0);

	if ((token == NULL) || (token->type != TO))
		error(28);

	token = getToken();
	compileExpression();
	/* So sanh 2 gia tri tren dinh stack: ident va exp2 */
	to_code(OP_LE, 0, 0);
	/* Neu dieu kien sai, thoat ra khoi vong lap FOR */
	to_code(OP_FJ, 0, UNKNOW);


	if ((token == NULL) || (token->type != DO))
		error(27);

	token = getToken();
	compileStatement();
	/* Dinh stack la dia chi cua ident, sao chep 2 lan */
	to_code(OP_CV, 0, 0);
	to_code(OP_CV, 0, 0);
	/* Dinh stack la gia tri cua ident */
	to_code(OP_LI, 0, 0);
	/* Dat gia tri 1 len stack roi cong voi ident */
	to_code(OP_LC, 0, 1);
	to_code(OP_ADD, 0, 0);
	/* Luu gia tri moi cua ident la (ident +1) vao vi tri cua ident */
	to_code(OP_ST, 0, 0);
	/* Quay tro lai vong lap, nhay toi L1 */
	to_code(OP_J, 0, label1_for);
	/* sinh ra nhan L2 */
	update_lastest_label(code_size);
	/* Giam thanh ghi T xuong 1 don vi do dinh stack la v */
	to_code(OP_DCT, 0, 1);
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
		checkExpressionIsIdent = 1;
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
		//printf("\n Factor %d - %d \n", location_id->base, location_id->offset);
		
		if ((token != NULL) && (token->type == LBRACK))
		{
			to_code(OP_LA, location_id->base, location_id->offset);
			to_code(OP_LC, 0, 1);
		}
		else
		{
			objectType t = getKind(temp_name);
			if (t == CONST_TYPE)
			{
				int value_const = getValue(temp_name);
				to_code(OP_LC, 0, value_const);
			}
			else
				to_code(OP_LV, location_id->base, location_id->offset);
		}

		int isVarArg = isVarArgument(temp_name);
		if (isVarArg == 1)
		{
			to_code(OP_LI, 0, 0);
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
		to_code(OP_LC, 0, num);

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

	objectType ob = token->type;

	if ((token != NULL) && ( (token->type == EQU) || (token->type == NEQ) ||
		(token->type == LSS) || (token->type == LEQ) || (token->type == GRT) ||
		(token->type == GEQ)))
	{
		token = getToken();
		compileExpression();

		/* Gen code for condition */
		if (ob == EQU)
		{
			to_code(OP_EQ, 0, 0);
		}
		else if (ob == NEQ)
		{
			to_code(OP_NE, 0, 0);
		}
		else if (ob == LSS)
		{
			to_code(OP_LT, 0, 0);
		}
		else if (ob == LEQ)
		{
			to_code(OP_LE, 0, 0);
		}
		else if (ob == GRT)
		{
			to_code(OP_GT, 0, 0);
		}
		else if (ob == GEQ)
		{
			to_code(OP_GE, 0, 0);
		}
		
		to_code(OP_FJ, 0, UNKNOW);
		label[label_size ++] = UNKNOW;
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
				printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_LV:
			{
				printf("%-5d%-5s%-5d%-5d\n", i, "LV", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_LC:
			{
				printf("%-5d%-5s%-5d\n", i, "LC", m_code[i].q);
				break;
			}
			case OP_LI:
			{
				printf("%-5d%-5s\n", i, "LI");
				break;
			}
			case OP_INT:
			{
				printf("%-5d%-5s%-5d\n", i, "INT", m_code[i].q);
				break;
			} 
			case OP_DCT:
			{
				printf("%-5d%-5s%-5d\n", i, "DCT", m_code[i].q);
				break;
			}
			case OP_J:
			{
				printf("%-5d%-5s%-5d\n", i, "J", m_code[i].q);
				break;
			}
			case OP_FJ:
			{
				printf("%-5d%-5s%-5d\n", i, "FJ", m_code[i].q);
				break;
			}
			case OP_HL:
			{
				printf("%-5d%-5s\n", i, "HL");
				break;
			}
			case OP_ST:
			{
				printf("%-5d%-5s\n", i, "ST");
				break;
			}
			case OP_CALL:
			{
				printf("%-5d%-5s%-5d%-5d\n", i, "CALL", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_EP:
			{
				printf("%-5d%-5s\n", i, "EP");
				break;
			}
			case OP_EF:
			{
				printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_RC:
			{
				printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_RI:
			{
				printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_WRC:
			{
				printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_WRI:
			{
				printf("%-5d%-5s\n", i, "WRI");
				break;
			}
			case OP_WLN:
			{
				printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_ADD:
			{
				printf("%-5d%-5s\n", i, "ADD");
				break;
			}
			case OP_SUB:
			{
				printf("%-5d%-5s\n", i, "SUB");
				break;
			}
			case OP_MUL:
			{
				printf("%-5d%-5s\n", i, "MUL");
				break;
			}
			case OP_DIV:
			{
				printf("%-5d%-5s\n", i, "DIV");
				break;
			}
			case OP_NEG:
			{
				printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
				break;
			}
			case OP_CV:
			{
				printf("%-5d%-5s\n", i, "CV");
				break;
			}
			case OP_EQ:
			{
				printf("%-5d%-5s\n", i, "EQ");
				break;
			}
			case OP_NE:
			{
				printf("%-5d%-5s\n", i, "NE");
				break;
			}
			case OP_GT:
			{
				printf("%-5d%-5s\n", i, "GT");
				break;
			}
			case OP_LT:
			{
				printf("%-5d%-5s\n", i, "LT");
				break;
			}
			case OP_GE:
			{
				printf("%-5d%-5s\n", i, "GE");
				break;
			}
			case OP_LE:
			{
				printf("%-5d%-5s\n", i, "LE");
				break;
			}
			case OP_BP:
			{
				printf("%-5d%-5s%-5d%-5d\n", i, "LA", m_code[i].p, m_code[i].q);
				break;
			}

			default:
			{

			} 
		}
	}
}

void update_lastest_label(int value)
{
	int i;
	for (i = code_size - 1; i >= 0; i --)
	{
		if (m_code[i].q == UNKNOW)
		{
			m_code[i].q = value;
			break;
		}
	}
}