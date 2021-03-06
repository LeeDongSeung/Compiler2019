/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef YYPARSER
#include "cm.tab.h"
#define YYPARSER
#endif


/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8
/*
typedef enum
	{ENDFILE,ERROR,
	IF,ELSE,INT,RETURN,WHILE,VOID,
	ID,NUM,
	ASSIGN,EQ,LT,LTEQ,GT,GTEQ,NOTEQ,PLUS,MINUS,TIMES,OVER,
	LPAREN,RPAREN,SEMI,COMMA,LBRACE,RBRACE,LBRACKET,RBRACKET,
	COMMENT,COMMENT_ERROR
	
	}TokenType;
*/

typedef int TokenType;
extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int lineno;
/* source line number for listing */
/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum { StmtK,ExpK,DeclK,TypeK,ParamK } NodeKind;
typedef enum { IfK, IterK,RetK,CompK } StmtKind;
typedef enum { OpK, ConstK, IdK,ArrIdK,CallK,AssignK } ExpKind;
typedef enum {FuncK,VarK,ArrK} DeclKind;
typedef enum {ParamVarK,ParamArrK} ParamKind;
typedef enum {TypeNameK} TypeKind;
/* ExpType is used for type checking */
typedef enum { Void, Integer, Array } ExpType;

#define MAXCHILDREN 3
#define Array 289
typedef struct treeNode
   {
     struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union {
         StmtKind stmt;
         ExpKind exp;
		 DeclKind decl;
		 ParamKind param;
		 TypeKind type;
     } kind;
     union { 
		TokenType type;
         TokenType op;
         int val,size;
         char * name;
     } attr;
     int intflag;
     ExpType type; /* for type checking of exps */
	struct treeNode*declTree;
} TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error;

#endif
