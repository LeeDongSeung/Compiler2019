#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations. */
static int location = 0;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine;
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse (TreeNode* t, 
				void (* preProc) (TreeNode *), 
				void (* postProc) (TreeNode *) ) 
{
	if (t != NULL) {

		preProc(t);
		int i;
		for (i = 0; i < MAXCHILDREN; i++)
			traverse(t->child[i], preProc, postProc);
		postProc(t);
		traverse(t->sibling, preProc, postProc);
	}
}

/* nullProc is a do-nothing procedure to
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc (TreeNode* t) {

	if (t == NULL) return;
	else return;
}





/*determine main function has valid type!*/
/*
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
             if(t->child[1]&&t->child[1]->attr.type!=VOID){
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
*/
