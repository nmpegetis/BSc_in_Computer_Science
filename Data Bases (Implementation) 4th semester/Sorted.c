/************************************************************************
  File: Sorted.c
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sorted.h"
#include "BF.h"

int Sorted_CreateFile( char *fileName )
{return BF_CreateFile(fileName);}

////////////////////////////////////////////////////////////////////////////////

int Sorted_OpenFile( char *fileName )
{return BF_OpenFile(fileName);}

////////////////////////////////////////////////////////////////////////////////

int Sorted_CloseFile( int fileDesc )
{return BF_CloseFile(fileDesc);}

////////////////////////////////////////////////////////////////////////////////

void print( Record * r )
{printf("{ %3d| %30s| %30s| %8f}\n", r->id, r->name, r->surname, r->avgPoints );
}

////////////////////////////////////////////////////////////////////////////////

int Sorted_InsertFirstEntry ( int fileDesc, Record record )
{char* block;
 int x = 0;
 int y = 0;
 int no_of_records;
 if ((y = BF_GetBlockCounter(fileDesc)) < 0)
    {BF_PrintError("Error BF_GetBlockCounter");
     x = -1;}
 else
    {if (y == 0)//den exei block mesa ara 8a ftiaksw ena
        {if (BF_AllocateBlock(fileDesc) < 0)
            {BF_PrintError("Error allocating block");
	         x = -1;}
        }
     if (BF_ReadBlock(fileDesc, 0, (void*)&block) < 0)
             {BF_PrintError("Error getting block");
	          x = -1;}
     no_of_records = *((int*)block);
     if (no_of_records <= 0){no_of_records = 1;}
     *((int*)block) = no_of_records;
     memcpy(block+sizeof(int), &record, sizeof(Record));
     if (BF_WriteBlock(fileDesc, 0) < 0)
        {BF_PrintError("Error writing block back");
		 x = -1;}
    }
 return x;
}

////////////////////////////////////////////////////////////////////////////////

void Sorted_GetAllEntries( int fileDesc, char* fieldName, void *value )
{char* block;
 int no_of_blocks = 0;
 int no_of_records;
 int i,j;
 int s,start,startr;//to b einai gia block kai to r gia record
 int e,end,endr;
 int now,nowr;
 int check,checkr;
 int offset,counter_block = 0;
 int flag_found = 0;
 int sorted_file = 1;
 Record rec,rec1,rec2;
 /////////////////////////////////////////////////////
 printf("  ID |             N A M E           |         S U R N A M E         |  POINTS \n");
 printf("-----|-------------------------------|-------------------------------|---------\n");
 /////////////////////////////////////////////////////
 if ((no_of_blocks = BF_GetBlockCounter(fileDesc)) < 0)
    {BF_PrintError("Error BF_GetBlockCounter");}
 else if (no_of_blocks == 0)
    {printf("Empty file to search\n");}
 else if (value == NULL){sorted_file = 1;}
 else if (strcmp(fieldName,"id") != 0 && strcmp(fieldName,"name") != 0 && strcmp(fieldName,"surname") != 0 && strcmp(fieldName,"avgPoints") != 0)
    {sorted_file = 2;printf("Sorted_GetAllEntries: wrong fieldName:1\n");}
 else
    {//tsekarw an einai sorted me to pedio pou leei
     for (i=0;i<no_of_blocks;i++)
         {if (BF_ReadBlock(fileDesc, i, (void*)&block) < 0)
             {BF_PrintError("Error getting block");sorted_file = 0;break;}
          no_of_records = *((int*)block);
          offset = sizeof(int);
          if (i == 0){memcpy(&rec2, block+offset, sizeof(Record));}
          for (j=0;j<no_of_records;j++)
              {memcpy(&rec1, &rec2, sizeof(Record));
               memcpy(&rec2, block+offset, sizeof(Record));
               offset += sizeof(Record);
               if (strcmp(fieldName,"id") == 0){if (rec1.id > rec2.id){sorted_file = 0;break;}}
               if (strcmp(fieldName,"name") == 0){if (strcmp(rec1.name,rec2.name) > 0){sorted_file = 0;break;}}
               if (strcmp(fieldName,"surname") == 0){if (strcmp(rec1.surname,rec2.surname) > 0){sorted_file = 0;break;}}
               if (strcmp(fieldName,"avgPoints") == 0){if (rec1.avgPoints > rec2.avgPoints){sorted_file = 0;break;}}
              }
         }
    }
 if (sorted_file == 0){printf("Sorted_GetAllEntries: unsorted file BF_ID:1\n");}
 if (sorted_file == 1)//einai taksinomhmeno arxeio
    {if (value == NULL)//typwnei ta panta
        {
         for (i=0;i<no_of_blocks;i++)
             {if (BF_ReadBlock(fileDesc, i, (void*)&block) < 0){BF_PrintError("Error getting block");}
              counter_block++;
              no_of_records = *((int*)block);
              offset = sizeof(int);
              for (j=0;j<no_of_records;j++)
                  {memcpy(&rec, block+offset, sizeof(Record));
                   print(&rec);
                   offset += sizeof(Record);
                  }
             }
        }//end if (value == NULL)
     else
        {start = 1;//dyadikh anazhthsh sta blocks
         end = no_of_blocks;
         now = (start+end)/2;
         while (flag_found == 0 && start <= end)
               {now = (start+end)/2;
                if (BF_ReadBlock(fileDesc, (now-1), (void*)&block) < 0){BF_PrintError("Error getting block");break;}
                counter_block++;
                no_of_records = *((int*)block);
                memcpy(&rec1, block+sizeof(int), sizeof(Record));
                memcpy(&rec2, block+sizeof(int)+(no_of_records-1)*sizeof(Record), sizeof(Record));
                if (strcmp(fieldName,"id") == 0)
                   {if (rec1.id > *((int*)value) ){end = now-1;}
                    else if (rec2.id < *((int*)value) ){start = now+1;}
                    else{flag_found = 1;end = now;start = now;}
                   }
                if (strcmp(fieldName,"name") == 0)
                   {if (strcmp(rec1.name,value) > 0){end = now-1;}
                    else if (strcmp(rec2.name,value) < 0){start = now+1;}
                    else{flag_found = 1;end = now;start = now;}
                   }
                if (strcmp(fieldName,"surname") == 0)
                   {if (strcmp(rec1.surname,value) > 0){end = now-1;}
                    else if (strcmp(rec2.surname,value) < 0){start = now+1;}
                    else{flag_found = 1;end = now;start = now;}
                   }
                if (strcmp(fieldName,"avgPoints") == 0)
                   {if (rec1.avgPoints > *((int*)value) ){end = now-1;}
                    else if (rec2.avgPoints < *((int*)value) ){start = now+1;}
                    else{flag_found = 1;end = now;start = now;}
                   }
               }
         if (end == now && start == now)//dyadikh anazhthsh sta records//if (flag_found == 1)
            {flag_found = 0;
             if (BF_ReadBlock(fileDesc, (now-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
             startr = 1;
             endr = no_of_records;
             while (flag_found == 0 && startr <= endr)
                   {nowr = (startr+endr)/2;
                    memcpy(&rec1, block+sizeof(int)+(nowr-1)*sizeof(Record), sizeof(Record));
                    if (strcmp(fieldName,"id") == 0)
                       {if (rec1.id > *((int*)value) ){endr = nowr-1;}
                        else if (rec1.id < *((int*)value) ){startr = nowr+1;}
                        else{flag_found = 1;endr = nowr;startr = nowr;}
                       }
                    if (strcmp(fieldName,"name") == 0)
                       {if (strcmp(rec1.name,value) > 0){endr = nowr-1;}
                        else if (strcmp(rec1.name,value) < 0){startr = nowr+1;}
                        else{flag_found = 1;endr = nowr;startr = nowr;}
                       }
                    if (strcmp(fieldName,"surname") == 0)
                       {if (strcmp(rec1.surname,value) > 0){endr = nowr-1;}
                        else if (strcmp(rec1.surname,value) < 0){startr = nowr+1;}
                        else{flag_found = 1;endr = nowr;startr = nowr;}
                       }
                    if (strcmp(fieldName,"avgPoints") == 0)
                       {if (rec1.avgPoints > *((int*)value) ){endr = nowr-1;}
                        else if (rec1.avgPoints < *((int*)value) ){startr = nowr+1;}
                        else{flag_found = 1;endr = nowr;startr = nowr;}
                       }
                   }
             // bres katw orio block kai rec
             start = now; startr = nowr;
             checkr = startr;check = start;
             if (BF_ReadBlock(fileDesc, (now-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
             counter_block++;
             no_of_records = *((int*)block);
             if (strcmp(fieldName,"id") == 0)
                {memcpy(&rec, block+sizeof(int)+(startr-1)*sizeof(Record), sizeof(Record));
                 while (rec.id == *((int*)value) )
                       {startr = checkr;start = check;
                        if (startr > 1){checkr = startr-1;}
                        else
                           {if (start <= 1){start = 1;startr = 1;break;}
                            else
                               {check = start-1;
                                if (BF_ReadBlock(fileDesc, (check-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
                                counter_block++;
                                checkr = *((int*)block);
                               }
                           }
                        memcpy(&rec, block+sizeof(int)+(checkr-1)*sizeof(Record), sizeof(Record));
                       }
                 }
             if (strcmp(fieldName,"name") == 0)
                {memcpy(&rec, &rec1, sizeof(Record));
                 while (strcmp(rec.name,value) == 0)
                       {startr = checkr;start = check;
                        if (startr > 1){checkr = startr-1;}
                        else
                           {if (start <= 1){start = 1;startr = 1;break;}
                            else
                               {check = start-1;
                                if (BF_ReadBlock(fileDesc, (check-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
                                counter_block++;
                                checkr = *((int*)block);
                               }
                           }
                        memcpy(&rec, block+sizeof(int)+(checkr-1)*sizeof(Record), sizeof(Record));
                       }
                 }
             if (strcmp(fieldName,"surname") == 0)
                {memcpy(&rec, &rec1, sizeof(Record));
                 while (strcmp(rec.surname,value) == 0)
                       {startr = checkr;start = check;
                        if (startr > 1){checkr = startr-1;}
                        else
                           {if (start <= 1){start = 1;startr = 1;break;}
                            else
                               {check = start-1;
                                if (BF_ReadBlock(fileDesc, (check-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
                                counter_block++;
                                checkr = *((int*)block);
                               }
                           }
                        memcpy(&rec, block+sizeof(int)+(checkr-1)*sizeof(Record), sizeof(Record));
                       }
                 }
             if (strcmp(fieldName,"avgPoints") == 0)
                {memcpy(&rec, &rec1, sizeof(Record));
                 while (rec.avgPoints == *((int*)value) )
                       {startr = checkr;start = check;
                        if (startr > 1){checkr = startr-1;}
                        else
                           {if (start <= 1){start = 1;startr = 1;break;}
                            else
                               {check = start-1;
                                if (BF_ReadBlock(fileDesc, (check-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
                                counter_block++;
                                checkr = *((int*)block);
                               }
                           }
                        memcpy(&rec, block+sizeof(int)+(checkr-1)*sizeof(Record), sizeof(Record));
                       }
                 }
             // bres anw orio block kai rec
             end = now; endr = nowr;
             checkr = endr;check = end;
             if (BF_ReadBlock(fileDesc, (now-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
             counter_block++;
             no_of_records = *((int*)block);
             if (strcmp(fieldName,"id") == 0)
                {memcpy(&rec, &rec1, sizeof(Record));
                 while (rec.id == *((int*)value) )
                       {endr = checkr;end = check;
                        if (endr < no_of_records){checkr = endr+1;}
                        else
                           {if (end >= no_of_blocks){end = no_of_blocks;endr = no_of_records;break;}
                            else
                               {check = end+1;
                                if (BF_ReadBlock(fileDesc, (check-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
                                counter_block++;
                                no_of_records = *((int*)block);
                                checkr = 1;
                               }
                           }
                        memcpy(&rec, block+sizeof(int)+(checkr-1)*sizeof(Record), sizeof(Record));
                       }
                 }
             if (strcmp(fieldName,"name") == 0)
                {memcpy(&rec, &rec1, sizeof(Record));
                 while (strcmp(rec.name,value) == 0)
                       {endr = checkr;end = check;
                        if (endr < no_of_records){checkr = endr+1;}
                        else
                           {if (end >= no_of_blocks){end = no_of_blocks;endr = no_of_records;break;}
                            else
                               {check = end+1;
                                if (BF_ReadBlock(fileDesc, (check-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
                                counter_block++;
                                no_of_records = *((int*)block);
                                checkr = 1;
                               }
                           }
                        memcpy(&rec, block+sizeof(int)+(checkr-1)*sizeof(Record), sizeof(Record));
                       }
                 }
             if (strcmp(fieldName,"surname") == 0)
                {memcpy(&rec, &rec1, sizeof(Record));
                 while (strcmp(rec.surname,value) == 0)
                       {endr = checkr;end = check;
                        if (endr < no_of_records){checkr = endr+1;}
                        else
                           {if (end >= no_of_blocks){end = no_of_blocks;endr = no_of_records;break;}
                            else
                               {check = end+1;
                                if (BF_ReadBlock(fileDesc, (check-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
                                counter_block++;
                                no_of_records = *((int*)block);
                                checkr = 1;
                               }
                           }
                        memcpy(&rec, block+sizeof(int)+(checkr-1)*sizeof(Record), sizeof(Record));
                       }
                 }
             if (strcmp(fieldName,"avgPoints") == 0)
                {memcpy(&rec, &rec1, sizeof(Record));
                 while (rec.avgPoints == *((int*)value) )
                       {endr = checkr;end = check;
                        if (endr < no_of_records){checkr = endr+1;}
                        else
                           {if (end >= no_of_blocks){end = no_of_blocks;endr = no_of_records;break;}
                            else
                               {check = end+1;
                                if (BF_ReadBlock(fileDesc, (check-1), (void*)&block) < 0){BF_PrintError("Error getting block");}
                                counter_block++;
                                no_of_records = *((int*)block);
                                checkr = 1;
                               }
                           }
                        memcpy(&rec, block+sizeof(int)+(checkr-1)*sizeof(Record), sizeof(Record));
                       }
                 }
             //typwse ta
             s = 1; e = no_of_records;
             for (i=(start-1);i<end;i++)
                 {if (BF_ReadBlock(fileDesc, i, (void*)&block) < 0){BF_PrintError("Error getting block");}
                  counter_block++;
                  no_of_records = *((int*)block);
                  if (i == start-1){s = startr;}//typwnei apo startr
                  else{s = 1;}
                  if (i == end-1){e = endr;}//typwnei mexri endr
                  else{e = no_of_records;}
                  for (j=s;j<=e;j++)
                      {memcpy(&rec1, block+sizeof(int)+(j-1)*sizeof(Record), sizeof(Record));
                       print(&rec1);
                      }
                 }
            }//end of if (flag_found == 1)
         else{printf("The Record was not found anywhere\n");}
        }//end of else mesa sto else
    }
 ////////////////////////////////////
 //printf("\nThe number of blocks read is %d\n\n",counter_block);
}

////////////////////////////////////////////////////////////////////////////////

int Sorted_checkSortedFile( const char* file, int fieldNo )
{char* block;
 int i,j;
 int no_of_blocks,no_of_records;
 int x = 1;
 int fileDesc;
 if ((fileDesc = BF_OpenFile(file)) < 0){BF_PrintError("Error opening file");x = 0;}
 if ((no_of_blocks = BF_GetBlockCounter(fileDesc)) < 0){BF_PrintError("Error BF_GetBlockCounter");x = 0;}
 Record rec1,rec2;
 for (i=0;i<no_of_blocks;i++)
     {if (BF_ReadBlock(fileDesc, i, (void*) &block) < 0){BF_PrintError("Error getting block");}
      else{no_of_records = *((int*)block);}
      if (i == 0){memcpy(&rec2, block+sizeof(int), sizeof(Record));}
      for (j=0;j<no_of_records;j++)
          {memcpy(&rec1, &rec2, sizeof(Record));
           memcpy(&rec2, block+sizeof(int)+j*sizeof(Record), sizeof(Record));
           if (fieldNo == 0){if (rec1.id > rec2.id){x=0;break;}}
           if (fieldNo == 1){if (strcmp(rec1.name,rec2.name) > 0){x=0;break;}}
           if (fieldNo == 2){if (strcmp(rec1.surname,rec2.surname) > 0){x=0;break;}}
           if (fieldNo == 3){if (rec1.avgPoints > rec2.avgPoints){x=0;break;}}
          }
     }
 if (BF_CloseFile(fileDesc) < 0){BF_PrintError("Error closing file");}
 return x;
}

////////////////////////////////////////////////////////////////////////////////

int Sorted_mergeFiles( const char* file1, const char* file2, int fieldNo )//NA THN KSANADW
{char* new_block;
 char* block1;
 char* block2;
 int x = 0;
 int no_of_blocks1,no_of_blocks2,new_no_of_blocks;
 int no_of_records1,no_of_records2,max_records;
 int new_fileDesc,fileDesc1,fileDesc2;
 if ((fileDesc1 = BF_OpenFile(file1)) < 0){BF_PrintError("Error opening file");}
 if ((no_of_blocks1 = BF_GetBlockCounter(fileDesc1)) < 0){BF_PrintError("Error BF_GetBlockCounter");}
 if ((fileDesc2 = BF_OpenFile(file2)) < 0){BF_PrintError("Error opening file");}
 if ((no_of_blocks2 = BF_GetBlockCounter(fileDesc2)) < 0){BF_PrintError("Error BF_GetBlockCounter");}
 Record rec,rec1,rec2,rec3;
 int result;
 int offset = sizeof(int);
 int size = 2+strlen(file1)+strlen(file2);//to 2 giati exei ena char gia to noumero kai ena to '/0'
 char* new_file = (char*)malloc(size);
 result = sprintf (new_file,"%s%s%d",file1,file2,fieldNo);
 max_records = (BLOCK_SIZE-sizeof(int))/sizeof(Record);
 if ( (result = Sorted_checkSortedFile( file1, fieldNo )) == 0)
    {x = -1;}
 else if ( Sorted_checkSortedFile( file2, fieldNo ) == 0 )
    {x = -1;}
 else
    {int i = 0,j = 0,w = 0;//i,j gia blocks
     if (BF_ReadBlock(fileDesc1, 0, (void*)&block1) < 0)//pare 1h eggrafh apo to file 1
        {BF_PrintError("Error getting block");}
     else
        {memcpy(&rec1, block1+offset, sizeof(Record));
         no_of_records1 = *((int*)block1);
        }
     if (BF_ReadBlock(fileDesc2, 0, (void*)&block2) < 0)//pare 1h eggrafh apo to file 2
        {BF_PrintError("Error getting block");}
     else
        {memcpy(&rec2, block2+offset, sizeof(Record));
         no_of_records2 = *((int*)block2);
        }
     int a = 1,b = 1;//a,b gia eggrafes se block (einai 1 giati phra hdh apo 1 eggrafh)
     if (BF_CreateFile(new_file) < 0){BF_PrintError("Error creating file");}
     else
        {if ((new_fileDesc = BF_OpenFile(new_file)) < 0){BF_PrintError("Error opening new file");}
         else if (BF_AllocateBlock(new_fileDesc) < 0){BF_PrintError("Error allocating block in new file");}
         else{if (BF_ReadBlock(new_fileDesc, 0, (void*)&new_block) < 0){BF_PrintError("Error getting block");}}
        }
     offset = sizeof(int);////////////////////////////////////////////////////////////////////////////////////
     while (i < no_of_blocks1 || j < no_of_blocks2)//ksekina na vazeis eggrafes mesa
           {if (fieldNo == 0)
               {if (rec1.id <= rec2.id){result = 1;}
                else{result = 2;}
               }
            else if (fieldNo == 1)
               {if (strcmp(rec1.name,rec2.name) <= 0){result = 1;}
                else{result = 2;}
               }
            else if (fieldNo == 2)
               {if (strcmp(rec1.surname,rec2.surname) <= 0){result = 1;}
                else{result = 2;}
               }
            else
               {if (rec1.avgPoints <= rec2.avgPoints){result = 1;}
                else{result = 2;}
               }
            if (rec1.id == -1){result = 2;}
            if (rec2.id == -1){result = 1;}
            if (result == 1)
               {memcpy(&rec, &rec1, sizeof(Record));
                if (a < no_of_records1)
                   {if (BF_ReadBlock(fileDesc1, i, (void*)&block1) < 0){BF_PrintError("Error getting block");x = -1;break;}
                    //to readblock evala giati eixa anekshghto provlhma
                    memcpy(&rec1, block1+sizeof(int)+a*sizeof(Record), sizeof(Record));
                    a++;
                   }
                else
                   {i++;
                    if (i > (BF_GetBlockCounter(fileDesc1)-1)){rec1.id = -1;}//gia na stamathsei na pairnei apo ayto to arxeio
                    else if (BF_ReadBlock(fileDesc1, i, (void*)&block1) < 0){BF_PrintError("Error getting block");x = -1;break;}
                    else{a = 1;memcpy(&rec1, block1+sizeof(int), sizeof(Record));}
                   }
               }
            else
               {memcpy(&rec, &rec2, sizeof(Record));
                if (b < no_of_records2)
                   {//if (BF_ReadBlock(fileDesc2, j, (void*)&block2) < 0){BF_PrintError("Error getting block");x = -1;break;}
                    memcpy(&rec2, block2+sizeof(int)+b*sizeof(Record), sizeof(Record));
                    b++;
                   }
                else
                   {j++;
                    if (j > (BF_GetBlockCounter(fileDesc2)-1)){rec2.id = -1;}//gia na stamathsei na pairnei apo ayto to arxeio
                    else if (BF_ReadBlock(fileDesc2, j, (void*)&block2) < 0){BF_PrintError("Error getting block");x = -1;break;}
                    else{b = 1;memcpy(&rec2, block2+sizeof(int), sizeof(Record));}
                   }
               }
            ////////////
            w++;
            if (rec.id == -1)
               {break;}
            else if (rec.id == 0 || strcmp(rec.name,"") == 0 || rec.avgPoints > 10 || rec.avgPoints < 0.000001)
               {w--;}//vgazei tis la8os
            else if (w <= max_records)
               {memcpy(new_block+offset, &rec, sizeof(Record));
                offset = sizeof(int)+w*sizeof(Record);//offset += sizeof(Record);
                *((int*)new_block) = w;
               }
            else
               {if (BF_WriteBlock(new_fileDesc, (BF_GetBlockCounter(new_fileDesc)-1) ) < 0)
                   {BF_PrintError("Error writing block back");
                    x = -1;
                    break;
                   }
                else if (BF_AllocateBlock(new_fileDesc) < 0)
                   {BF_PrintError("Error allocating block in new file");
                    x = -1;
                    break;
                   }
                else if ((new_no_of_blocks = BF_GetBlockCounter(new_fileDesc)) < 0)
                   {BF_PrintError("Error BF_GetBlockCounter");
                    x = -1;
                    break;
                   }
                else if (BF_ReadBlock(new_fileDesc, (new_no_of_blocks-1), (void*)&new_block) < 0)
                   {BF_PrintError("Error getting block");
                    x = -1;
                    break;
                   }
                else
                   {offset = sizeof(int);
                    memcpy(new_block+offset, &rec, sizeof(Record));
                    offset = sizeof(int)+sizeof(Record);
                    w = 1;
                    *((int*)new_block) = w;
                   }
               }
           }
     if (BF_CloseFile(new_fileDesc) < 0){BF_PrintError("Error closing file");}
    }
 if (BF_CloseFile(fileDesc1) < 0){BF_PrintError("Error closing file");}
 if (BF_CloseFile(fileDesc2) < 0){BF_PrintError("Error closing file");}
 free(new_file);
 return x;
}
/************************************************************************
  File: Sorted.c
*************************************************************************/
