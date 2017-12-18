#include "sematics.h"
#include "parse.h"
#include <ctype.h>

char *objectTypeString[] = {"variable", "const", "array", "procedure"};
/* Kiem tra ident da duoc khai bao hay chua trong pham vi hien tai*/
/* Dua vao bien countSymbolTable de xac dinh hien tai la bang so bao nhieu */
int checkIdent(char *id_name, objectType ot, int level)
{
	int current = countSymbolTable - 1;
	int i;
	for (i = countSymbolTable -1; i >= 0; i--)
	{
		if (sTb[i].levelOfTable == level - 1)
		{
			current = i;
			break;
		}
	}

	int order = countSymbolTable - 1; /* thu tu cua bang can lookup */

	int numberOfIdent = sTb[current].countSymbolIndent;
	for (i = 0; i < numberOfIdent; i++)
	{
		char name1[100], name2[100];
		strcpy(name1, sTb[current].listSymbolIndent[i].name);
		strcpy(name2, id_name);
		int i1, i2;
		for (i1 = 0; i1 < strlen(name1); i1++)
		{
			name1[i1] = toupper(name1[i1]);
		}

		for (i2 = 0; i2 <strlen(name2); i2 ++)
		{
			name2[i2] = toupper(name2[i2]);
		}

		if (strcmp(name1, name2) == 0)
		{
			return 0; /* Trung ten */
		}
	}

	return 1;
}


/* Them mot dinh danh vao bang */
void enter_ident_pro(char *id_name, objectType ot, int level)
{
	int i;
	for (i = countSymbolTable - 1; i >= 0; i--)
	{
		if(sTb[i].levelOfTable == (level-1))
		{
			int nextIdent = sTb[i].countSymbolIndent;
			sTb[i].listSymbolIndent[nextIdent].name = id_name;
			sTb[i].listSymbolIndent[nextIdent].type = ot;
			sTb[i].listSymbolIndent[nextIdent].nextSymbolTable = -1;
			if (ot == PROCEDURE_TYPE)
			{
				sTb[i].listSymbolIndent[nextIdent].nextSymbolTable = countSymbolTable - 1;
				sTb[countSymbolTable - 1].parentSymbolTable = sTb[i].index;
			}
			sTb[i].listSymbolIndent[nextIdent].index =nextIdent;
			sTb[i].countSymbolIndent ++;
			break;
		}
	}
}

void enter_ident(char *id_name, objectType ot)
{
	int nextIdent = sTb[countSymbolTable - 1].countSymbolIndent;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].name = id_name;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].type = ot;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].nextSymbolTable = -1;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].index =nextIdent;
	sTb[countSymbolTable - 1].countSymbolIndent ++;
}

void enter_ident_array(char *id_name, objectType ot, int value)
{
	int nextIdent = sTb[countSymbolTable - 1].countSymbolIndent;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].name = id_name;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].type = ot;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].nextSymbolTable = -1;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].index =nextIdent;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].value = value;
	sTb[countSymbolTable - 1].countSymbolIndent ++;
}

/* Chi ra vi tri cua danh bieu trong bang ky hieu */
int location_ident(char *id_name)
{
	int current = countSymbolTable - 1;

	while (current != -1)
	{
		int numberOfIdent = sTb[current].countSymbolIndent;

		int i;
		for (i = 0; i < numberOfIdent; i++)
		{
			if (strcmp(sTb[current].listSymbolIndent[i].name, id_name) == 0)
			{
				return i; /* Trung ten */
			}
		}
		current = sTb[current].parentSymbolTable;
	}
	return -1;
}

void print_symbolTable()
{
	int i;
	for (i = 0; i < countSymbolTable; i++)
	{
		printf("\nBang ky hieu so %d\n", i);
		printf("\t--index = %d\n", sTb[i].index);
		printf("\t--Name = %s\n", sTb[i].name);
		printf("\tLevel = %d\n", sTb[i].levelOfTable);
		printf("\tparentSymbolTable = %d\n", sTb[i].parentSymbolTable);
		printf("\tcountSymbolIndent = %d\n", sTb[i].countSymbolIndent);
		printf("\tDanh sach cac ky hieu:\n");
		int j;
		int countSym = sTb[i].countSymbolIndent;
		for (j = 0; j < countSym; j++)
		{
			printf("\t\t--Index: %d\n", sTb[i].listSymbolIndent[j].index);
			printf("\t\tName: %s\n", sTb[i].listSymbolIndent[j].name);
			printf("\t\tType: %s\n", objectTypeString[(int) sTb[i].listSymbolIndent[j].type]);
			printf("\t\tValue: %d\n", sTb[i].listSymbolIndent[j].value);
			printf("\t\tNext symbolTable: %d\n", sTb[i].listSymbolIndent[j].nextSymbolTable);

		}
	}
}

void compileDeclareConst()
{
	if ((token == NULL) || (token->type != IDENT))
		error(8);

	int ret_checkIdent = checkIdent(token->name, 0, 0);

	if (ret_checkIdent == 0) /* Trung ten */
	{
		printf("\n==>Previous declaration of \"%s\" was here", token->name);
		error(31);
	}
	enter_ident(token->name, CONST_TYPE);
	token = getToken();
	if ((token == NULL) || (token->type != EQU))
		error(9);

	token = getToken();
	if ((token == NULL) || (token->type != NUMBER))
		error(10);
	//print_symbolTable();
	token = getToken();
}

void compileDeclareVar()
{
	if ((token == NULL) || (token->type != IDENT))
		error(13);

	int ret_checkIdent = checkIdent(token->name, 0, 0);

	if (ret_checkIdent == 0) /* Trung ten */
	{
		printf("\n==>Previous declaration of \"%s\" was here", token->name);
		error(31);
	}

	char *tempTokenName = token->name;
	int tempValue;
	int isArray = 0;
	token = getToken();
	/* Handle array type */
	if ((token != NULL) && (token->type == LBRACK))
	{
		token = getToken();
		if ((token == NULL) || (token->type != NUMBER))
			error(15);
		tempValue = atoi(token->name);
		token = getToken();
		if ((token == NULL) || (token->type != RBRACK))
			error(16);
		isArray = 1;
		token = getToken();
	}
	if (isArray == 0)
	{
		enter_ident(tempTokenName, VAR_TYPE);
	}
	else
	{
		enter_ident_array(tempTokenName, ARRAY_TYPE, tempValue);
	}
	//print_symbolTable();
}

void compileDeclareProcedure()
{
	if ((token == NULL) || (token->type != IDENT))
		error(21);
	cur_level ++;

	int ret_checkIdent = checkIdent(token->name, PROCEDURE_TYPE, sTb[countSymbolTable-1].levelOfTable);

	if (ret_checkIdent == 0) /* Trung ten */
	{
		printf("\n==>Previous declaration of \"%s\" was here", token->name);
		error(32);
	}
	countSymbolTable ++;
	make_table(token->name);
	enter_ident_pro(token->name, PROCEDURE_TYPE, sTb[countSymbolTable-1].levelOfTable);
	//print_symbolTable();
	token = getToken();
}

void make_table(char *name)
{
	sTb[countSymbolTable - 1].name = name;
	sTb[countSymbolTable - 1].index = countSymbolTable - 1;
	sTb[countSymbolTable - 1].levelOfTable = cur_level;
	sTb[countSymbolTable - 1].numArguments = 0;
}

void addDeclareVariableInProcedure()
{
	if ((token == NULL) || (token->type != IDENT))
		error(17);

	int ret_checkIdent = checkIdent(token->name, PROCEDURE_TYPE, sTb[countSymbolTable-1].levelOfTable);

	if (ret_checkIdent == 0) /* Trung ten */
	{
		printf("\n==>Previous declaration of \"%s\" was here", token->name);
		error(32);
	}
	enter_ident(token->name, VAR_TYPE);
	int curOb = sTb[countSymbolTable - 1].numArguments;
	sTb[countSymbolTable - 1].ot[curOb] = VAR_TYPE;
	strcpy(sTb[countSymbolTable - 1].otString[curOb], "varvar");
	sTb[countSymbolTable - 1].numArguments ++;
}

void handleIdentStatement()
{
	int p = location_ident(token->name);

	if (p < 0)
	{
		printf("\n\"%s\" undeclared (first use in this function)\n", token->name);
		error(31);
	}
	
	objectType t = getKind(token->name);
	checkType(t);
}

int getValue(char *id_name)
{
	int current;
	int i;
	for (i = countSymbolTable -1; i >= 0; i--)
	{
		if (sTb[i].levelOfTable == cur_level)
		{
			current = i;
			break;
		}
	}
	while (current != -1)
	{
		int numberOfIdent = sTb[current].countSymbolIndent;

		int i;
		for (i = 0; i < numberOfIdent; i++)
		{
			char name1[100], name2[100];
			strcpy(name1, sTb[current].listSymbolIndent[i].name);
			strcpy(name2, id_name);
			int i1, i2;
			for (i1 = 0; i1 < strlen(name1); i1++)
			{
				name1[i1] = toupper(name1[i1]);
			}

			for (i2 = 0; i2 <strlen(name2); i2 ++)
			{
				name2[i2] = toupper(name2[i2]);
			}
			if (strcmp(name1, name2) == 0)
			{
				return sTb[current].listSymbolIndent[i].value; 
			}
		}
		current = sTb[current].parentSymbolTable;
	}
	return -1;
}


objectType getKind(char *id_name)
{
	int current;
	int i;
	for (i = countSymbolTable -1; i >= 0; i--)
	{
		if (sTb[i].levelOfTable == cur_level)
		{
			current = i;
			break;
		}
	}
	while (current != -1)
	{
		int numberOfIdent = sTb[current].countSymbolIndent;

		int i;
		for (i = 0; i < numberOfIdent; i++)
		{
			char name1[100], name2[100];
			strcpy(name1, sTb[current].listSymbolIndent[i].name);
			strcpy(name2, id_name);
			int i1, i2;
			for (i1 = 0; i1 < strlen(name1); i1++)
			{
				name1[i1] = toupper(name1[i1]);
			}

			for (i2 = 0; i2 <strlen(name2); i2 ++)
			{
				name2[i2] = toupper(name2[i2]);
			}
			if (strcmp(name1, name2) == 0)
			{
				return sTb[current].listSymbolIndent[i].type; 
			}
		}
		current = sTb[current].parentSymbolTable;
	}
	return NONE_TYPE;
}

void checkType(objectType t)
{
	if (t == NONE_TYPE)
	{
		error(31);
	}
	if (t == CONST_TYPE)
	{
		error(41);
	}
	else if (t == PROCEDURE_TYPE)
	{
		error(33);
	}

	token = getToken();

	if ((t == ARRAY_TYPE) && ((token == NULL) || (token->type != LBRACK)))
	{
		error(42);
	}
}

void handleIdentCallStatement()
{
	objectType t = getKind(token->name);
	if (t != PROCEDURE_TYPE)
	{
		error(43);
	}

	token = getToken();
}

void handleIdentForStatement()
{
	if ((token == NULL) || (token->type != IDENT))
		error(21);

	objectType t = getKind(token->name);
	if (t != VAR_TYPE)
	{
		error(44);
	}

	token = getToken();
}

int getTable(char *nameP)
{
	int i;
	for (i = countSymbolTable -1; i >= 1; i--)
	{
		if(strcmp(sTb[i].name, nameP) == 0)
		{
			return i;
		}
	}
}

int handleFactorIdent()
{
	int p = location_ident(token->name);

	if (p < 0)
	{
		printf("\n\"%s\" undeclared (first use in this function)\n", token->name);
		error(31);
	}
	objectType t = getKind(token->name);
	token = getToken();
	if ((token != NULL) && (token->type != LBRACK))
	{
		if (t == ARRAY_TYPE)
		{
			error(42);
		}
		if (t == PROCEDURE_TYPE)
		{
			error(47);
		}
		return 0;
	}

	return 1;
}
