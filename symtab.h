/*******************************************************/
/* File : symtab.h                                     */
/* symbol table interface for the TINY compiler        */
/* (allows only one symbol table)                      */
/* Compiler Construction: Principles and Practice      */
/* Kenneth C. Louden                                   */
/*******************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include "globals.h"

/* the list of line numbef of the source
 * code in which a variable is referenced
 */

typedef struct LineListRec{
		int lineno;
		struct LineListRec*next;
}*LineList;

/* The record in the bucket lists for
 * each variable, including name,
 * assigned memory location, and
 * the list of line number in which
 * it appears in the source code
 */
#define SIZE 211
typedef struct BucketListRec{
		char* name;
        TreeNode*tree;
		LineList lines;
		int memloc;/* memory location for variable */
		struct BucketListRec*next;
}*BucketList;
/*to determine redeclaration!*/
TreeNode* st_find(char*name,int depth);
#define MAX_SCOPE 200
/* hash table */
/* indirecting addressing impossible!
2019 05 09 i need to complement this more!*/
BucketList*hashTable[MAX_SCOPE];
/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory locations is inserted only the
 * first time, otherwise ignored
 */
void st_insert(char*name,int lineno,int loc,int depth,TreeNode*tree);
/* Function st_lookup returns the memory
 * location of a variable or -1 if not found
 */
TreeNode*st_lookup(char*name,int depth);

/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */
void printSymTab(FILE*listing);
void freeBucketList(BucketList*arr);
#endif
