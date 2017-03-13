/*******************************************************************************
Arxeio ylopoihshs	: TStoixeiouListas.c
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#include "TStoixeiouListas.h"


void TSListasSetValue(TStoixeiouListas *stoixeioPtr, TStoixeiouListas testdata)
{   
	TSOurasSetValue( stoixeioPtr, testdata );
}


void TSListasSetEisodos(TStoixeiouListas *stoixeioPtr, unsigned int eisodos)
{   
	TSOurasSetEisodos( stoixeioPtr, eisodos );
}


void TSListasSetArithmos(TStoixeiouListas *stoixeioPtr, int arithmos)
{   
	TSOurasSetArithmos( stoixeioPtr, arithmos );
}


void TSListasSetProblepsi(TStoixeiouListas *stoixeioPtr, int problepsi)
{   
	TSOurasSetProblepsi( stoixeioPtr, problepsi );
}


void TSListasSetThesi(TStoixeiouListas *stoixeioPtr, int thesi)
{   
	TSOurasSetThesi( stoixeioPtr, thesi );
}

unsigned int TSListasGetEisodos(TStoixeiouOuras *stoixeioPtr){
	return TSOurasGetEisodos(stoixeioPtr);
}


void TSListasPrintValue(TStoixeiouListas testdata)
{
	TSOurasPrintValue( testdata );
}


/**************************************************8mallon den tha to xrisimopoiisoume
int TSListasReadValue(TStoixeiouListas *testdata)
{
	TSOurasReadValue( testdata );
}
*/


int TSListasIso(TStoixeiouListas stoixeio1, TStoixeiouListas stoixeio2)
{
	TSOurasIso( stoixeio1, stoixeio2 );
}
