/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;
void printError(TreeNode * t, const char *error){
    if(t==NULL)return;
    fprintf(listing, "%s at line :%d\n", error, t->lineno);
    Error = TRUE;
}

/*determine main function has valid type!*/
void mainCheck(TreeNode*t){
    if(t==NULL){
        printError(t,"There does not exist main function\n");
        return;
    }
    for(;t->sibling;t=t->sibling);
    if(t->nodekind==DeclK&&t->kind.decl==FuncK&&strcmp(t->attr.name,"main")==0){
           if(t->child[0]&&t->child[0]->nodekind==TypeK){
              if(t->child[0]->attr.type!=VOID){
                   printError(t,"Return type of main function is void type!");
                    return;
             }
             if(t->child[1]!=NULL){
                   printError(t,"Parameter of main function is void type!");
                    return;
              }
               return;
         }
    }
    else{
        printError(t,"There does not exist main function\n");
        return;
    }
}