/************************************************************************
  File: Sorted.h
*************************************************************************/
#include "record.h"

int Sorted_CreateFile( char *fileName );
int Sorted_OpenFile( char *fileName );
int Sorted_CloseFile( int fileDesc );
int Sorted_InsertFirstEntry ( int fileDesc, Record record );
void Sorted_GetAllEntries( int fileDesc, char* fieldName, void *value );
int Sorted_checkSortedFile( const char* file, int fieldNo );
int Sorted_mergeFiles( const char* file1, const char* file2, int fieldNo );
