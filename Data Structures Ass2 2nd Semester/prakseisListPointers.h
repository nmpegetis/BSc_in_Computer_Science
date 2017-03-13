/*******************************************************************************
Arxeio ylopoihshs	: prakseisListPointers.h
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#ifndef __CH7_CLPOINTER__ 
#define __CH7_CLPOINTER__
#include "TStoixeiouListas.h"

/*dhlwseis tupwn*/

typedef struct tupos_komvou *tupos_deikti;	//gia OA...perissotera mesa sto BankQueueOA.c

/*dhlwseis sunarthsewn*/

/*dhmiourgia listas*/
void LIST_dimiourgia(tupos_deikti *lista);

void LIST_katastrofi(tupos_deikti * const lista);

/*prakseis elegxou*/
int LIST_keni(const tupos_deikti lista);

/*prakseis prosbashs*/
void LIST_periexomeno(const tupos_deikti p, TStoixeiouListas *val);

void LIST_allagi(tupos_deikti * const p, TStoixeiouListas stoixeio);

void LIST_diadromi(const tupos_deikti lista, int * const error);

/*prakseis eisagwgh-diagrafh*/
void LIST_eisagwgi(tupos_deikti * const lista, TStoixeiouListas stoixeio,
					tupos_deikti prodeiktis, int *error);

void LIST_diagrafi(tupos_deikti * const lista, tupos_deikti *deiktis, int * const error);


/* Epilogh Kombou */

void LIST_epomenos(const tupos_deikti lista, tupos_deikti * const p, int * const error);

void LIST_proigoumenos(const tupos_deikti lista, tupos_deikti * const p, int * const error);

void LIST_first(const tupos_deikti lista, tupos_deikti * const first, int * const error);

void LIST_last(const tupos_deikti lista, tupos_deikti * const last, int * const error);

/*prakseis anazhthshs*/

void LIST_anazitisi(const tupos_deikti lista, TStoixeiouListas stoixeio,
					tupos_deikti *prodeiktis, int *vrethike);

#endif /*#ifndef __CH7_CLPOINTER__ */
