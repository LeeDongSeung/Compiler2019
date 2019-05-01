/****************************************************/
/* File: util.h                                     */
/* Utility functions for the TINY compiler          */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_
/*
const char*StmtTable[]={
		"If Statement\n",
		"While Statement\n",
		"Return Statement\n",
		"Compound Statement\n",
		"Unknown Statement\n"
};
*/
/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType, const char* );


/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind);


/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * );

/*Function newDeclNode creates a new statement
 * node for syntax tree construction
 */
TreeNode* newDeclNode(DeclKind);

/* Function newTypeNode creates a new statement
 * node for syntax tree construction
 */
TreeNode* newTypeNode(TypeKind);
/* Function newParamNode creates a new statement
 * node for syntax tree construction
 */
TreeNode* newParamNode(ParamKind);
#endif
