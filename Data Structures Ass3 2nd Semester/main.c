/*******************************************************************************
Arxeio ylopoihshs	: main.c
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/

#include <stdio.h>		/*standar input-output*/
#include <stdlib.h>		/*gia ti sunartisi apodeusmeusis xwrou apo ti swro---free( )*/
#include "BulkTree.h"		/*gia xrisi olwn twn sunartisewn pou den dilwnontai sto stdio.h, gia to TStoixeioyTree kai gia oles tis sunartiseis pou den dilwnontai se auto to arxeio*/

#define ARR_SIZE 14		/*o arithmos twn grammwn tou pinaka pou dimiourgeitai kata  tin kataskeui*/

int main(int argc, char **argv)
{
	BulkTreePtr   	dentro;		/*dilwsi gia to dentro*/
	TStoixeioyTree 	record;		/*o typos twn stoixeiwn tou dentrou*/
	int 	error =0;		/*akeraios opou se periptwsi lathous entopizei se poio simeio egine to lathos*/
	int 	found;			/*plithos atomwn pou brethikan kata tin anazitisi kai sunolikos xronos pou apaitithike*/
	double	print_timing_random, search_timing_random, print_timing_sorted, search_timing_sorted; /*oi sunolikoi xronoi anazitisis kai ektupwsis apo ta 2 arxeia*/
	static const char arxeio1[] = "atoma-random.txt";
	static const char arxeio2[] = "atoma-sorted.txt";
	int i = 0;			/*gia tis epanalipseis ston pinaka twn ektupwsewn*/
	double *insert_timing_random, *insert_timing_sorted;	/*oi merikoi kai o pliris xronos kataskeuis diabazontas apo to arxeio atoma-random.txt kai atoma-sorted.txt antistoixa*/
	
	printf("\nmaziki diaxeirisi atomwn me DDA diabazontas ta onomata apo to atoma-random.txt\n\n\n");
	
	BulkTree_dimiourgia(&dentro);					/*desmeusi xwrou sto heap kai dimiourgia enos dentrou(keno) megethous NULL*/
	insert_timing_random = BulkTree_kataskeui( &dentro, &error, &record, arxeio1 );//kataskeuazei ena dentro apo to arxeio onomatwn atoma-random.txt kai ektupwnei tous xronous merikis kai plirous kataskeuis
	print_timing_random = BulkTree_ektupwsh(dentro);		//ektupwnei alfabitika ta onomata se arxeio atoma-random-out.txt kai to xrono pou apaitithike
	search_timing_random = BulkTree_Anazitisi(dentro, &record);	//anazita sto dentro ta atoma apo to arxeio atoma-search.txt kai epistrefei to sunoliko xrono anazitisis
	BulkTree_katastrofi(&dentro);					/*katastrofi dentrou*/
	

	
	printf("\n\n\nmaziki diaxeirisi atomwn me DDA diabazontas ta onomata apo to atoma-sorted.txt\n\n\n");
	
	BulkTree_dimiourgia(&dentro);					/*desmeusi xwrou sto heap kai dimiourgia enos dentrou(keno) megethous NULL*/
	insert_timing_sorted = BulkTree_kataskeui( &dentro, &error, &record, arxeio2 );//kataskeuazei ena dentro apo to arxeio onomatwn atoma-random.txt kai ektupwnei tous xronous merikis kai plirous kataskeuis
	print_timing_sorted = BulkTree_ektupwsh(dentro);		//ektupwnei alfabitika ta onomata se arxeio atoma-random-out.txt kai to xrono pou apaitithike
	search_timing_sorted = BulkTree_Anazitisi(dentro, &record);	//anazita sto dentro ta atoma apo to arxeio atoma-search.txt kai epistrefei to sunoliko xrono anazitisis
	BulkTree_katastrofi(&dentro);					/*katastrofi dentrou*/

	
 	fprintf(stdout, "\n\nRANDOM INPUT\t\t\t\t\t|\tSORTED INPUT\t\n\n");
	for (i; i < ARR_SIZE-1; ++i)
		fprintf(stdout, "insert_timing_random 2^%d =\t%f msec\t|\tinsert_timing_sorted 2^%d =\t%f msec\n", i+1, insert_timing_random[i], i+1, insert_timing_sorted[i]);
 	fprintf(stdout, "insert_timing_random total =\t%f msec\t|\tinsert_timing_sorted total =\t%f msec\n", insert_timing_random[ARR_SIZE-1], insert_timing_sorted[ARR_SIZE-1]);
 	fprintf(stdout, "print_timing_random =\t\t%f msec\t|\tprint_timing_sorted =\t\t%f msec\n", print_timing_random, print_timing_sorted);
 	fprintf(stdout, "search_timing_random =\t\t%f msec\t|\tsearch_timing_sorted =\t\t%f msec\n", search_timing_random, search_timing_sorted);
 	
 /*gia ektupwsi twn xronwn kai se arxeio*/
 	FILE * pFile;
	pFile = fopen ("pinakas-xronometrisewn.txt", "a");	/*anoigei to arxeio gia epektasi. an uparxei idi kati grammeno mesa, den to diagrafei kai bazei ta kainourgia dedomena sto telos*/
	if (pFile!=NULL){				/*elegxei an anoikse to arxeio*/
		fprintf(pFile, "\n\nRANDOM INPUT\t\t\t\t\t|\tSORTED INPUT\t\n\n");
		for (i=0; i < ARR_SIZE-1; ++i)
			fprintf(pFile, "insert_timing_random 2^%d =\t%f msec\t|\tinsert_timing_sorted 2^%d =\t%f msec\n", i+1, insert_timing_random[i], i+1, insert_timing_sorted[i]);
	 	fprintf(pFile, "insert_timing_random total =\t%f msec\t|\tinsert_timing_sorted total =\t%f msec\n", insert_timing_random[ARR_SIZE-1], insert_timing_sorted[ARR_SIZE-1]);
	 	fprintf(pFile, "print_timing_random =\t\t%f msec\t|\tprint_timing_sorted =\t\t%f msec\n", print_timing_random, print_timing_sorted);
	 	fprintf(pFile, "search_timing_random =\t\t%f msec\t|\tsearch_timing_sorted =\t\t%f msec\n", search_timing_random, search_timing_sorted);	/*tupwnei sto arxeio*/
		fclose (pFile);				/*kleinei to arxeio*/
	}
	else perror("upirkse kapoio sfalma sto anoigma tou arxeiou\n");
 	
 	free(insert_timing_random);		//eleutherwsi tou xwrou pou desmeutike gia ton pinaka sti swro
	free(insert_timing_sorted);		//omoiws
	
	getchar();		//gia t windows..dev-c++
	return 0;
}




