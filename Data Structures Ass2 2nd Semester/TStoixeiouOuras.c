/*******************************************************************************
Arxeio ylopoihshs	: TStoixeiouOuras.c
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#include <stdio.h>
#include "TStoixeiouOuras.h"

/***********************eisagwgi stin oura twn stoixeiwn tou pelati [erwtima 4.i.a]*****************************/


void TSOurasSetValue(TStoixeiouOuras *stoixeioPtr, TStoixeiouOuras testdata)
{   
	stoixeioPtr->lepto_eisodou = testdata.lepto_eisodou;	/*lepto eidodou*/
	stoixeioPtr->auksontas_ar_pelati = testdata.auksontas_ar_pelati;/*auksontas arithmos pelati*/	
	stoixeioPtr->problepsi = testdata.problepsi;		/*problepomenos xronos anamonis*/
	stoixeioPtr->thesi = testdata.thesi;			/*thesi tou pelati*/

}

void TSOurasSetEisodos(TStoixeiouOuras *stoixeioPtr, unsigned int eisodos)
{   
	stoixeioPtr->lepto_eisodou = eisodos;	/*lepto eidodou*/
}


void TSOurasSetArithmos(TStoixeiouOuras *stoixeioPtr, int arithmos)
{   
	stoixeioPtr->auksontas_ar_pelati = arithmos;/*auksontas arithmos pelati*/	
}


void TSOurasSetProblepsi(TStoixeiouOuras *stoixeioPtr, int problepsi)
{   	
	stoixeioPtr->problepsi = problepsi;		/*problepomenos xronos anamonis*/
}


void TSOurasSetThesi(TStoixeiouOuras *stoixeioPtr, int thesi)
{   
	stoixeioPtr->thesi = thesi;			/*thesi tou pelati*/
}


unsigned int TSOurasGetEisodos(TStoixeiouOuras *stoixeioPtr){
	return stoixeioPtr->lepto_eisodou;
}


void TSOurasPrintValue(TStoixeiouOuras testdata)
{
	printf("{| min:%d / s_n:%d / pr:%d / pos:%d |} ", testdata.lepto_eisodou, testdata.auksontas_ar_pelati, testdata.problepsi, testdata.thesi );	/*ektupwnei ta stoixeia tou kathe pelati pou perimenei stin oura*/
}
/*
int TSOurasReadValue(TStoixeiouOuras *testdata)	//isws kai na min mas xreiazetai...mallon telika den mas xreiazetai
{ 	printf("Dwse enan ari8mo: ");		//basika xreiazetai stin periptwsi pou den dexetai apo ti grammi entolwn ta orismata oute apo ti scanf
	if (scanf("%d", testdata->lepto_eisodou)!= 1)
		return 0;
	else return 1;
}
*/
int TSOurasIso(TStoixeiouOuras stoixeio1, TStoixeiouOuras stoixeio2)
{
/*	if((stoixeio1.lepto_eisodou == stoixeio2.lepto_eisodou) && (stoixeio1.auksontas_ar_pelati == stoixeio2.auksontas_ar_pelati) && (stoixeio1.problepsi == stoixeio2.problepsi) && (stoixeio1.thesi == stoixeio2.thesi)) return 1;
	return 0;*/ //kanonika isxuei auto alla stin periptwsi mas epeidi den einai toso apaititiko auto pou zititai kai kathe lepto mpainei mono enas pelati mporoume na to aplopoiisoume se auti ti morfi
	return (stoixeio1.lepto_eisodou == stoixeio2.lepto_eisodou);
}
