/*******************************************************/
/* File : symtab.c                                     */
/* symbol table implementation for the TINY compiler   */
/* (allows only one symbol table)                      */
/* Symbol table is implemented as a chained            */
/* hash table                                          */
/* Compiler Construction: Principles and Practice      */
/* Kenneth C. Louden                                   */
/*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* SIZE is the size of the hash table */


/* SHIFT is the power of two used as multiplier
   in hash function */
#define SHIFT 4

/* the hash function */
static int hash(char *key){
		int temp = 0,i=0;
		while(key[i]!='\0'){
				temp = ((temp<<SHIFT)+key[i])%SIZE;
				i++;
		}
		return temp;
}


TreeNode* st_find(char*name,int depth){
	int h = hash(name);
	BucketList l = hashTable[depth][h];
	while(l!=NULL&&strcmp(l->name,name)!=0){
			l = l->next;
	}
	//does not exist!
	if(l==NULL)return NULL;
	//exist!!!
	return l->tree;
}
void st_insert(char*name,int lineno,int loc,int depth,TreeNode*tree){
	int h = hash(name);
	BucketList l = hashTable[depth][h];
	//printf("%s %d\n",name,depth);
	/*variable not yet in table */
	if(l==NULL){
		l = (BucketList)calloc(1,sizeof(struct BucketListRec));
		l->name = name;
		l->lines = (LineList)calloc(1,sizeof(struct LineListRec));
		l->lines->lineno = lineno;
		l->memloc = loc;
		l->next = hashTable[depth][h];
		l->tree = tree;
		hashTable[depth][h] = l;
		printf("%p\n",hashTable[depth][h]);
	}
	else{
		LineList t = l->lines;
		while(t->next) t = t->next;
		t->next = (LineList)calloc(1,sizeof(struct LineListRec));
		t->next->lineno = lineno;
	}
	return;
}/* st_inset */
void freeBucketList(BucketList*arr){
	int i=0;
	BucketList del = NULL;
	LineList curline = NULL,delline = NULL;
	for(;i<SIZE;i++){
		BucketList l = arr[i];
		while(l){
			del = l;
			curline = delline = del->lines;
			while(curline){
				delline = curline;
				curline = curline->next;
				free(delline);
			}
			l = l->next;
			free(del);
		}
	}
	return;
}
/*문제가 있음!*/
TreeNode* st_lookup(char*name,int depth){
	int h = hash(name);
	int i=depth;
	for(;i>=0;i--){
		BucketList l = hashTable[i][h];
		printf("%p\n",l);
		while(l!=NULL&&strcmp(l->name,name)!=0){
			printf("%d %s %s\n",depth,l->name,name);
			l=l->next;
		}
		if(l)return l->tree;
	}
	return NULL;
}