/*******************************************************************************
Arxeio ylopoihshs	: TStoixeiouOuras.h
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#ifndef __TStoixeioOuras__ 
#define __TStoixeioOuras__

/***********************ulopoiisi allagis TStoixeiouOuras se struct[erwtima 3]*****************************/

typedef struct {
	int lepto_eisodou;		/*lepto eidodou*/	//auto pou itan prin int 
	int auksontas_ar_pelati;	/*auksonta arithmo pelati*/
	int problepsi;			/*problepomeno xrono anamonis*/
	int thesi;			/*i "pragmatiki" thesi tou pelati*/
} TStoixeiouOuras;	   /*o tupos tis ouras*/



void TSOurasSetValue(TStoixeiouOuras *stoixeioPtr, TStoixeiouOuras testdata);	/*allazei tin timi tou stoixeiou*/

void TSOurasSetEisodos(TStoixeiouOuras *stoixeioPtr, unsigned int eisodos);
void TSOurasSetArithmos(TStoixeiouOuras *stoixeioPtr, int arithmos);
void TSOurasSetProblepsi(TStoixeiouOuras *stoixeioPtr, int problepsi);
void TSOurasSetThesi(TStoixeiouOuras *stoixeioPtr, int thesi);
unsigned int TSOurasGetEisodos(TStoixeiouOuras *stoixeioPtr);

void TSOurasPrintValue(TStoixeiouOuras testdata);	/*ektupwnei to stoixeio*/
int TSOurasReadValue(TStoixeiouOuras *testdata);	/*diabazei enan arithmo kai ton bazei sto testdata*//*to readValue den tha to xrisimopoiisw*/
int TSOurasIso(TStoixeiouOuras stoixeio1, TStoixeiouOuras stoixeio2);

#endif
