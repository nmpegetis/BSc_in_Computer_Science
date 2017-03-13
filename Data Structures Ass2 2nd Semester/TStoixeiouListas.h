/*******************************************************************************
Arxeio ylopoihshs	: TStoixeiouListas.h
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#ifndef __TStoixeiouListas_H__
#define __TStoixeiouListas_H__
#include "TStoixeiouOuras.h"
typedef TStoixeiouOuras TStoixeiouListas;

void TSListasSetValue(TStoixeiouListas *stoixeioPtr, TStoixeiouListas testdata);

void TSListasSetEisodos(TStoixeiouListas *stoixeioPtr, unsigned int eisodos);
void TSListasSetArithmos(TStoixeiouListas *stoixeioPtr, int arithmos);
void TSListasSetProblepsi(TStoixeiouListas *stoixeioPtr, int problepsi);
void TSListasSetThesi(TStoixeiouListas *stoixeioPtr, int thesi);
unsigned int TSListasGetEisodos(TStoixeiouListas *stoixeioPtr);

void TSListasPrintValue(TStoixeiouListas testdata);
int TSListasReadValue(TStoixeiouListas *testdata);
int TSListasIso(TStoixeiouListas stoixeio1, TStoixeiouListas stoixeio2);
#endif
