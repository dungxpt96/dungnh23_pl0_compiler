#ifndef _SEMATICS_H
#define _SEMATICS_H

#include <string.h>
#include <stdio.h>

/* Chi so cac bang ky hieu */
int countSymbolTable; // start = 1;
/* Mot mang cac bang ky hieu */
int cur_level;
int cur_numTable;

typedef enum {
	VAR_TYPE = 0, 
	CONST_TYPE,
	ARRAY_TYPE,
	PROCEDURE_TYPE
} objectType;

/* Danh bieu */
struct symbolIdent {
	int index; // So thu tu cua danh bieu trong bang ky hieu
	char *name; // Ten cua danh bieu
	objectType type; // Loai danh bieu: variable, array, const, subProcedure
	int offset;
	int value; /* If is NUMBER */
	int nextSymbolTable; // Trong truong hop subProcedure se su dung truong nay, neu khong la -1
};
typedef struct symbolIdent symbolIdent;

/* Bang ky hieu */
struct symbolTable
{
	int index; // chi so cua Bang Ky Hieu
	char *name;
	int parentSymbolTable; // Chi so cua Bang Cha sinh ra bang ky hieu nay
	int levelOfTable;
	int countSymbolIndent; // Tong so danh bieu hien tai co trong bang
	int sizeOfTable; // Tong dung luong cua bang ky hieu (bao gom ca cac bang con)
	symbolIdent listSymbolIndent[1000]; /* Danh sach cac danh bieu */
};
typedef struct symbolTable symbolTable;

symbolTable sTb[1000];

/* Kiem tra ident da duoc khai bao hay chua */
int checkIdent(char *id_name, objectType ot, int level);
/* Them mot dinh danh vao bang */
void enter_ident_pro(char *id_name, objectType ot, int level);
void enter_ident(char *id_name, objectType ot);
/* Chi ra vi tri cua danh bieu trong bang ky hieu */
int location_ident(char *id_name);

void print_symbolTable();

void compileDeclareConst();
void compileDeclareVar();
void compileDeclareProcedure();
void make_table(char *name);


#endif 