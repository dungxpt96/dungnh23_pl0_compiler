#ifndef _PARSE_H
#define _PARSE_H

#include "scanner.h"
#define MAX_SIZE_CODE 1000
#define UNKNOW 99999

void compile(const char *);
void error(int id_error);

void compileTerm();
void compileFactor();
void compileExpression();
void compileCondition();
void compileStatement();
void compileBlock();
void compileProgram();

void handleConstBlock();
void handleVarBlock();
void handleProcedureBlock();
void handleBeginEndBlock();

void compileCallStatement();
void compileBeginEndStatement();
void compileIfElseStatement();
void compileWhileStatement();
void compileForStatement();
void compileWriteStatement();

typedef struct location{
	int base;
	int offset;
} location_t;

location_t *location_id;

typedef enum {
	OP_LA = 0,
	OP_LV,
	OP_LC,
	OP_LI,
	OP_INT, // Increment t
	OP_DCT, // Decrement t
	OP_J,
	OP_FJ,
	OP_HL,
	OP_ST,
	OP_CALL, // Call
	OP_EP,
	OP_EF,
	OP_RC,
	OP_RI,
	OP_WRC,
	OP_WRI,
	OP_WLN,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_NEG,
	OP_CV,
	OP_EQ,
	OP_NE,
	OP_GT,
	OP_LT,
	OP_GE,
	OP_LE,
	OP_BP
} OpCode ;

typedef struct instr{
	OpCode op;
	int p;
	int q;	
} instruction;

instruction m_code[MAX_SIZE_CODE];
int code_size;


void to_code(OpCode op, int p, int q);
void print_code();
void update_lastest_label(int value);

int label[100];
int label_size;
#endif