/****************************************************/
/* File: cm.y                                       */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

%{
#define YYPARSER /* distinguishes Yacc output from other code file */
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode*
static int savedNumber; /* for use in assignments as a number*/
static int savedLineno; /*for use*/
static TreeNode* savedTree;/*stores syntax tree for later return*/
static int yylex(void);
%}

/* reserved words */
%token IF ELSE INT RETURN VOID WHILE
/* multicharacter tokens */
%token ID NUM
%token PLUS MINUS
%token TIMES OVER
%token LTEQ LT GT GTEQ EQ NOTEQ
%token ASSIGN SEMI COMMA
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token ERROR ENDFILE
%token COMMENT COMMENT_ERROR

/* to resolve reduce shift conflict */
/*%right RPAREN RBRACE RBRACKET ELSE*/
/*parameter to resolve reduce/shift conflict in int a[], int a*/
%right RBRACKET RPAREN ELSE
%%

/* 1 */
program : declaration_list
		{
				savedTree = $1;
		}
		;
/* 2 */
declaration_list : declaration_list declaration
				 {
						 YYSTYPE t = $1;
						 if(t){
								 while(t->sibling){
										 t = t->sibling;
								 }
								 t->sibling = $2;
								 $$ = $1;
						 }
						 else{
								 $$ = $2;
						 }
				 }
				 | declaration
				 {
						 $$ = $1;
					
				 }
				 ;
/* 3 */
declaration : var_declaration
			{
					$$ = $1;
			}
			| fun_declaration
			{
					$$ = $1;
			}
			;
/* no need to add? 20190429 */
number : NUM
		{
				savedNumber = atoi(tokenString);
				savedLineno = lineno;
		}
		;
/* here!*/
identifier : ID
			{
					$$ = newExpNode(IdK);
					$$->attr.name = copyString(tokenString);
					savedLineno = lineno;
			}
			;
/* 4 */
var_declaration : type_specifier identifier SEMI
				{
						$$ = newDeclNode(VarK);
						$$->attr.name = $2->attr.name;
						$$->lineno = lineno;
						$$->sibling = newTypeNode(TypeNameK);
						$$->sibling->attr.type = $1->attr.type;
				}
				| type_specifier identifier LBRACKET number RBRACKET SEMI
				{
						
						$$ = newDeclNode(ArrK);
						$$->attr.name = $2->attr.name;
						$$->lineno = lineno;
						$$->sibling = newTypeNode(TypeNameK);
						$$->sibling->attr.type = $1->attr.type;
						$$->sibling->lineno = lineno;
						$$->sibling->sibling = newExpNode(ConstK);
						$$->sibling->sibling->attr.val = savedNumber;
						$$->sibling->sibling->lineno = lineno;
				}
				;
/* 5 */
type_specifier : INT
			{
				$$ = newTypeNode(TypeNameK);
				$$->attr.type = INT;
			}
			| VOID
			{
				$$ = newTypeNode(TypeNameK);
				$$->attr.type = VOID;
			}
			;
/* 6 */
fun_declaration : type_specifier identifier
				{
					$$ = newDeclNode(FuncK);
					$$->attr.name = $2->attr.name;
					$$->lineno = lineno;
				}
				LPAREN params RPAREN compound_stmt
				{
					$$ = $3;
					/*type line 123~125  3line!*/
					$$->child[0] = $1;
					/* parameter */
					$$->child[1] = $5;
					/* body */
					$$->child[2] = $7;
				}
				;
/* 7 */
params : param_list
		{
			$$ = $1;
		}
		| VOID
		{
			$$ = newParamNode(ParamVarK);
		}
		;

/* 8 */
param_list : param_list COMMA param
			{
				YYSTYPE t = $1;
				if(t){
					while(t->sibling)t = t->sibling;
					t->sibling = $3;
					$$ = $1;
				}
				else
						$$ = $3;
			}
			| param
			{
				$$ = $1;
			}
			;

/* 9 */
param : type_specifier identifier
	{
		$$ = newParamNode(ParamVarK);
		$$->child[0] = $1;
		$$->child[1] = $2;
		$$->attr.name = $2->attr.name;
	}
	| type_specifier identifier LBRACKET RBRACKET
	{
		$$ = newParamNode(ParamArrK);
		$$->attr.name = $2->attr.name;
		$$->child[0] = $1;
		$$->child[1] = $2;
	}
	;

/* 10 */
compound_stmt : LBRACE local_declarations statement_list RBRACE
				{
						$$ = newStmtNode(CompK);
						$$->child[0] = $2;
						$$->child[1] = $3;
				}
				;
/* 11 */
local_declarations : local_declarations var_declaration
				{
					YYSTYPE t = $1;
				//for local variable int!
				$2->sibling->intflag = 1;
					if(t){
							while(t->sibling) t = t->sibling;
							t->sibling = $2;
							$$ = $1;
					}
					else{
							$$ = $2;
					}
				}
				|
				{
					$$ = NULL;
				}
				;

/* 12 */
statement_list : statement_list statement
				{
						YYSTYPE t = $1;
						if(t){
								while(t->sibling)t=t->sibling;
								t->sibling = $2;
								$$ = $1;
						}
						else
								$$ = $2;
				}
				| 
				{
						$$ = NULL;
				}
				;

/* 13 */
statement : expression_stmt
			{
					$$ = $1;
			}
			| compound_stmt
			{
					$$ = $1;
			}
			| selection_stmt
			{
					$$ = $1;
			}
			| iteration_stmt
			{
					$$ = $1;
			}
			| return_stmt
			{
					$$ = $1;
			}
			;

/* 14 */
expression_stmt : expression SEMI
				{
						$$ = $1;
				}
				| SEMI
				{
						$$ = NULL;
				}
				;

/* 15 */
selection_stmt : IF LPAREN expression RPAREN statement
				{
					//	fprintf(listing,"12\n");
					$$ = newStmtNode(IfK);
					$$->child[0] = $3;
					$$->child[1] = $5;
				}
				| IF LPAREN expression RPAREN statement ELSE statement
				{
					//	fprintf(listing,"34\n");
					$$ = newStmtNode(IfK);
					$$->child[0] = $3;
					$$->child[1] = $5;
					$$->child[2] = $7;
				}
				;

/* 16 */
iteration_stmt : WHILE LPAREN expression RPAREN statement
				{
						$$ = newStmtNode(IterK);
						$$->child[0] = $3;
						$$->child[1]= $5;
				}
				;

/* 17 */
return_stmt : RETURN SEMI
			{
				$$ = newStmtNode(RetK);
			}
			| RETURN expression SEMI
			{
				$$ = newStmtNode(RetK);
				$$->child[0] = $2;
			}
			;
/* 18 */ 
expression : var ASSIGN expression
			{
				$$ = newExpNode(AssignK);
				$$->child[0] = $1;
				$$->child[1] = $3;
			}
			| simple_expression
			{
				$$ = $1;
			}
			;
	
/* 19 */
var : identifier
	{
		$$ = $1;
	}
	| identifier LBRACKET expression RBRACKET
	{
			$$ = newExpNode(ArrIdK);
			$$->attr.name = $1->attr.name;
			//why????? 2019 0430!
			$$->child[0] = $3;
			free($1);
	}
	;

/* 20 */
simple_expression : additive_expression relop additive_expression
					{
							$$ = $2;
							$$->child[0] = $1;
							$$->child[1] = $3;
					}
					| additive_expression
					{
							$$ = $1;
					}
					;

/* 21 */
relop : LTEQ
		{
			$$ = newExpNode(OpK);
			$$->attr.op = LTEQ;
		}
		| LT
		{
			$$ = newExpNode(OpK);
			$$->attr.op = LT;
		}
		| GT
		{
			$$ = newExpNode(OpK);
			$$->attr.op = GT;
		}
		| GTEQ
		{
			$$ = newExpNode(OpK);
			$$->attr.op = GTEQ;
		}
		| EQ
		{
			$$ = newExpNode(OpK);
			$$->attr.op= EQ;
		}
		| NOTEQ
		{
			$$ = newExpNode(OpK);
			$$->attr.op = NOTEQ;
		}
		;
/* 22*/
additive_expression : additive_expression addop term
					{
						$$ = $2;
						$$->child[0] = $1;
						$$->child[1] = $3;
					}
					| term
					{
						$$ = $1;
					}
					;
/* 23*/
addop : PLUS
		{
				$$ = newExpNode(OpK);
				$$->attr.op = PLUS;
		}
		| MINUS
		{
	//			fprintf(listing,"2\n");
				$$ = newExpNode(OpK);
				$$->attr.op = MINUS;
		}
		;
/* 24 */
term : term mulop factor
	{
		$$ = $2;
		$$->child[0] = $1;
		$$->child[1] = $3;
	}
	| factor
	{
			$$ = $1;
	}
	;
/* 25 */
mulop : TIMES
		{
				$$ = newExpNode(OpK);
				$$->attr.op = TIMES;
		}
		| OVER
		{
				$$ = newExpNode(OpK);
				$$->attr.op = OVER;
		}
		;
	
/* 26 */
factor : LPAREN expression RPAREN
		{
			$$ = $2;
		}
		| var
		{
				$$ = $1;
		}
		| call
		{
				$$ = $1;
		}
		| number
		{
			$$ = newExpNode(ConstK);
			$$->attr.val = savedNumber;
			$$->lineno = savedLineno;
		}
		;
	
/* 27 */
call : identifier
	{
		$$ = newExpNode(CallK);
		$$->attr.name = $1->attr.name;
		savedLineno = $1->lineno;
		free($1);

	}
	LPAREN args RPAREN
	{
		$$ = $2;
		$$->child[0] = $4;
		$$->lineno = savedLineno;
	}
	;

/* 28 */
args : arg_list
	{
		$$ = $1;
	}
	|
	{
		$$ = NULL;
	}
	;
/* 29 */
arg_list : arg_list COMMA expression
		{
			YYSTYPE t = $1;
			if(t){
				while(t->sibling)t=t->sibling;
				t->sibling = $3;
				$$ = $1;
			}
			else
					$$ = $3;
		}
		| expression
		{
			$$ = $1;
		}
		;
%%

int yyerror(char*message){
	fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
	fprintf(listing,"Current Token: ");
	printToken(yychar,tokenString);
	Error = 1;
	return 0;
}
/* yylex calls getToken to make Yacc/Bison output
 * compatible with earlier version of
 * the TINY scanner
 */
static int yylex(void){
		return getToken();
}
TreeNode* parse(void){
		yyparse();
		return savedTree;
}

