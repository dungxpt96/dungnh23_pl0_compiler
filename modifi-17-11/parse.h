#ifndef _PARSE_H
#define _PARSE_H

#include "scanner.h"

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

#endif