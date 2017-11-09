#ifndef _SCANNER_H
#define _SCANNER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_IDENT_LEN 10
#define MAX_LENGTH_NUM 6

char* fileInput;
int numFile = 0;
int row;

/* with type NUMBER and IDENT */
char id[MAX_IDENT_LEN + 1];
char num[MAX_LENGTH_NUM + 1];

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
token_t keyWord[] = {
	{ BEGIN, "BEGIN" },
	{ END, "END" },
	{ IF, "IF" },
	{ THEN, "THEN" },
	{ WHILE, "WHILE" },
	{ DO, "DO" },
	{ CALL, "CALL" },
	{ ODD, "ODD" },
	{ TO, "TO" },
	{ CONST, "CONST" },
	{ VAR, "VAR" },
	{ PROCEDURE, "PROCEDURE" },
	{ PROGRAM, "PROGRAM" },
	{ ELSE, "ELSE" },
	{ FOR, "FOR" }
};

token_t convertToToken[] = {
	{ NONE, "NONE"},
	{ IDENT, ""},
	{ NUMBER, ""},
	{ BEGIN, "BEGIN" },
	{ END, "END" },
	{ IF, "IF" },
	{ THEN, "THEN" },
	{ WHILE, "WHILE" },
	{ DO, "DO" },
	{ CALL, "CALL" },
	{ ODD, "ODD" },
	{ TO, "TO" },
	{ CONST, "CONST" },
	{ VAR, "VAR" },
	{ PROCEDURE, "PROCEDURE" },
	{ PROGRAM, "PROGRAM" },
	{ ELSE, "ELSE" },
	{ FOR, "FOR" },
	{ PLUS,	"PLUS" },	
	{ MINUS, "MINUS" },		
	{ TIMES, "TIMES" },		
	{ SLASH, "SLASH" },	
	{ EQU, "EQU" },
	{ NEQ, "NEQ" },	
	{ LSS, "LSS" },	
	{ LEQ, "LEQ" },		
	{ GRT, "GRT" },		
	{ GEQ, "GEQ" },		
	{ LPARENT, "LPARENT" },	
	{ RPARENT, "RPARENT" },
	{ LBRACK, "LBRACK" },	
	{ RBRACK, "RBRACK" },	
	{ PERIOD, "PERIOD" },		
	{ COMMA, "COMMA" },	
	{ SEMICOLON, "SEMICOLON" },	
	{ ASSIGN, "ASSIGN" },	
	{ PERCENT, "PERCENT" }
};

/* readable token from file input  */
token_t *listToken;
int numToken = 0;

void showHelpCommand();
void scanner(bool l, bool s);
token_t *getToken(char *filename);
TokenType checkKeyWord(char *str);
void showListToken(char *filename);

#endif