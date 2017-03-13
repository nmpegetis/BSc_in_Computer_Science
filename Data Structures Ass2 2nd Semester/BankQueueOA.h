/*******************************************************************************
Arxeio ylopoihshs	: BankQueueOA.h
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#ifndef __CH2_QARRAY__ 
#define __CH2_QARRAY__
#include "TStoixeiouListas.h"	/*gia na perilambanei to TStoixeiouListas, tin TSListasPrintValue kai tin TSListasSetValue*/

/*dilwseis tupwn */

#define PLITHOS 1000		/*to plithos twn pelatwn pou mporei na xwrane se mia trapeza*/

typedef struct QueueStruct *BankOurasPtr;

int pelates_se_anamoni;		/*oi sunolikoi pelates pou perimenouns stin anamoni...+ ta AMEA*/
unsigned int 	xronos;			/*roloi,lepta*/
	int		thesi;			/*i pragmatiki thesi twn pelatwn*/


//******************na koitaksw mipws mporw na metaferw kapoia pragmata sto .c


/*dilwseis sunartisewn*/

/*dimiourgia - katastrofi*/  
BankOurasPtr BankOura_dimiourgia();
void BankOura_katastrofi(BankOurasPtr *oura);

/*prakseis elegxou*/
int BankOura_keni(BankOurasPtr oura);	/*elegxei an i oura einai keni*/

/*prakseis prosthesis,apomakrunsis,megethous ouras*/
void BankOura_prosthesi(BankOurasPtr *oura, TStoixeiouOuras stoixeio, int *uperxeilisi);	/*prosthetei to stoixeio stin oura*/
void BankOura_apomakrunsh(BankOurasPtr *oura, TStoixeiouOuras *stoixeio, int *upoxeilisi);	//** ebala * sto oura /*afairei to stoixeio apo tin oura*/
int BankOura_megethos(BankOurasPtr oura);
//void SizeOuras(TOuras oura, int *size);			/*elegxei to megethos tis ouras kathe stigmi*/

void BankOura_apoxwrhsh(BankOurasPtr oura, float pithanothta);
void BankOura_UpdateThesi(BankOurasPtr oura, int ShiftThesi);

void inspectQbyOrder (BankOurasPtr oura);	/*emfanizei tin oura opws diamorfwnetai se kathe stigmi*/

#endif /*#ifndef __CH2_QARRAY__ */
















