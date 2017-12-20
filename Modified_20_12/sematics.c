#include "sematics.h"
#include "parse.h"
#include "scanner.h"
#include <ctype.h>

char *objectTypeString[] = {"variable", "const", "array", "procedure"};
/* Kiem tra ident da duoc khai bao hay chua trong pham vi hien tai*/
/* Dua vao bien countSymbolTable de xac dinh hien tai la bang so bao nhieu */
int checkIdent(char *id_name, objectType ot, int level)
{
	//printf("\ncheckIdent => level: %d\n", level);
	int order = countSymbolTable - 1; /* thu tu cua bang can lookup */
	if (ot == PROCEDURE_TYPE)
	{
		int j;
		for (j = countSymbolTable - 1; j >= 0; j--)
		{
			if (sTb[j].levelOfTable == (level))
			{
				order = j;
				break;
			}
		}
	}
	int i;
	int numberOfIdent = sTb[order].countSymbolIndent;
	for (i = 0; i < numberOfIdent; i++)
	{
		char name1[100], name2[100];
		strcpy(name1, sTb[order].listSymbolIndent[i].name);
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

		//printf("\ncompare: %s - %s\n", name1, name2);
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
				sTb[i].listSymbolIndent[nextIdent].value = code_size;
				sTb[i].listSymbolIndent[nextIdent].nextSymbolTable = countSymbolTable - 1;
				sTb[countSymbolTable - 1].parentSymbolTable = sTb[i].index;
			}
			sTb[i].listSymbolIndent[nextIdent].index =nextIdent;
			sTb[i].countSymbolIndent ++;
			break;
		}
	}
}

void enter_ident(char *id_name, objectType ot, int t)
{
	int nextIdent = sTb[countSymbolTable - 1].countSymbolIndent;

	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].isArgValue = t;

	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].name = id_name;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].type = ot;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].nextSymbolTable = -1;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].index =nextIdent;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].offset = 4 + sTb[countSymbolTable - 1].counterVarConst;
	sTb[countSymbolTable - 1].countSymbolIndent ++;
	sTb[countSymbolTable - 1].counterVarConst ++;
}

void enter_ident_array(char *id_name, objectType ot, int value)
{
	int nextIdent = sTb[countSymbolTable - 1].countSymbolIndent;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].name = id_name;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].type = ot;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].nextSymbolTable = -1;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].index =nextIdent;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].value = value;
	sTb[countSymbolTable - 1].listSymbolIndent[nextIdent].offset = 4 + sTb[countSymbolTable - 1].counterVarConst;

	sTb[countSymbolTable - 1].countSymbolIndent ++;
	sTb[countSymbolTable - 1].counterVarConst += value;	
}

/* Chi ra vi tri cua danh bieu trong bang ky hieu */
location_t *location_ident(char *id_name)
{
	location_t *temp = (location_t *) malloc (sizeof(location_t));
	int base = 0;
	int offset = 4;

	int current = countSymbolTable - 1;;

	int j;
	for (j = countSymbolTable - 1; j >= 0; j--)
	{
		if (sTb[j].levelOfTable == cur_level)
		{
			current = j;
			break;
		}
	}

	while (current != -1)
	{
		//printf("\nLocation ident, current level = %d\n", current);
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

			//printf("--%s--%s\n", sTb[current].listSymbolIndent[i].name, id_name);
			if (strcmp(name1, name2) == 0)
			{
				temp->base = base;
				temp->offset = sTb[current].listSymbolIndent[i].offset;
				if (sTb[current].listSymbolIndent[i].type == PROCEDURE_TYPE)
				{
					temp->offset = sTb[current].listSymbolIndent[i].value;
				}
				//printf("\n return %d - %d \n", temp->base, temp->offset);
				return temp; /* Trung ten */
			}
		}
		current = sTb[current].parentSymbolTable;
		base ++;
	}
	temp->base = -1;
	temp->offset = -1;
	return temp;
}
/*
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
		printf("\tcounterVarConst = %d\n", 	sTb[i].counterVarConst);
		printf("\tDanh sach cac ky hieu:\n");
		int j;
		int countSym = sTb[i].countSymbolIndent;
		for (j = 0; j < countSym; j++)
		{
			printf("\t\t--Index: %d\n", sTb[i].listSymbolIndent[j].index);
			printf("\t\tName: %s\n", sTb[i].listSymbolIndent[j].name);
			printf("\t\tType: %s\n", objectTypeString[(int) sTb[i].listSymbolIndent[j].type]);
			printf("\t\tValue: %d\n", sTb[i].listSymbolIndent[j].value);
			printf("\t\tOffset: %d\n", sTb[i].listSymbolIndent[j].offset);
			printf("\t\tIs Var Arg: %d\n", sTb[i].listSymbolIndent[j].isArgValue);
			printf("\t\tNext symbolTable: %d\n", sTb[i].listSymbolIndent[j].nextSymbolTable);

		}
	}
}
//*/
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

	int index = sTb[countSymbolTable - 1].countSymbolIndent;

	enter_ident(token->name, CONST_TYPE, 0);
	token = getToken();
	if ((token == NULL) || (token->type != EQU))
		error(9);

	token = getToken();
	if ((token == NULL) || (token->type != NUMBER))
		error(10);

	sTb[countSymbolTable - 1].listSymbolIndent[index].value = atoi(token->name);
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
		enter_ident(tempTokenName, VAR_TYPE, 0);
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
	//printf("\nCurrent level when appear procedure %d\n", cur_level);
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

void addDeclareVariableInProcedure(int ot)
{
	if ((token == NULL) || (token->type != IDENT))
		error(17);

	int ret_checkIdent = checkIdent(token->name, PROCEDURE_TYPE, sTb[countSymbolTable-1].levelOfTable);
	//printf("\nadd addDeclareVariableInProcedure: %d\n", ret_checkIdent);
	if (ret_checkIdent == 0) /* Trung ten */
	{
		printf("\n==>Previous declaration of \"%s\" was here", token->name);
		error(32);
	}
	enter_ident(token->name, VAR_TYPE, ot);
}

void handleIdentStatement()
{
	location_id = location_ident(token->name);

	if (location_id->base < 0)
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

	location_id = location_ident(token->name);

	if (location_id->base < 0)
	{
		printf("\n\"%s\" undeclared (first use in this function)\n", token->name);
		error(31);
	}

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
	//printf("\nCheck ident \"%s\"\n", token->name);
	//printf("\nhandleFactorIdent\n");
	location_id = location_ident(token->name);

	if (location_id->base < 0)
	{
		printf("\n\"%s\" undeclared (first use in this function)\n", token->name);
		error(31);
	}
	objectType t = getKind(token->name);
	checkWord[numWord++] = token->type;
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

int getNumVC()
{
	int current = countSymbolTable - 1;;

	int j;
	for (j = countSymbolTable - 1; j >= 0; j--)
	{
		if (sTb[j].levelOfTable == cur_level)
		{
			current = j;
			break;
		}
	}

	return sTb[current].counterVarConst;
}

int isVarArgument(char *name)
{
	int current = countSymbolTable - 1;;

	int j;
	for (j = countSymbolTable - 1; j >= 0; j--)
	{
		if (sTb[j].levelOfTable == cur_level)
		{
			current = j;
			break;
		}
	}

	while (current != -1)
	{
		//printf("\nLocation ident, current level = %d\n", current);
		int numberOfIdent = sTb[current].countSymbolIndent;
		int i;
		for (i = 0; i < numberOfIdent; i++)
		{
			char name1[100], name2[100];
			strcpy(name1, sTb[current].listSymbolIndent[i].name);
			strcpy(name2, name);
			int i1, i2;
			for (i1 = 0; i1 < strlen(name1); i1++)
			{
				name1[i1] = toupper(name1[i1]);
			}

			for (i2 = 0; i2 <strlen(name2); i2 ++)
			{
				name2[i2] = toupper(name2[i2]);
			}

			//printf("--%s--%s\n", sTb[current].listSymbolIndent[i].name, id_name);
			if (strcmp(name1, name2) == 0)
			{
				return sTb[current].listSymbolIndent[i].isArgValue;
			}
		}
		current = sTb[current].parentSymbolTable;
	}
	
	return 0;
}
