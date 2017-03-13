/*******************************************************************************
Arxeio ylopoihshs	: TStoixeioyTree.h
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/

#ifndef __TStoixeioyTree_H__
#define __TStoixeioyTree_H__


typedef struct Rec{
	char onoma[25];
	char epwnumo[25];	
} TStoixeioyTree;	   /*o typos tis ouras*/

//oles oi parakatw sunartiseis kalountai apo to ch8_AVLpointer kai ch8_BSTpointer

int TStree_iso(TStoixeioyTree Elem1, TStoixeioyTree Elem2);
int TStree_mikrotero(TStoixeioyTree Elem1, TStoixeioyTree Elem2);
int TStree_megalytero(TStoixeioyTree Elem1, TStoixeioyTree Elem2);

int TStree_mikrotero_iso(TStoixeioyTree Elem1, TStoixeioyTree Elem2);
int TStree_megalytero_iso(TStoixeioyTree Elem1, TStoixeioyTree Elem2);
int TStree_diaforo(TStoixeioyTree Elem1, TStoixeioyTree Elem2);

void TStree_setValues (TStoixeioyTree *target, TStoixeioyTree source);
void TStree_writeValue(TStoixeioyTree Elem);
#endif
