/************************************************************************
  File: readme.txt
*************************************************************************/
////den exw ellhnika sto putty kai sas grafw se greeklish

stoixeia:Giakoumis Antonis  1115200700035
	     Mpegeths Nikolaos  1115200700281

compile etsi:
        gcc main.c Sorted.c BF.o -o run

klhsh:
      ./run > test.txt 
            (gia na ta valei se arxeio mias kai ap'to putty
             den emfanizei olo to katevato twn typwsewn)

ta arxeia einai ta:
        
        BF.h
        record.h
        main1.c
        main2.c
        Sorted.c
        Sorted.h
        readme.txt
//oi 3 prwtes synarthseis kaloun apla thn synarthsh tou BF epipedou


/******************** Sorted_InsertFirstEntry ********************/
   h synarthsh ayth arxika diavazei posa block yparxoun
   epeita an den yparxoun block dhmiourgei 1. to diavazei
   eisagei thn do8eisa eggrafh sthn prwth 8esh toy prwtou block
   prosarmwzei ton counter sthn arxh kai epistrefei to block me write back



/******************** Sorted_GetAllEntries ********************/
   arxika diavazei ton ari8mo twn block kai apofasizei ti 8a kanei
   an exei block kai exei NULL sto value tote 8a dwsei shma na ta typwsei ola
   alliws elegxei na einai swsto to fieldname kai an einai swsto elegxei ta
   arxeia an einai taksinomhmena me ton idio tropo pou to kanei h checksorted
   an pane ola kala tote dhlwnetai taksinomhmeno kai an einai NULL
   to value trexei seiriaka ta block kai ta records kai ta typwnei
   se diaforetikh periptwsh ksekinaei dyadikh anazhthsh sta block
   pairnei to mesaio block toy arxeiou
   koitaei an to value einai mikrotero apo thn prwth eggrafh toy block,
   wste na koitaksei to aristero miso toy arxeiou h an einai megalytero
   apo thn teleytaia toy eggrafh wste na koitaksei to deksio miso toy arxeiou
   an den isxyei kati apo ayta tote h eggrafh 8a einai sigoura mesa sto block ayto
   ayto epanalambanetai mexri na vre8ei to block
   otan bre8ei kanei dyadikh anazhthsh stis eggrafes toy block mexri na vrei
   (an yparxei) poia eggrafh einai ayth pou psaxnoume
   otan thn vrei arxizei kai trexei pros ta pisw seiriaka mexris otou na vrei tis
   prohgoumenes eggrafes me value.omoiws pros thn anti8eth katey8unsh
   telos typwnei apo thn prwth eggrafh pou vrike ws thn teleytaia seiriaka
   //yparxei sto telos mia typwsh pou exei metrhsei posa block diavasthkan,alla
   //den xrhsimopoieitai.ayto ginetai gia na tairiazeih synarthsh mas me tis dw8eises typwseis



/******************** Sorted_checkSortedFile ********************/
   anoigei to arxeio kai diavazei posa block exei
   me mia epanalhptikh domh trexei ta block kai tis eggrafes toys mia pros mia
   elegxei an h prohgoumenh eggrafh kai h twrinh exoun katallhlh timh gia na
   einai sorted kai an den exoun stamataei kai epistrefei arnhtiko ari8mo
   //an to arxeio einai adeio tote einai taksinomhmeno...



/******************** Sorted_mergeFiles ********************/
   arxika anoigei ta arxeia,ypologizei poses eggrafes xwrane se ena block genika
   ftiaxnei to kainourio onoma toy arxeiou kai pairnei thn prwth eggrafh apo ka8e arxeio
   ka8ws kai ton ari8mo twn eggrafwn pou exei to prwto block kai dhmiourgei to kainourio
   arxeio kai toy ftiaxnei to prwto toy block.
   meta mpainei se epanalhptiko vrogxo o opoios apofasizei arxika apo poio arxeio 8a mpei
   h eggrafh pou exei diavastei hdh kai thn pernaei sto "rec" kai diavazei thn epomenh
   gia na eksetastei sthn epomenh epanalhpsh.
   an teleiwsoun oi eggrafes tote sthn teleytaia pou diavasame dinoume -1 sto id ths kai
   etsi diavazei mono apo to allo arxeio. an termatisei kai h epomenh tote h eggrafh pou
   8a paei sthn "rec" 8a exei -1 sto id kai ekei exoume syn8hkh termatismou.
   h epanalhptikh loipon domh mas afou ftiaksei thn "rec" sthn arxh
   prospa8ei na thn valei sto arxeio pou dhmiourgoume. an xwraei hdh sto block mas
   (kanontas xrhsh toy megistou ari8mou eggrafwn se block)
   mpainei kai prosarmwzetai o akeraios sthn arxh katallhlla.
   an den xwraei grafoume to gemato block sto arxeio kai kanoume allocate ena neo
   block kai mpainei sthn arxh toy.
   telos kleinei ta arxeia ola.
