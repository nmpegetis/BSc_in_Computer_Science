/*******************************************************************************
Arxeio ylopoihshs	: TStoixeioyTree.c
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "TStoixeioyTree.h"

//vale, a lo mejor tengo que poner un tambien orisma!
//oi parakatw sunartiseis kalountai apo to dentro wste na taksinomei ta stoixeia tou alfabitika
int TStree_iso (TStoixeioyTree Elem1, TStoixeioyTree Elem2)	//sugkrinei ta stoixeia kai epistrefei 1 an einai isa alliws 0				
{
	return ((strcmp(Elem1.onoma, Elem2.onoma) ==0) && (strcmp(Elem1.epwnumo, Elem2.epwnumo) ==0));	
}

int TStree_mikrotero(TStoixeioyTree Elem1, TStoixeioyTree Elem2)//sugkrinei ta stoixeia kai epistrefei 1 an to prwto einai mikrotero apo to deutero alliws 0
{

	
	if((strcmp(Elem1.epwnumo, Elem2.epwnumo) < 0)) return 1;
	else if((strcmp(Elem1.epwnumo, Elem2.epwnumo) ==0) && (strcmp(Elem1.onoma, Elem2.onoma) <0)) return 1;	
	else return 0;
}

int TStree_megalytero(TStoixeioyTree Elem1, TStoixeioyTree Elem2)//sugkrinei ta stoixeia kai epistrefei 1 an to prwto einai megalutero apo to deutero alliws 0
{
	if((strcmp(Elem1.epwnumo, Elem2.epwnumo) > 0)) return 1;
	else if((strcmp(Elem1.epwnumo, Elem2.epwnumo) ==0) && (strcmp(Elem1.onoma, Elem2.onoma) >0)) return 1;	
	else return 0;
	//return(Elem1 > Elem2);
}

////////////////////////////////////////////////////////////////////////////////

int TStree_mikrotero_iso(TStoixeioyTree Elem1, TStoixeioyTree Elem2)			//vale
{
    return TStree_mikrotero(Elem1,Elem2)||TStree_iso(Elem1,Elem2);
}

int TStree_megalytero_iso(TStoixeioyTree Elem1, TStoixeioyTree Elem2)			//vale
{
    return TStree_megalytero(Elem1,Elem2)||TStree_iso(Elem1,Elem2);
}

int TStree_diaforo(TStoixeioyTree Elem1, TStoixeioyTree Elem2)				//vale
{
    return !TStree_iso(Elem1,Elem2);
}

////////////////////////////////////////////////////////////////////////////////

void TStree_setValues (TStoixeioyTree *target, TStoixeioyTree source)			//vale
{

	strcpy(target->onoma,source.onoma);	//antigrafei to onoma tou source sto onoma tou target
	strcpy(target->epwnumo,source.epwnumo);	//omoiws
}

void TStree_writeValue(TStoixeioyTree Elem)						//vale
{
	static int metritis=1;		//to dilwnw ws static gia na diatirei tin timi tou kai meta tin eksodo apo ti sunartisi
	char filename[20];
	if(metritis <= 10000){		//tin prwti fora den einai metritis==1 giati apla den tou exei dothei kapoia timi opote mpainei mesa sto block tou if
		metritis += 1;
		strcpy( filename,"atoma-random-out.txt");
	}
	else{
		strcpy( filename,"atoma-sorted-out.txt");
	}
	//printf("%s\t%s\n", Elem.epwnumo, Elem.onoma );
	FILE * pFile;
	pFile = fopen (filename, "a");	/*anoigei to arxeio gia grapsimo me epektasi i an den uparxei to dimiourgei. an uparxei idi kati grammeno mesa,den to diagrafei kai bazei ta kainourgia dedomena sto telos...xrisimopoiw to "a" anti gia to "w" gia ti einai polu pio grigoro afou to w kathe fora diagrafei to arxeio an uparxei idi kai etsi kathusterei polu*/
	if (pFile!=NULL){				/*elegxei an anoikse to arxeio*/
		fprintf( pFile, "%s\t%s\n", Elem.epwnumo, Elem.onoma);	/*tupwnei sto arxeio*/
		fclose (pFile);				/*kleinei to arxeio*/
	}
	else perror("upirkse kapoio sfalma sto anoigma tou arxeiou\n");
}



