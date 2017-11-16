#include "scanner.h"

int main(int argc, char *argv[])
{
	bool l = false, s = false;
	uint8_t i;
	
	if (argc < 2)
	{
		printf("WARNING: To few arguments\n");
		printf("-------------------------------------------\n");
		showHelpCommand();
		return -1;
	}
	else if ((argc == 2) && (strcmp(argv[1], "--help") == 0))
	{
		showHelpCommand();
		return -1;
	}
	else 
	{
		for (i = 1; i < argc; i ++)
		{
			if (strcmp(argv[i], "-l") == 0)
			{
				l = true;
			}
			else if (strcmp(argv[i], "-s") == 0)
			{
				s = true;
			}
			else
			{	
				numFile ++;
				if (numFile >= 2)
				{
					printf("ERROR: To many input file, choose Only one file\n");
					printf("-------------------------------------------\n");
					showHelpCommand();
					return -1;
				}
				fileInput = argv[i];
			}
		}
	}

	if ((numFile == 1) && (l == false) && (s == false))
	{
		printf("WARNING: Please choose option -l or -s\n");
		printf("-------------------------------------------\n");
		showHelpCommand();
		return -1;
	}

	if (numFile == 0)
	{
		printf("WARNING: Please enter input file\n");
		printf("-------------------------------------------\n");
		showHelpCommand();
		return -1;
	}

	scanner(l, s);
	free(listToken);
	return 0;
}

/* Show Help when user missing arguments */
void showHelpCommand()
{
	printf("usage: <ExecuteFile> [--help] [-l] [-s] <file_input path>\n");
	printf("  --help\tDisplay this information\n");
	printf("  -l\t\tShow list of token in FILE_INPUT\n");
	printf("  -s\t\tShow assembly code (Use in future)\n");
	printf("ex   : ./scanner -l filePL0.txt \n");
}

/* 
 * scan input file and generate TOKEN 
 * if l = true => show list token
 * if s = true => show assembly code
 */
void scanner(bool l, bool s)
{
	if (getToken(fileInput) != NULL)
	{
		if (l == true)
			showListToken(fileInput);
	}
}

token_t *getToken(char *filename)
{
	bool isComment = false;
	int ch;	/* character */
	row = 1;
	int curPos = 0; // Position number in current line

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) 
	{
		perror("ERROR in open file: ");
		return NULL;
	}

	ch = fgetc(fp); curPos ++;
	listToken = (token_t *)malloc(1 * sizeof(token_t));

	while (ch != EOF)
	{
		if (isComment == true) /* if in comment, ignore*/
		{
			ch = fgetc(fp); curPos ++;
			if (ch == 10) /* new line */
			{
				row ++;
				curPos = 0;
			}
			else if (ch == '*')
			{
				ch = fgetc(fp); curPos ++;
				while ((ch == '*') && (ch != EOF))
				{
					ch = fgetc(fp); curPos ++;
				}
				if (ch == ')') {
					isComment = false;
					ch = fgetc(fp); curPos ++;
				}
			}
		}
		else // not in comment
		{
			if (isdigit(ch)) 
			{
				uint8_t countNum = 0;

				while (isdigit(ch)) 
				{
					num[countNum ++] = ch;
					if (countNum > MAX_LENGTH_NUM) 
					{
						printf("Error: Line:%d, Column:%d ::", row, curPos);
						printf("Number too long\n");
						return NULL;
					}
					ch = fgetc(fp); curPos ++;
				}
				num[countNum] = '\0';
				listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
				listToken[numToken].type = NUMBER;
				strcpy(listToken[numToken ++].name, num);
			}
			else if (isalpha(ch))
			{
				uint8_t countStr = 0;

				while ( isalpha(ch) || isdigit(ch))
				{
					if (countStr < MAX_IDENT_LEN) 
					{
						id[countStr ++] = ch;
					}
					ch = fgetc(fp); curPos ++;
				}
				id[countStr] = '\0';
				TokenType temp;
				listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
				if((temp = checkKeyWord(id)) != NONE)
				{
					listToken[numToken].type = temp;
					strcpy(listToken[numToken ++].name, convertToToken[temp].name);
				}
				else
				{
					listToken[numToken].type = IDENT;
					strcpy(listToken[numToken ++].name, id);
				}
			}
			else 
			{
				switch(ch) {
					case '\n':
						row ++; 
						curPos = 0;	
						ch = fgetc(fp); curPos ++;
					break;
					case ' ':
						while (ch == ' ' || ch == '\t')
						{
							ch = fgetc(fp); curPos ++;
						}
					break;
					case '\t':
						while (ch == ' ' || ch == '\t')
						{
							ch = fgetc(fp); curPos ++;
						}
					break;
					case '+':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = PLUS;
						strcpy(listToken[numToken ++].name, "PLUS");
						ch = fgetc(fp); curPos ++;
					break;
					case '-':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = MINUS;
						strcpy(listToken[numToken ++].name, "MINUS");
						ch = fgetc(fp); curPos ++;
					break;
					case '*':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = TIMES;
						strcpy(listToken[numToken ++].name, "TIMES");
						ch = fgetc(fp); curPos ++;
					break;
					case '/':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = SLASH;
						strcpy(listToken[numToken ++].name, "SLASH");
						ch = fgetc(fp); curPos ++;
					break;
					case '=':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = EQU;
						strcpy(listToken[numToken ++].name, "EQU");
						ch = fgetc(fp); curPos ++;
					break;
					case ',':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = COMMA;
						strcpy(listToken[numToken ++].name, "COMMA");
						ch = fgetc(fp); curPos ++;
					break;
					case '.':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = PERIOD;
						strcpy(listToken[numToken ++].name, "PERIOD");
						ch = fgetc(fp); curPos ++;
					break;
					case '>':
						ch = fgetc(fp); curPos ++;
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						if (ch == '=')
						{
							listToken[numToken].type = GEQ;
							strcpy(listToken[numToken ++].name, "GEQ");
									ch = fgetc(fp); curPos ++;
						}
						else 
						{
							listToken[numToken].type = GRT;
							strcpy(listToken[numToken ++].name, "GRT");
								}
					break;
					case '<':
						ch = fgetc(fp); curPos ++;
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						if (ch == '=')
						{
							listToken[numToken].type = LEQ;
							strcpy(listToken[numToken ++].name, "LEQ");
									ch = fgetc(fp); curPos ++;
						}
						else if (ch == '>')
						{
							listToken[numToken].type = NEQ;
							strcpy(listToken[numToken ++].name, "NEQ");
									ch = fgetc(fp); curPos ++;
						}
						else 
						{
							listToken[numToken].type = LSS;
							strcpy(listToken[numToken ++].name, "LSS");
								}
					break;
					case '(':
						ch = fgetc(fp); curPos ++;
						if (ch == '*')
						{
							isComment = true;
						}
						else 
						{
							listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
							listToken[numToken].type = LPARENT;
							strcpy(listToken[numToken ++].name, "LPARENT");
						}
					break;
					case ')':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = RPARENT;
						strcpy(listToken[numToken ++].name, "RPARENT");
						ch = fgetc(fp); curPos ++;
					break;
					case '[':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = LBRACK;
						strcpy(listToken[numToken ++].name, "LBRACK");
						ch = fgetc(fp); curPos ++;
					break;
					case ']':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = RBRACK;
						strcpy(listToken[numToken ++].name, "RBRACK");
						ch = fgetc(fp); curPos ++;
					break;
					case '%':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = PERCENT;
						strcpy(listToken[numToken ++].name, "PERCENT");
						ch = fgetc(fp); curPos ++;
					break;
					case ':':
						ch = fgetc(fp); curPos ++;
						if (ch == '=')
						{
							listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
							listToken[numToken].type = ASSIGN;
							strcpy(listToken[numToken ++].name, "ASSIGN");
							ch = fgetc(fp); curPos ++;
						}
						else {
							printf("Error: Line:%d, Column:%d ::", row, curPos);
							printf("Invalid symbol\n");
							return NULL;
						}
					break;
					case ';':
						listToken = (token_t *)realloc(listToken, (numToken + 1) * sizeof(token_t));
						listToken[numToken].type = SEMICOLON;
						strcpy(listToken[numToken ++].name, "SEMICOLON");
						ch = fgetc(fp); curPos ++;
					break;
					default:
	                    printf("Error: Line:%d, Column:%d ::", row, curPos);
						printf("Invalid symbol\n");
						return NULL;
				}
			}
		}
	}

	fclose(fp);
	return listToken;
}

void showListToken(char *filename)
{
	int i;
	printf("-----------------------------------------------\n");
	printf("List Token in File: %s\n", filename);
	printf("-----------------------------------------------\n");
	for (i = 0; i < numToken; i++)
	{
		if (listToken[i].type == NUMBER)
		{
			printf("NUMBER(%s)\n", listToken[i].name);
		}
		else if (listToken[i].type == IDENT)
		{
			printf("IDENT(%s)\n", listToken[i].name);
		}
		else {
			printf("%s\n", listToken[i].name);
		}
	}
	printf("-----------------------------------------------\n");
}

TokenType checkKeyWord(char *str)
{
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
	for (i = 0; i < 15; i ++)
	{
		if (strcmp(str_, keyWord[i].name) == 0)
			return keyWord[i].type;
	}

	return NONE;
}