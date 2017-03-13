/*******************************************************************************
Arxeio ylopoihshs	: BulkTree.h
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#ifndef __BulkTree__
#define __BulkTree__
#include "TStoixeioyTree.h"	/*gia na perilambanei to TStoixeioyTree, tin TSListasPrintValue kai tin TSListasSetValue*/

/*dilwseis tupwn */

typedef struct BulkTreeRec *BulkTreePtr;

/*dilwseis sunartisewn*/
/*dimiourgia*/  
void BulkTree_dimiourgia(BulkTreePtr *BulkTree);				//vale
/*katastrofi*/
void BulkTree_katastrofi(BulkTreePtr *BulkTree);				//vale
/*kataskeuh*/
double* BulkTree_kataskeui(BulkTreePtr *BulkTree,int *error,TStoixeioyTree *stoixeio, const char *arxeio);	//vale
/*anazitisi*/
double BulkTree_Anazitisi(BulkTreePtr BulkTree,TStoixeioyTree *stoixeio);	//vale
/*ektupwseis*/
double BulkTree_ektupwsh(BulkTreePtr BulkTree);					//vale


#endif /*#ifndef __BulkTree__ */
