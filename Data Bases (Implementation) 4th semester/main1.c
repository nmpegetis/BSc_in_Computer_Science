#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BF.h"
#include "Sorted.h"

const char* shuffled = "shuffled";
const char* ids = "ids_srt";
const char* name = "names_srt";
const char* surname = "surnames_srt";
const char* points = "points_srt";
const char* a = "a"; // a is part of shuffled, sorted by name
const char* b = "b"; // b is part of shuffled, sorted by surname


int main( int argc, char* argv[] ){

	int fda, fdb, fdid, fdtmp;
	Record rec;

	BF_Init();

	fda = Sorted_OpenFile((char*)a);
	if ( fda < 0 ){
		BF_PrintError("File \"a\" could not be opened");
		return -1;
	}

	/* Doing a simple scan on "a" file */
	printf("Printing everything from file \"a\":\n");
	Sorted_GetAllEntries(fda, NULL, NULL );

	fdb = Sorted_OpenFile((char*)b);
	if ( fdb < 0 ){
		Sorted_CloseFile( fda );
		BF_PrintError("File \"b\" could not be opened");
		return -1;
	}

	printf("\n\n");

	/* Searching for PAPADOPOULOS */
	printf("Searching with name=\"PAPADOPOULOS\" in \"b\"\n");
	Sorted_GetAllEntries(fdb, "name", "PAPADOPOULOS");

	/* Open the ids file */
	fdid = Sorted_OpenFile((char*)ids);

	/* Close file "a" */
	if ( Sorted_CloseFile(fda) < 0 ){
		Sorted_CloseFile( fdb );
		Sorted_CloseFile( fdid );

		BF_PrintError("Error closing file \"a\"");
		return -1;
	}

	printf("\n\n");

	/* Searching again for PAPADOPOULOS */
	printf("Searching with nane=\"PAPADOPOULOS\" in \"b\"\n");
	Sorted_GetAllEntries(fdb, "nane", "PAPADOPOULOS");

	printf("\n\n");

	/* Print file "id". This should be printing everything */
	printf("Printing everything from file \"id\"\n");
	Sorted_GetAllEntries(fdid, "name", NULL);

	printf("\n\n");

	/* Finally.. PAPADOPOULOS */
	if ( (fdtmp = Sorted_OpenFile( (char*)surname )) < 0){
		Sorted_CloseFile( fdb );
		BF_PrintError("Error opening file \"surname\"");
		return -1;
	}

	printf("Searching with surname=\"PAPADOPOULOS\" in \"surname\"\n");
	Sorted_GetAllEntries(fdtmp, "surname", "PAPADOPOULOS");

	if ( Sorted_CloseFile(fdtmp) < 0 ){
		Sorted_CloseFile( fdb );
		BF_PrintError("Error closing file \"surname\"");
		return -1;
	}

	printf("\n\n");

	/* Close file id */
	if ( Sorted_CloseFile( fdid ) < 0 ){
		Sorted_CloseFile( fdb );
		BF_PrintError("Error closing file \"id\"");
		return -1;
	}

	/* Create a temporary file */
	if ( Sorted_CreateFile("tmp1") < 0 ){
		Sorted_CloseFile( fdb );
		BF_PrintError("Error closing file \"id\"");
		return -1;
	}

	if ( (fdtmp = Sorted_OpenFile( "tmp1" )) < 0 ){
		Sorted_CloseFile( fdb );
		BF_PrintError("Error inserting entry in file \"tmp1\"");
	}

	rec.id = 18;
	strcpy(rec.name, "K18");
	strcpy(rec.surname, "YSBD");
	rec.avgPoints = 7.239f;

	printf("Inserting entry in a temporary file\n");
	if ( Sorted_InsertFirstEntry( fdtmp, rec ) < 0 ){
		Sorted_CloseFile( fdb );
		Sorted_CloseFile( fdtmp );
		BF_PrintError("Error inserting entry in file \"tmp1\"");
	}
	printf("\n\n");

	/* Print everything from "b" */
	printf("Printing everything from file \"b\" \n");
	Sorted_GetAllEntries(fdb, "avgPoints", NULL);
	printf("\n\n");

	/* Close b */
	if ( Sorted_CloseFile( fdb ) < 0 ){
		Sorted_CloseFile( fdtmp );
		BF_PrintError("Error closing file \"b\"");
	}

	/* Print everything from tmp */
	printf("Printing everything from file \"tmp1\" \n");
	Sorted_GetAllEntries(fdtmp, "id", NULL);
	printf("\nDid you print a record? You should have..\n");

	/* Close the temporary file */
	Sorted_CloseFile(fdtmp);

	return 0;
}
