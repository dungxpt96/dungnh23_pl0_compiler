#ifndef _SCANNER_H
#define _SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_IDENT_LEN 10
#define MAX_NUM_LEN 6

char id[MAX_IDENT_LEN + 1];
char num[MAX_NUM_LEN + 1];

FILE *fp;
int ch;
int numLine;
int numColumn;
int isComment;
int lastLine;
int lastColumn;
int lastLengthLine;
int hasBlock;
int begin;
char text[1000000];
int numChar;

/* Token Type */
typedef enum {
	NONE = 0,
	IDENT,
	NUMBER,
	BEGIN, 
	END, 
	IF, 
	THEN, 
	WHILE,
	DO, 
	CALL, 
	ODD, 
	TO,
	CONST,
	VAR, 
	PROCEDURE, 
	PROGRAM,
	ELSE, 
	FOR, 
	PLUS,	
	MINUS, 	
	TIMES, 	
	SLASH,
	EQU, 
	NEQ, 
	LSS,	
	LEQ,		
	GRT,		
	GEQ, 		
	LPARENT, 
	RPARENT,
	LBRACK, 
	RBRACK, 
	PERIOD, 	
	COMMA, 	
	SEMICOLON, 
	ASSIGN, 
	PERCENT
} TokenType;

typedef struct tokens{
	TokenType type;
	char name[20];
} token_t;

token_t *token;
token_t listToken[100000];
int numToken;

token_t *getToken();
token_t* checkKeyword(char *str);
void showListToken();
token_t* ignoreComment();
void showHelpCommand(); // Done
char getChar(); // Done\

#endif