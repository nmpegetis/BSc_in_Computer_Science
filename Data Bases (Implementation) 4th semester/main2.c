#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "BF.h"
#include "Sorted.h"

#define NAMES_SIZE 12
#define SURNAMES_SIZE 11

const char* shuffled = "shuffled";
const char* ids = "ids_srt";
const char* name = "names_srt";
const char* surname = "surnames_srt";
const char* points = "points_srt";
const char* a = "a";
const char* b = "b";

Record randomRecord();

int curname = 0;
char *names[] = {"AUANASIA", "DIMITRIS", "ELENH", "GIWRGOS", "JERRY", "MARINA", "NANCY",
		"PANOS", "PETROS", "TOM", "VASSILIS", "YANNIS"};

char *surnames[] = {"PANAGIWTOU", "ASHMOGLOU", "ARAVANTHS", "PAPAPETROU", "LAMBROU", "THEOLOGOU",
		"ZERBA", "LEE-LEWIS", "SPANOU", "ZIGKOLHS", "TZIOKOU"};

int main( int argc, char* argv[] ){

	int i, j;
	int blkno = 0;
	int fdtmp1, fdtmp2;
	int sorted, merged;
	int blkcount = 0;
	void *frstBlk, *lastBlk;

	srand( time(NULL) );

	BF_Init();

	if ( Sorted_CreateFile("tmp2") < 0 ){
		BF_PrintError("Error creating file tmp2");
		return -1;
	}

	if ( (fdtmp1 = Sorted_OpenFile("tmp2")) < 0 ){
		BF_PrintError("Error opening file tmp2");
		return -1;
	}

	blkno = 0;
	if ( BF_AllocateBlock( fdtmp1 ) < 0 ){
		BF_CloseFile(fdtmp1);
		BF_PrintError("Error allocating first block for file tmp2");
		return -1;
	}

	i = 0;
	while ( i < NAMES_SIZE ){

		Record r = randomRecord();

		if ( BF_AllocateBlock( fdtmp1 ) < 0 ){
			BF_CloseFile(fdtmp1);
			BF_PrintError("Error allocating a block for file tmp2");
			return -1;
		}

		Sorted_InsertFirstEntry(fdtmp1, r);

		j = i + 1;
		BF_ReadBlock( fdtmp1, j, &lastBlk );
		BF_ReadBlock( fdtmp1, blkno, &frstBlk );
		memcpy( lastBlk, frstBlk, BLOCK_SIZE );

		if ( BF_WriteBlock( fdtmp1, j ) < 0 ) {
			BF_CloseFile(fdtmp1);
			BF_PrintError("Error writing block back to disk");
			return -1;
		}

		i++;
	}

	/* empty the first block */
	BF_ReadBlock( fdtmp1, blkno, &frstBlk );
	memset(frstBlk, 0, BLOCK_SIZE);
	if ( BF_WriteBlock( fdtmp1, blkno ) < 0 ) {
		BF_CloseFile(fdtmp1);
		BF_PrintError("Error writing block back to disk");
		return -1;
	}


	/* Print everything that exists in the tmp2 file */
	printf("Printing everything in tmp2\n");
	Sorted_GetAllEntries(fdtmp1, NULL, NULL);

	if ( BF_CloseFile(fdtmp1) < 0 ){
		BF_PrintError("Error writing block back to disk");
		return -1;
	}
	printf("\n\n");

	sorted = Sorted_checkSortedFile( "tmp2", 0 );

	/* check if tmp1 file exists */
	if ( (fdtmp2 = Sorted_OpenFile("tmp1") ) < 0 ){
		BF_PrintError("Error opening tmp1. Did you remember to run main1 before?");
		return -1;
	}

	/* Close the file */
	Sorted_CloseFile(fdtmp2);


	/* Merge the two files, tmp1 and tmp2, based on id */
	printf("Now merging files tmp1 and tmp2 for id: \n");
	merged = Sorted_mergeFiles("tmp1", "tmp2", 0);

	if ( sorted && (merged == 0) ){
		printf("1st merging succeeded correctly!");
	}else if ( sorted && (merged != 0) ){
		printf("1st merging failed when it should have succeeded!");
	}else if ( (merged == 0) && !sorted ){
		printf("1st merging succeeded when it should have failed!");
	}else{
		printf("1st merging failed as it should have!! Nice!");
	}
	printf("\n\n");

	/* Merge the two files, tmp1 and tmp2, based on name */
	printf("Now merging files tmp1 and tmp2 for name: \n");
	if ( Sorted_mergeFiles("tmp1", "tmp2", 1) < 0 ){
		BF_PrintError("Files tmp1 and tmp2 were not merged. This should have succeeded!");
	}else{
		printf("Merge succeeded correctly!");
	}
	printf("\n\n");

	if ( (fdtmp1 = Sorted_OpenFile("tmp1tmp21")) < 0 ){
		BF_PrintError("Can not open the file tmp1tmp21");
		return -1;
	}

	printf("PRINT EVERYTHING in tmp1tmp21\n");
	Sorted_GetAllEntries( fdtmp1, NULL, NULL);
	printf("\n");
	printf("There should be %d records \n\n\n", (NAMES_SIZE + 1));

	printf("Searching for JERRY in tmp1tmp21 file\n");
	Sorted_GetAllEntries( fdtmp1, "name", "JERRY" );
	printf("\n\n");

	if ( Sorted_CreateFile("new") < 0 ){
		return -1;
	}

	if ( (fdtmp2 = Sorted_OpenFile("new")) < 0){
		BF_PrintError("Can not open the new file");
		Sorted_CloseFile(fdtmp1);
		return -1;
	}

	blkcount = BF_GetBlockCounter( fdtmp1 );
	for ( i = 0; i < blkcount; i++ ){

		BF_AllocateBlock(fdtmp2);

		BF_ReadBlock( fdtmp1, i, &frstBlk );
		BF_ReadBlock( fdtmp2, i, &lastBlk );

		memcpy( lastBlk, frstBlk, BLOCK_SIZE );
		BF_WriteBlock(fdtmp2, i);
	}

	if ( Sorted_CloseFile(fdtmp2) < 0 ){
		BF_PrintError("Can not close the new file");
		return -1;
	}

	fdtmp2 = Sorted_OpenFile((char*)name);
	if ( fdtmp2 < 0 ){
		BF_PrintError("Can not open the file names_srt");
		Sorted_CloseFile(fdtmp2);
		return -1;
	}

	printf("PRINT EVERYTHING in names_srt\n");
	Sorted_GetAllEntries( fdtmp2, NULL, NULL);
	printf("\n\n");

	BF_CloseFile(fdtmp2);

	/* Check if file name is sorted correctly */
	sorted = Sorted_checkSortedFile(name, 1);
	if ( sorted == 1 ){
		printf("file names_srt is correctly sorted!");
	}else{
		printf("file is not correctly sorted!");
	}
	printf("\n\n");

	merged = Sorted_mergeFiles("new", (char*)name, 1);
	if ( merged < 0 ){
		BF_PrintError("The two files were not merged!");
		return -1;
	}

	fdtmp2 = Sorted_OpenFile("newnames_srt1");

	printf("Searching for DIMITRIS in newnames_srt1 file\n");
	Sorted_GetAllEntries( fdtmp2, "name", "DIMITRIS" );
	printf("\n\n");

	if ( Sorted_CloseFile(fdtmp2) < 0 ){
		BF_PrintError("Can not close the new file");
		return -1;
	}

	return 0;
}


Record randomRecord(){

	Record rec;
	int idx;

	rec.id = rand() % 1000 + 800;
	strcpy( rec.name, names[curname++] );
	idx = drand48() * SURNAMES_SIZE;
	strcpy( rec.surname, surnames[idx] );
	rec.avgPoints = drand48();

	return rec;
}
