/*******************************************************************************
Arxeio ylopoihshs	: BulkTreeAVL.c
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>               	/* gia to gettimeofday() kai to timeval */
#include <string.h>
#include <math.h>			//gia ti sunartisi power...episis ston compiler prepei na baloume to epithema -lm
#include "BulkTree.h"
#include "ch8_AVLpointer.h"


#define ARR_SIZE 14 


/*dilwsi tupou mesa sto .c gia OA*/


typedef struct BulkTreeRec{
	typos_deikti TreeRoot;
}BulkTreeRec;	   /*o typos tou dentrou*/			//isws to BulkTreeRec sto telos na mi xreiazetai

struct typos_komvou{
	TStoixeioyTree dedomena;
	typos_deikti apaidi;
	typos_deikti dpaidi;
} typos_komvou;



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void episkepsi(typos_deikti);						//cabrota
void endodiataksi(typos_deikti);					//taksinomimena
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



/*ulopoiisi sunartisewn pou dilwthikan sto header file*/
/*dimiourgia*/  
void BulkTree_dimiourgia(BulkTreePtr *BulkTree)							//vale
{
	*BulkTree= malloc(sizeof(BulkTreeRec));		//desmeusi xwrou sto heap gia to dentro
	AVLTree_dimiourgia(&(*BulkTree)->TreeRoot);		//(*BulkTree)->TreeRoot = NULL
	printf("Dimiourgithike ena AVL dentro!\n");
}


void BulkTree_katastrofi(BulkTreePtr *BulkTree)							//vale
{
	AVLTree_katastrofi(&(*BulkTree)->TreeRoot);
	free(*BulkTree);
	*BulkTree = NULL;
	printf("To AVL dentro katastrafike! O xwros apodesmeutike!\n");
}


/*kataskeuh*/
double* BulkTree_kataskeui(BulkTreePtr *BulkTree,int *error,TStoixeioyTree *stoixeio, const char *arxeio )
{//diabazei atoma apo to arxeio onomatwn "atoma-random.txt" kai ta eisagei sto dentro. Episis epistefei ton pinaka me tous xronous eisagwgis twn atomwn

	double *ar = (double*)malloc(ARR_SIZE * sizeof(double));	//desmeusi pinaka double me ARR_SIZE megethos tupou double
	int metritis =0;			//metraei tis grammes mesa sto arxeio
	int power =1;				//oi dunameis pou tha mas xreiastoun kata tis sugkriseis
	char filename[20];
	int ypsilotero;			
	strcpy( filename,arxeio);		

	FILE * pFile;
	pFile = fopen (filename,"r");			//anoigei to arxeio gia diabasma mono
	if (pFile!=NULL){				//an uparxei to pfile
		
		struct timeval t1, t2;			//2 domes oi 't1' kai 't2' metonomasmenes apo tin timeval
		double elapsedTime;
		
		gettimeofday(&t1, NULL);		/*ksekinaei o xronos... Resolution in Milli-Seconds. NOT THOUROUGHLY TESTED */
		
		 while (!feof(pFile)){			//oso den exoume ftasei sto telos tou arxeiou
			metritis++;			//metritis grammis stin opoia briskomaste
			fscanf( pFile, "%s\t%s\n", stoixeio->epwnumo, stoixeio->onoma);//diabazei kai ekxwrei sto stoixeio ta 2 strings pou briskontai stin kathe grammi.
			AVLTree_eisagogi(&(*BulkTree)->TreeRoot, *stoixeio,&ypsilotero, error);	//kanei tin eisagwgi tou stoixeiou sto dentro
			if(metritis == pow(2, power)){		//pow sunartisi gia tin euresi dunamis...perilambanetai stin kefalida math.h
				//printf("\nmpike tin %d fora stin %d dunami\n",metritis,power);	//gia na doume an leitourgei swsta i sunthiki
				gettimeofday(&t2, NULL);	/*stamataei o xronos - ousiastika pairnei ena deigma apo to xrono pou kulaei*/
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
				elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
				ar[power-1] = elapsedTime;		//bale to xrono eisagwgis tou 2^power atomou ston pinaka
				power++;		
				//gettimeofday(&t1, NULL);/*ksanamidenizoume to roloi stin periptwsi pou theloume na metrisoume anamesa stis xronikes stigmes posos xronos pernaei		
				/*printf("elapsedTime=%g msec\n", elapsedTime);*/
			}
		}
		gettimeofday(&t2, NULL);			/*stamataei o xronos molis ftasoume sto telos tou arxeiou*/
		elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
		elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
		ar[power-1] = elapsedTime;			//bale to xrono eisagwgis tou teleutaiou atomou ston pinaka
		
		fclose (pFile);				//kleise to arxeio
		printf("Eisixthisan sto dentro ta onomata apo to arxeio %s! H Kataskeui oloklirwthike!\n",filename);
	}
	else perror("upirkse kapoio sfalma sto anoigma tou arxeiou\n");

	return ar;			//epistefei ton pinaka me tous xronous	
}

/*anazitisi*/
double BulkTree_Anazitisi(BulkTreePtr BulkTree,TStoixeioyTree *stoixeio)
{//diabazei ta atoma apo to arxeio atoma-search.txt kai ta anazitaei diadoxika sto dentro.Epistrefei to plithos twn atomwn pou brethikan kai to sunoliko xrono pou apaitithike.
	
	typos_deikti current;			//prosorini metabliti
	int plithos =0;				//to plithos twn atomwn pou brethikan
	struct timeval t1, t2;			//2 domes oi 't1' kai 't2' metonomasmenes apo tin timeval
	double elapsedTime;
	gettimeofday(&t1, NULL);		/*ksekinaei o xronos... Resolution in Milli-Seconds. NOT THOUROUGHLY TESTED */
	int found =0;
	
	current =NULL;

	FILE * pFile;
	pFile = fopen ("atoma-search.txt","r");		//anoigei to arxeio gia diabasma mono
	if (pFile!=NULL){				//an uparxei to pfile
		 while (!feof(pFile)){			//oso den exoume ftasei sto telos tou arxeiou
			fscanf( pFile, "%s\t%s\n", stoixeio->epwnumo, stoixeio->onoma);//diabazei kai ekxwrei sto stoixeio ta 2 strings pou briskontai stin kathe grammi.
			AVLTree_anazitisi(BulkTree->TreeRoot, *stoixeio, &current, &found);//epeita pairnei to stoixeio kai to anazitaei sto dentro
			if(found){			//an brethike
				plithos++;
				printf("\nTo stoixeio bre8hke!\n");
			}
			else	printf("\nTo stoixeio DEN bre8hke!\n");
		}
		fclose (pFile);				//kleise to arxeio
	}
	else perror("upirkse kapoio sfalma sto anoigma tou arxeiou\n");

	gettimeofday(&t2, NULL);			/*stamataei o xronos molis ftasoume sto telos tou arxeiou*/
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
	
	printf("H Anazitisi oloklirwthike!\n");
	printf("To plithos twn atomwn pou brethikan einai\t%d !\n", plithos);
	
	return elapsedTime;				//epestrepse to sunoliko xrono olwn twn anazitisewn
}

/*ektupwseis*/
double BulkTree_ektupwsh(BulkTreePtr BulkTree)
{	/*diatrexei to dentro kai ektupwnei ta atoma me alfabitiki seira se arxeio atoma-random-out.txt.episis epistefei to sunoliko xrono pou apaitithike*/

	struct timeval t1, t2;			//2 domes oi 't1' kai 't2' metonomasmenes apo tin timeval
	double elapsedTime;
	gettimeofday(&t1, NULL);		/*ksekinaei o xronos gia tin edodiataksi kai ektupwsi... Resolution in Milli-Seconds. NOT THOUROUGHLY TESTED */

	endodiataksi(BulkTree->TreeRoot);		//i endodiataksi diatasei taksinomimena ta onomata kai ta ektupwnei sto arxeio atoma-random-out.txt

	gettimeofday(&t2, NULL);		/*stamataei o xronos*/
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
	
	printf("Ta onomata ektupwthikan sto arxeio ! H Ektupwsi oloklirwthike!\n");
	
	return elapsedTime;			/*epistrefei to sunoliko xrono pou apaitithike*/	
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void episkepsi(typos_deikti tree)
{
	TStoixeioyTree x;
	AVLTree_periexomeno(tree, &x);	//kalei tin TStree_setValue
	TStree_writeValue(x);
	printf("\n");
}

void endodiataksi(typos_deikti tree)		//taksinomimena
{
	typos_deikti paidi;
	int error;
	error=0;
	if(!AVLTree_keno(tree))
	{
		AVLTree_apaidi(tree, &paidi, &error);
		endodiataksi(paidi);
		episkepsi(tree);
		AVLTree_dpaidi(tree, &paidi, &error);
		endodiataksi(paidi);
	}
}

