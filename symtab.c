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
#define SIZE 211

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


int st_find(char*name,BucketList*arr){
	int h = hash(name);
	BucketList l = arr[h];
	while(l!=NULL&&strcmp(l->name,name)!=0){
			l = l->next;
	}
	//does not exist!
	if(l==NULL)return -1;
	//exist!!!
	return 1;
}
void st_insert(char*name,int lineno,int loc,BucketList*arr){
	int h = hash(name);
	BucketList l = arr[h];
	while(l!=NULL&&(strcmp(l->name,name)!=0))l = l->next;
	/*variable not yet in table */
	if(l==NULL){
		l = (BucketList)calloc(1,sizeof(struct BucketListRec));
		l->name = name;
		l->lines = (LineList)calloc(1,sizeof(struct LineListRec));
		l->lines->lineno = lineno;
		l->memloc = loc;
		l->next = arr[h];
		arr[h] = l;
	}
	else{
		LineList t = l->lines;
		while(t->next) t = t->next;
		t->next = (LineList)calloc(1,sizeof(struct LineListRec));
		t->next->lineno = lineno;
	}
	return;
}/* st_inset */

