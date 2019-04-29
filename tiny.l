/****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice	*/
/* Kenneth C. Louden								*/
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
#define YY_NO_UNPUT
char tokenString[MAXTOKENLEN+1];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+
wholechar [0-9a-zA-Z]
%%

{identifier}{number}{wholechar}* {return ERROR;}
{number}{identifier}{wholechar}* {return ERROR;}

"if"            {return IF;}
"else"          {return ELSE;}
"int"           {return INT;}
"return"        {return RETURN;}
"void"          {return VOID;}
"while"         {return WHILE;}

"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}

"<"             {return LT;}
"<="            {return LTEQ;}
">"             {return GT;}
">="            {return GTEQ;}
"=="            {return EQ;}
"!="            {return NOTEQ;}

"="             {return ASSIGN;}
";"             {return SEMI;}
","             {return COMMA;}

"("             {return LPAREN;}
")"             {return RPAREN;}
"{"             {return LBRACE;}
"}"             {return RBRACE;}
"["             {return LBRACKET;}
"]"             {return RBRACKET;}

{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"/*"            { register int c;
					for(;;){
						while((c=input())!='*'&&c!=EOF){
//						fprintf(listing,"%c",c);
						if(c=='\n')lineno++;
						}
						if(c=='*'){
							while((c=input())=='*');
							if(c=='\n')lineno++;
							if(c=='/') break;
						}
						if(c==EOF)
						{
				//			fprintf(stderr,"EOF in comment\n");
						return COMMENT_ERROR;
						}
					}
                }
.               {return ERROR;}
%%
TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  fprintf(listing,"\t%d\t",lineno);
  if (TraceScan) {
  	printToken(currentToken,tokenString);
  }
  return currentToken;
}

