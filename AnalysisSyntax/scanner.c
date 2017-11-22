#include "scanner.h"

void showHelpCommand()
{
	printf("    .............................................\n");
	printf("    :   usage: <ExecuteFile> <file_input path>  :\n");
	printf("    :   ex: ./pl0 fileInput                     :\n"); 
	printf("    :...........................................:\n");
}

char getChar()
{
	if (begin == 1)
	{
		printf("%d.    ", numLine);
		begin = 0;
	}
	ch = fgetc(fp);
	numColumn ++;
	
	if (ch != EOF)
		printf("%c", ch);
	if (ch == '\n')
	{
		lastLengthLine = numColumn;
		numColumn = 0;
		numLine ++;
		printf("%d.    ", numLine);
	}

	return ch;
}

token_t* ignoreComment()
{
	ch = getChar();
	while (ch != EOF)
	{
		if (ch == '*')
		{
			ch = getChar();
			while ((ch == '*') && (ch != EOF))
			{
				ch = getChar();
			}
			if (ch == ')') {
				/* end comment */
				ch = getChar();
				return getToken();
			}
		}

		ch = getChar();
	}

	return NULL;
}

token_t *getToken()
{

	lastLine = numLine;
	lastColumn = numColumn;
	
	token_t *token_temp = (token_t *) malloc(sizeof(token_t));

	if (ch == EOF)
		return NULL;

	/* ignore space character */
	while ((ch == '\n') || (ch == ' ') || (ch == '\t'))
	{
		ch = getChar();

		if (ch == EOF)
			return NULL;

	}

	/* get NUMBER */
	if (isdigit(ch)) 
	{
		int countNum = 0;

		while (isdigit(ch)) 
		{
			num[countNum ++] = ch;
			if (countNum > MAX_NUM_LEN) 
			{
				error(1);
			}
			ch = getChar();
		}
		num[countNum] = '\0';
		token_temp->type = NUMBER;
		strcpy(token_temp->name, num);
		return token_temp;
	}

	/* get IDENT or KEYWORD */
	else if (isalpha(ch))
	{
		int countStr = 0;

		while ((isalpha(ch) || isdigit(ch)))
		{
			if (countStr < MAX_IDENT_LEN) 
			{
				id[countStr ++] = ch;
			}
			ch = getChar();
		}
		id[countStr] = '\0';
		
		token_temp = checkKeyword(id);
	}

	/* get other symbol */
	else
	{
		switch(ch) {
			case '+':
				token_temp->type = PLUS;
				strcpy(token_temp->name, "PLUS");
				ch = getChar();
				break;
			case '-':
				token_temp->type = MINUS;
				strcpy(token_temp->name, "MINUS");
				ch = getChar();
				break;
			case '*':
				token_temp->type = TIMES;
				strcpy(token_temp->name, "TIMES");
				ch = getChar();
				break;
			case '/':
				token_temp->type = SLASH;
				strcpy(token_temp->name, "SLASH");
				ch = getChar();
				break;
			case '=':
				token_temp->type = EQU;
				strcpy(token_temp->name, "EQU");
				ch = getChar();
				break;
			case ',':
				token_temp->type = COMMA;
				strcpy(token_temp->name, "COMMA");
				ch = getChar();
				break;
			case '.':
				token_temp->type = PERIOD;
				strcpy(token_temp->name, "PERIOD");
				ch = getChar();
				break;
			case '>':
				ch = getChar();
				if (ch == '=')
				{
					token_temp->type = GEQ;
					strcpy(token_temp->name, "GEQ");
					ch = getChar();
				}
				else 
				{
					token_temp->type = GRT;
					strcpy(token_temp->name, "GRT");
				}
				break;
			case '<':
				ch = getChar();
				if (ch == '=')
				{
					token_temp->type = LEQ;
					strcpy(token_temp->name, "LEQ");
					ch = getChar();
				}
				else if (ch == '>')
				{
					token_temp->type = NEQ;
					strcpy(token_temp->name, "NEQ");
					ch = getChar();
				}
				else 
				{
					token_temp->type = LSS;
					strcpy(token_temp->name, "LSS");
				}
				break;
			case '(':
				ch = getChar();
				if (ch == '*')
				{
					/* is comment, ignore */
					token_temp = ignoreComment();
				}
				else 
				{
					token_temp->type = LPARENT;
					strcpy(token_temp->name, "LPARENT");
				}
				break;
			case ')':
				token_temp->type = RPARENT;
				strcpy(token_temp->name, "RPARENT");
				ch = getChar();
				break;
			case '[':
				token_temp->type = LBRACK;
				strcpy(token_temp->name, "LBRACK");
				ch = getChar();
				break;
			case ']':
				token_temp->type = RBRACK;
				strcpy(token_temp->name, "RBRACK");
				ch = getChar();
				break;
			case '%':
				token_temp->type = PERCENT;
				strcpy(token_temp->name, "PERCENT");
				ch = getChar();
				break;
			case ':':
				ch = getChar();
				if (ch == '=')
				{
					token_temp->type = ASSIGN;
					strcpy(token_temp->name, "ASSIGN");
					ch = getChar();
				}
				else {
					error(2);
				}
				break;
			case ';':
				token_temp->type = SEMICOLON;
				strcpy(token_temp->name, "SEMICOLON");
				ch = getChar();
			break;
			default:
                error(36);
		}
	}

	return token_temp;
}

token_t* checkKeyword(char *str)
{
	token_t* token_temp = (token_t *) malloc(sizeof(token_t));
	/* Capital */
	int str_length = strlen(str);
	char str_[str_length + 1];
	strcpy(str_, str);
	int i;

	for (i = 0; i < str_length; i++)
	{
		char pos = str_[i];
		if ((pos >= 'a') && (pos <= 'z'))
		{
			str_[i] = pos - 32;
		}
	}

	if (strcmp(str_, "BEGIN") == 0)
		token_temp->type = BEGIN;
	else if (strcmp(str_, "END") == 0)
		token_temp->type = END;
	else if (strcmp(str_, "IF") == 0)
		token_temp->type = IF;
	else if (strcmp(str_, "THEN") == 0)
		token_temp->type = THEN;
	else if (strcmp(str_, "WHILE") == 0)
		token_temp->type = WHILE;
	else if (strcmp(str_, "DO") == 0)
		token_temp->type = DO;
	else if (strcmp(str_, "CALL") == 0)
		token_temp->type = CALL;
	else if (strcmp(str_, "ODD") == 0)
		token_temp->type = ODD;
	else if (strcmp(str_, "TO") == 0)
		token_temp->type = TO;
	else if (strcmp(str_, "CONST") == 0)
		token_temp->type = CONST;
	else if (strcmp(str_, "VAR") == 0)
		token_temp->type = VAR;
	else if (strcmp(str_, "PROCEDURE") == 0)
		token_temp->type = PROCEDURE;
	else if (strcmp(str_, "PROGRAM") == 0)
		token_temp->type = PROGRAM;
	else if (strcmp(str_, "ELSE") == 0)
		token_temp->type = ELSE;
	else if (strcmp(str_, "FOR") == 0)
		token_temp->type = FOR;
	else
	{
		token_temp->type = IDENT;
		strcpy(token_temp->name, str);
		return token_temp;
	}
	strcpy(token_temp->name, str_);
	return token_temp;
}