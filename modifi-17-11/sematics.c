#include "sematics.h"
#include "parse.h"
char *objectTypeString[] = {"variable", "const", "array", "procedure"};
/* Kiem tra ident da duoc khai bao hay chua trong pham vi hien tai*/
/* Dua vao bien countSymbolTable de xac dinh hien tai la bang so bao nhieu */
int checkIdent(char *id_name, objectType ot, int level)
{
	int order = countSymbolTable - 1; /* thu tu cua bang can lookup */
	if (ot == PROCEDURE_TYPE)
	{
		int j;
		for (j = countSymbolTable - 1; j >= 0; j--)
		{
			if (sTb[j].levelOfTable == (level-1))
			{
				order = j;
				break;
			}
		}
	}
	int numberOfIdent = sTb[order].countSymbolIndent;
	int i;
	for (i = 0; i < numberOfIdent; i++)
	{
		if (strcmp(sTb[order].listSymbolIndent[i].name, id_name) == 0)
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
	if (ot == PROCEDURE_TYPE)
		sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].nextSymbolTable = countSymbolTable - 1;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].index =nextIdent;
	sTb[countSymbolTable - 1].countSymbolIndent ++;
}

/* Chi ra vi tri cua danh bieu trong bang ky hieu */
int location_ident(char *id_name)
{
	int numberOfIdent = sTb[countSymbolTable - 1].countSymbolIndent;

	int i;
	for (i = 0; i < numberOfIdent; i++)
	{
		if (strcmp(sTb[countSymbolTable - 1].listSymbolIndent[i].name, id_name) == 0)
		{
			return i; /* Trung ten */
		}
	}
	return 0;
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
			printf("\t\tNext symbolTable: %d\n", sTb[i].listSymbolIndent[j].nextSymbolTable);

		}
	}
}

void compileDeclareConst()
{
	printf("\nIN CONST CHECK\n");

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
	print_symbolTable();
	token = getToken();
}

void compileDeclareVar()
{
	printf("\nIN VAR CHECK\n");
	if ((token == NULL) || (token->type != IDENT))
		error(13);

	int ret_checkIdent = checkIdent(token->name, 0, 0);

	if (ret_checkIdent == 0) /* Trung ten */
	{
		printf("\n==>Previous declaration of \"%s\" was here", token->name);
		error(31);
	}
	enter_ident(token->name, VAR_TYPE);
	print_symbolTable();
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

void compileDeclareProcedure()
{
	if ((token == NULL) || (token->type != IDENT))
		error(21);
	cur_level ++;

	int ret_checkIdent = checkIdent(token->name, PROCEDURE_TYPE, sTb[countSymbolTable-1].levelOfTable);

	if (ret_checkIdent == 0) /* Trung ten */
	{
		printf("\n==>Previous declaration of \"%s\" was here", token->name);
		error(31);
	}
	countSymbolTable ++;
	make_table(token->name);
	printf("====%d\n", sTb[countSymbolTable-1].levelOfTable);
	enter_ident_pro(token->name, PROCEDURE_TYPE, sTb[countSymbolTable-1].levelOfTable);
	print_symbolTable();
	token = getToken();
}

void make_table(char *name)
{
	sTb[countSymbolTable - 1].name = name;
	sTb[countSymbolTable - 1].index = countSymbolTable - 1;
	sTb[countSymbolTable - 1].levelOfTable = cur_level;
}

void addDeclareVariableInProcedure()
{
	if ((token == NULL) || (token->type != IDENT))
		error(17);

	int ret_checkIdent = checkIdent(token->name, PROCEDURE_TYPE, sTb[countSymbolTable-1].levelOfTable);

	if (ret_checkIdent == 0) /* Trung ten */
	{
		printf("\n==>Previous declaration of \"%s\" was here", token->name);
		error(31);
	}
	enter_ident(token->name, VAR_TYPE);
}