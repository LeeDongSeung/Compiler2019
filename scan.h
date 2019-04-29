/****************************************************/
/* File: scan.h										*/
/* The scanner interface for the TINY compiler		*/
/* Compiler Construction: Principles and Practic	*/
/* Kenneth C. Louden								*/
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_
/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN 40
#include "globals.h"
/* tokenString array stores the lexeme of each token*/
extern char tokenString[MAXTOKENLEN+1];
/* function getToken return the
 * next token in source file
 */
TokenType getToken(void);
#endif
