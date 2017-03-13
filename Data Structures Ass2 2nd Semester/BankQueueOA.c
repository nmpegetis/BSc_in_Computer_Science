/*******************************************************************************
Arxeio ylopoihshs	: BankQueueOA.c
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "BankQueueOA.h"
#include "prakseisListPointers.h"

/*dilwseis tupwn mesa sto .c gia OA*/

typedef struct QueueStruct{
	tupos_deikti embros;		/*thesi tou prwtou stoixeiou tis ouras*/
	tupos_deikti piso;		/*thesi tou teleutaiou stoixeiou tis ouras*/
	int megethos;       		/* megethos ouras */
//	TStoixeiouListas pinakas[PLITHOS];	/*o pinakas twn stoixeiwn twn pelatwn megethous PLITHOS*/	//******mporei auto na prepei na  to antikatastisw me to apo katw
} QueueStruct;	   /*o tupos ths ouras*/

struct tupos_komvou{
	TStoixeiouListas dedomena;	/*ta dedomena*/		//**********edw na dw ti paizei....pou mou xrisimeuei
	tupos_deikti    epomenos; 	/*deikths sto epomeno dedomeno*/
};


/*ulopoiisi sunartisewn pou dilwthikan sto header file*/


/*dimiourgia*/
BankOurasPtr BankOura_dimiourgia()	/*dimiourgia listas megethous 0 pou den exei oute epomeno oute proigoumeno*/
{
	BankOurasPtr ThisQueue = malloc( sizeof(QueueStruct));		/*desmeusi xwrou apo ti swro megethous QueueStruct gia ti dimiourgia tis ouras*/
	LIST_dimiourgia(&ThisQueue->embros);			/*o deiktis tis arxis tis listas pros to epomeno dedomeno deixnei se NULL,ara den exei epomeno stoixeio*/
	ThisQueue->piso = ThisQueue->embros;	/*oute kai proigoumeno*/
	ThisQueue->megethos = 0;		/*to megethos tis ouras-listas einai 0*/
	printf("Dimiourgithike mia oura trapezhs!\n");
	return ThisQueue;
}

/*katastrofi*/
void BankOura_katastrofi(BankOurasPtr *oura)
{/*
 *	Pro: 		Dhmiourgia BankQueue
 *	Meta:		Katastrofh (free) olhs ths ouras
*/
	LIST_katastrofi(&(*oura)->embros);
	free(*oura);
	*oura = NULL;
	printf("H oura katastrafike! O xwros apodesmeutike!\n");
}

/*keni*/
int BankOura_keni(BankOurasPtr oura)
{/*Epistrefei 1 an h BankQueue einai kenh, diaforetika 0*/
	return LIST_keni(oura->embros);	//epistrefei auto pou epistrefei i LIST_keni...ousiastika an i oura einai NULL
}


int BankOura_megethos(BankOurasPtr oura)
{/*
  * Pro  		Dhmiourgia BankQueue
  * Meta        epistrefei ton mhkos ths listas
*/
		//printf("to megethos tis kanonikis ouras twn pelatwn auti ti xroniki stigmi einai: %d \n",oura->megethos);		
		return oura->megethos;
}


void BankOura_prosthesi(BankOurasPtr *oura, TStoixeiouOuras stoixeio, int *uperxeilisi)
{/*An exei xwro, BankQueue exei epauksh8ei me to stoixeio.uperxeilisi == 0 an to stoixeio eishx9ei, alliws 1*/
	int error =0;												//********na tsekarw katra posos sumpiptoun to error me tin uperxeilisi
	LIST_eisagwgi( &((*oura)->embros), stoixeio, (*oura)->piso, uperxeilisi );
	LIST_last( (*oura)->embros, &((*oura)->piso), &error );
	if( error !=1 ) (*oura)->megethos++;		/*auksanei o metritis afou prostethike ena stoixeio*/


/**************************tupwnontai sto Customer.txt ta stoixeia pou upothetika anagrafontai sto xartaki proteraiotitas[erwtima 4.i.b askisis 1]****************************/
	FILE * pFile;
	pFile = fopen ("Customer.txt","a");	/*anoigei to arxeio gia grapsimo me prosartisi sto telos twn newn dedomenwn, an uparxei idi kati grammeno mesa, xwris na diagrafei ta proigoumena dedomena*/
	if (pFile!=NULL){	/*elegxei an anoikse to arxeio*/
		fprintf( pFile, "{ lepto eisodou=|%d|\taukswn arithmos pelati=|%d|\tpelates se anamoni =|%d|\tproblepsi xronou anamonis=|%d|\tthesi pelati=|%d| }\n", stoixeio.lepto_eisodou, stoixeio.auksontas_ar_pelati, pelates_se_anamoni, stoixeio.problepsi, stoixeio.thesi );	/*tupwnei sto arxeio*/
		fclose (pFile);		/*kleinei to arxeio*/
	}
	else printf("upirkse kapoio sfalma sto anoigma tou arxeiou\n");
}


void BankOura_apomakrunsh(BankOurasPtr *oura, TStoixeiouOuras *stoixeio, int *upoxeilisi)	//den ebala * sto oura
{/*An uparxei stoixeio, BankQueue exei meiw8ei kata ena stoixeio.upoxeilisi == 0 an to stoixeio apomakrun8hke,alliws 1*/

	tupos_deikti temp;
	int error =0;
	if( BankOura_keni(*oura)) *upoxeilisi =1;
	else{
		*upoxeilisi =0;
		LIST_periexomeno( (*oura)->embros, stoixeio);		//epistrefei sto 'stoixeio' ta dedomena sta opoia deixnei o '(*oura)->embros'
		if( (*oura)->embros == (*oura)->piso ){			//an einai to prwto stoixeio
			temp =(*oura)->embros;
			LIST_diagrafi( &((*oura)->embros), &temp, upoxeilisi );	//diagrafei to stoixeio
			(*oura)->embros = (*oura)->piso = NULL;			//diagrafei to deikti pou edeixne to stoixeio
		}
		else{						//an den einai to prwto stoixeio
			temp = (*oura)->embros;
			LIST_diagrafi ( &((*oura)->embros ), &temp, upoxeilisi );
		}
		if( *upoxeilisi != 1 ){
			(*oura)->megethos--;		/*meiwnetai to megethos tis ouras afou afairethike ena stoixeio*/
//			BankOura_UpdateThesi(oura, -1);	/*enimervnei ti */
		}
		
/**************************tupwnontai sto Statistics.txt ta stoixeia tou pelati pou molis eksupiretithike[erwtima 4.ii askisis 1]****************************/
		FILE * pFile;
		pFile = fopen ("Statistics.txt","a");
		if (pFile!=NULL){
			fprintf( pFile, "{ lepto eisodou=|%d|\taukswn arithmos pelati=|%d|\tproblepsi xronou anamonis=|%d|\tpragmatikos xronos anamonis =|%d|\tthesi pelati=|%d| }\n", stoixeio->lepto_eisodou, stoixeio->auksontas_ar_pelati, stoixeio->problepsi, xronos-stoixeio->lepto_eisodou, stoixeio->thesi );	
			fclose (pFile);
		}
		else printf("upirkse kapoio sfalma sto anoigma tou arxeiou\n");
	}
}



/*********************** PROSOXH *************************************************
 Oi 2 proxeis pou akolou8oun aforoun mono thn Oura Trapezas kai
    mporoun na dokimastoun mono me ton Tupos Stoixeiou pou perilambanei thn 8esh.
********************************************************************************** */
 
void BankOura_apoxwrhsh(BankOurasPtr oura, float pithanothta)
{/* Pro: Dhmiourgia BankQueue * Meta: Diatrexei thn lista kai diapistvnei tuxaia an o trexon komvos prepei na diagrafei. An enas komvos diagrafei sunexizei thn diadromh kai meiwnei thn 9esh tvn upoloipvn kata 1.*/


//an aposxoliasw ta printf fainetai oti douleuei kala...

	tupos_deikti temp;
	temp=oura->embros;	///********isws xreizetai na balw dieuthunseis '&' gia na exw prosbasi sto oura->embros
	int megethos = oura->megethos;
	//if(LIST_keni(temp)) return;		/*den xreiazetai..elegxetai sti main*/
	int apoxwrisi =0;
		
	while( megethos>0 && apoxwrisi == 0){
		if(megethos !=1 ){
			int random = rand()%100;	//auti i random einai proswrini gia KATHE pelati...se kathe epanalipsi allazei timi se antithesi me tin 'pithanothta'...oso pio megali einai i 'pithanothta' toso pio pithano einai na kseperasei tin random stis prwtes epanalipseis pou tha ginoun...oso pio mikri einai i 'pithanothta' toso pio pithano einai na kseperasei tin 'random' stis teleutaies epanalipseis...
			if( pithanothta > random ){
				int upoxeilisi =0;
//				printf("\n\n\n\n\n%d\n",oura->megethos);
				BankOura_apomakrunsh(&oura, &temp->dedomena, &upoxeilisi);	/*tote pigainei sto tameio kai i oura meiwnetai kata mia thesi*/
				if( upoxeilisi != 1 ) {

	//				while(!LIST_keni(temp)){
	//					temp->dedomena.thesi -= 1;
	//					temp = temp->epomenos;
	//				}
	//sti main kanw...if(!upoxeilisi)...kai to apo katw
	//tin oura pou kanei update tin allzei olokliri i ti misi opws diladi theloume??
					BankOura_UpdateThesi(oura, -1);	//afora mono tin kanoniki oura twn pelatwn	
					apoxwrisi =1;
				}
//to allaksa simera				apoxwrisi =1;	
				temp=temp->epomenos;
			}
			megethos--;
//to allaksa simera			temp=temp->epomenos;
//			printf("to megethos den einai 1 einai %d \n\n",megethos);
		}
		else{
			int upoxeilisi =0;
//			printf("\n\n\n\n\n%d\n",oura->megethos);
			BankOura_apomakrunsh(&oura, &temp->dedomena, &upoxeilisi);	/*tote pigainei sto tameio kai i oura meiwnetai kata mia thesi*/
			if( upoxeilisi != 1 ) {
//			UpdateTheis....mallon prepei na mpei edw mesa....
//ta apo katw 2 ta allaksa simera
				BankOura_UpdateThesi(oura, -1);	//afora mono tin kanoniki oura twn pelatwn	
				apoxwrisi =1;
			}
//ta allaksa simera			apoxwrisi =1;	
//			printf("mpike mesa %d \n\n\n\n\n\n\n\n\n",oura->megethos);
		}
	}
}

void BankOura_UpdateThesi(BankOurasPtr oura, int ShiftThesi)	//afora mono tin kanoniki oura twn pelatwn
{/*
 *	Pro: 		Dhmiourgia BankQueue
 *	Meta: 		Diatrexei thn lista gia ka8e pelath allazei thn8esh kata ShiftThesi (== +1 h -1)
*/
//na mpei opou uparxei eisodos i eksodos pelati

//an mpei amea(+1) tote OLOI oi pelates stin oura tha pane mia thesi meta...
//an ginei apoxwrisi(-1) tote oi pelates pou tha pane mia thesi aristera tha einai MONO osoi epontai tou pelati pou apoxwrise///????....

//an ginei apoxwrisi amea tote oi pelates tha pane oloi -1 thesi

//profanws afou proigountai ta amea den xreiazetai na ginetai update i thesi tous update tha ginetai mono i thesi olwn twn upoloipwn pelatwn kanontas shift kata 1 thesi deksia...episis meta na elegkw kata poso o problepomenos xronos den einai isos me ton teliko pragmatiko xrono

	tupos_deikti temp;
	temp=oura->embros;
	
	while(!LIST_keni(temp))
	{
		temp->dedomena.thesi += ShiftThesi;
		temp = temp->epomenos;
	}
}


void inspectQbyOrder (BankOurasPtr oura)	/*ektupwnei ta stoixeia tis ouras me ti seira*/
{
	int error=0;
	LIST_diadromi(oura->embros, &error);
	if(error) printf("H oura einai adeia!");
	printf("\n");
}


