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

void buildSymtab(TreeNode *syntaxTree){
    /*dynamic allocation for hashTable?*/
    insertNode(syntaxTree,0);
    // typeCheck(syntaxTree);
     mainCheck(syntaxTree);
    return;
}
void insertNode(TreeNode*t,int depth){
    int i=0;
    if(hashTable[depth]==NULL){
        hashTable[depth] = (BucketList*)calloc(SIZE,sizeof(BucketList));
    }
    i=0;
    TreeNode* here = NULL;
    int preorderflag = 0;
    for(;t;t=t->sibling){
        preorderflag = 0;
        switch(t->nodekind){
            case StmtK:
                if(t->kind.stmt == IfK){
                    insertNode(t->child[1],depth+1);
                    insertNode(t->child[2],depth+1);
                }
                else if(t->kind.stmt == IterK){
                    insertNode(t->child[1],depth+1);
                }
                else if(t->kind.stmt == CompK){
                    /* local declaration in compound statement, so plus scope!*/
                    insertNode(t->child[0],depth+1);
                    insertNode(t->child[1],depth+1);
                }
				freeBucketList(hashTable[depth+1]);
            break;
            case ExpK:
                if(t->kind.exp == IdK){
                    if((here=st_lookup(t->attr.name,depth))==NULL){
                
                        printError(t,"Variable did not declared before");
                        return;
                    }
                    st_insert(t->attr.name,t->lineno,1,depth,t);
                    t->type = INT;
                    t->declTree = here;
                   
                }
                else if(t->kind.exp == ArrIdK){
                   if((here=st_lookup(t->attr.name,depth))==NULL){
                        printError(t,"Variable did not declared before");
                        return;
                    }
                    st_insert(t->attr.name,t->lineno,1,depth,t);
                    t->type = INT;
                    t->declTree = here;
                }
                else if(t->kind.exp == CallK){
                    if((here=st_lookup(t->attr.name,depth))==NULL){
                        printError(t,"Function did not declared before");
                        return;
                    }
                    st_insert(t->attr.name,t->lineno,1,depth,t);
                    t->declTree = here;
                }
            break;
            case DeclK:
                if(t->kind.decl == FuncK){
                    if(st_find(t->attr.name,depth)){
                   
                        printError(t,"Same Function Redeclaration");
                        return;
                    }
                    st_insert(t->attr.name,t->lineno,1,depth,t);
                }
                else if(t->kind.decl == VarK||t->kind.decl==ArrK){
                        preorderflag = 1;
                    if(st_find(t->attr.name,depth)){
                        printError(t,"Same VariableRedeclaration");
                        return;
                    }
                    st_insert(t->attr.name,t->lineno,1,depth,t);
                }
            break;
            case TypeK:
            break;
            case ParamK:
                for(;t;t=t->sibling){
                    /*Parameter*/
                    if (hashTable[depth+1] == NULL)
                    {
                        hashTable[depth+1] = (BucketList *)calloc(SIZE, sizeof(BucketList));
                    }
                
                    st_insert(t->child[1]->attr.name, t->lineno, 1, depth + 1, t);
                }
            return;
        }
        if (!preorderflag)
            {
                for (i = 0; i < MAXCHILDREN; i++)
                {
                    if (t->child[i])
                        insertNode(t->child[i] , depth);
                }
            }
    }
   freeBucketList(hashTable[depth]);
}
void typeCheck(TreeNode *t){
    //postorder!
    return;
}
