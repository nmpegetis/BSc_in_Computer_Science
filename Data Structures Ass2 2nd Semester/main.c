/*******************************************************************************
Arxeio ylopoihshs	: main.c
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#include <stdio.h>	/*standar input-output*/
#include <stdlib.h>	/*gia xrisi tis srand(), RAND_MAX*/
#include <time.h>	/*gia xrisi tis time()*/
#include "BankQueueOA.h"/*gia xrisi olwn twn sunartisewn pou den dilwnontai sto stdio.h kai twn metablitwn pou den dilwnontai se auto to arxeio*/

int main(void)
{
	BankOurasPtr   	oura;			/*dilwsi gia tin oura pelatwn*/
	BankOurasPtr	ouraAmea;		/*dilwsi gia tin oura twn AMEA*/
	TStoixeiouListas elements;		/*o tupos twn stoixeiwn "elements"*/
	float		pithanotita_afiksis;	/*pithanotita afiksis, metaksu 0 kai 1*/
	float		pithanotita_amea;	/*pithanotita na einai AMEA, metaksu 0 kai 1*/
	float		pithanotita_apoxwrisis;	/*pithanotita na uparksei apoxwrisi, metaksu 0 kai 1*/
	unsigned int	xronos_eksupiretisis;	/*standar xronos eksupiretisis enos pelati apo ton tamia*/
	unsigned int	xronos_prosomoiwsis; 	/*sunolikos xronos leitourgias tis trapezas*/
	unsigned int	enapomenwn_xronos;	/*xronos gia to telos eksupiretisis enos pelati*/
	unsigned int	eksupiretithentes_pelates; 	/*plithos eksupiretithentwn pelatwn*/
	unsigned int	anamoni_eksupiretithentwn;	/*sunolikos xronos anamonis twn eksupiretithentwn pelatwn apo tin kanoniki oura*/
	int		pelates_stin_oura;	/*sunolikos arithmos pelatwn pou perimenoun stin kanoniki oura*/	/*auti i metabliti stin pragmatikotika den xreiazetai kan...einai oso to megethos tis ouras panta*/
	int 		sunolo_pelatwn;		/*to sunolo twn pelatwn pou piran xartaki kai mpikan stin oura*/
	int		tamias;			/*o xronos pou o tamias exei teleiwsei me tin eksupiretisi tou teleutaiou stin oura pelati kai perimenei*/
	int		uperxeilisi;		/*an den ginei i prosthesi stin oura kai exoume uperxeilisi*/
	int		upoxeilisi;		/*an den ginei i apomakrunsi apo tin oura kai exoume upoxeilisi*/
	float		mesos_xronos;		/*mesos xronos anamonis eksupiretithentwn*/
	float		random;			/*tuxaiotita*/
	float		randomAmea;		/*tuxaiotita gia ta AMEA*/
	
	//***logika tha xreiastoun metablites gia na kratame kai ti thesi tou pelati...
	
	srand(time(NULL));			/*gennitria tuxaiwn arithmwn*/

	printf("Dwste xrono leitourgias trapezis, pithanotita afiksis pelati(p.x 0.55), pithanotita na einai AMEA(p.x 0.15), pithanotita na apoxwrisei pelatis(p.x 0.08) kai xrono eksupiretisis\n");
	scanf("%u %f %f %f %u", &xronos_prosomoiwsis,&pithanotita_afiksis,&pithanotita_amea,&pithanotita_apoxwrisis,&xronos_eksupiretisis);
	getchar();
	printf("\nH prosomoiwsi tha diarkesei %4u lepta.\n",xronos_prosomoiwsis);
	printf("H pithanotita afiksis pelati se ena lepto einai: %4.2f.\n",pithanotita_afiksis);
	printf("H pithanotita o pelatis pou afixthike na einai AMEA einai: %4.2f.\n",pithanotita_amea);
	printf("H pithanotita na apoxwrisei kapoios pelatis einai: %4.2f.\n",pithanotita_apoxwrisis);
	printf("H diarkeia eksupiretisis enos pelati einai %d lepta.\n\n\n",xronos_eksupiretisis);
		
	printf("Oura pelatwn: ");
	oura = BankOura_dimiourgia();	/*dimiourgia mias ouras megethous 0 pou den exei oute epomeno oute proigoumeno...einai keni*/
	printf("Oura AMEA: ");
	ouraAmea = BankOura_dimiourgia();	/*dimiourgia allis mias ouras megethous 0 gia ta AMEA pou den exei oute epomeno oute proigoumeno...einai keni*/
	xronos = 0;
	enapomenwn_xronos = 0;
	eksupiretithentes_pelates = 0;
	anamoni_eksupiretithentwn = 0;
	pelates_stin_oura = 0;
	pelates_se_anamoni = 0;
	sunolo_pelatwn = 0;
	thesi = 0;
	tamias = 0;

	while( xronos <= xronos_prosomoiwsis )
	{
	
	/*ta parakatw ta kanw ola mesw sunartisewn gia kaluteri apokrupsi OA*/
	
		TSListasSetEisodos(&elements, xronos);
		int problepsi = (xronos_eksupiretisis*pelates_se_anamoni)+enapomenwn_xronos;	//i problepsi pou grafei to xartaki eisodou xwris na kserei an eimaste AMEA i oxi
		TSListasSetProblepsi(&elements, problepsi);
		TSListasSetArithmos(&elements, sunolo_pelatwn);
		TSListasSetThesi(&elements, thesi);
//to allaksa mallon den xreiazetai		pelates_se_anamoni = pelates_stin_oura;
		
		random = ((float)rand())/(float)(RAND_MAX);	/*ta metatrepei epitopou se float,to RAND_MAX ~= 32767*/
		randomAmea = ((float)rand())/(float)(RAND_MAX);	
		printf("\nlepto: %d \n",xronos);
//PRIN: i pitanotita afiksis den mporei na einai mikroteri apo tin pithanotita na einai AMEA
//META: i pithanotita AMEA eksartatai apo tin pithanotita afiksis twn pelatwn
		if ( random < pithanotita_afiksis ){		/*an ftasei pelatis (kumainetai metaksu 0-1)*/
			if( random < (pithanotita_amea*pithanotita_afiksis) ){	/*an ftasei kapoio AMEA*/
/****sxolio****/		int x =	BankOura_megethos(ouraAmea);//mporw na to kanw kai kalutera alla einia teleutaia stigmi kai twra to proseksa to lathos pou ektupwne sto statistics kai etsi to allaksa me auto ton tropo...ligo paradoksos tropos alla swstos
				TSListasSetThesi(&elements, x);
				BankOura_prosthesi(&ouraAmea, elements, &uperxeilisi);		//tote prosthese ton pelati stin oura twn AMEA
				if (!uperxeilisi){		/*an egine i prosthesi kai den exoume uperxeilisi*/
					BankOura_UpdateThesi(oura, 1 );	/*metakinise ti thesi olwn twn pelatwn stin kanoniki oura mia thesi pisw afou dinetai proteraiotita sta AMEA*/
/*edw gia poious pelates milame akribws*/pelates_se_anamoni++;	/*an mpei enas pelatis i oura auksanetai kata 1*/	/*mipws na ++ tous pelates stin anamoni?????/*/
/*/to ebala twra*/			thesi++;		        				
        				sunolo_pelatwn++;
        				printf("Prostethike ena AMEA stin oura twn AMEA\n");
/*kapou edw mesa mipws mpei kai to shift*/}
        			else{
        				printf("Yperxeilisi ouras!\n");
                  			return 0;
        			}
        		}
			else{
				BankOura_prosthesi(&oura, elements, &uperxeilisi);		//alliws prosthese ton stin kanoniki oura			
				if (!uperxeilisi){		/*an egine i prosthesi kai den exoume uperxeilisi*/ 
					pelates_se_anamoni++;
/*omoiws me parapanw*/         		pelates_stin_oura++;	
        				thesi++;
        				sunolo_pelatwn++;
        				printf("Prostethike enas pelatis stin oura\n");
        			}
        			else{
        				printf("Yperxeilisi ouras!\n");
                	 		return 0;
        			}
        		}
        	}
        	else printf("Se auto to lepto den irthe kanenas neos pelatis\n");
        	
        	if( !BankOura_keni(ouraAmea) ){
        		printf("H oura twn AMEA exei ws eksis:\n");
/*EXTRA*/		inspectQbyOrder (ouraAmea);			/*gia na ektupwnetai i oura opws einai mexri stigmis efoson uparxei estw kai ena AMEA mesa se auti*/
        	}
      		printf("H oura twn pelatwn exei ws eksis:\n");
/*EXTRA*/	inspectQbyOrder (oura);			/*gia na ektupwnetai i kanoniki oura opws einai mexri stigmis*/
		if(pelates_stin_oura !=0 ){	//an uparxei estw k enas pelatis stin kanoniki oura
    		    	float possibility = rand()%101;		//i pithanotita me tin opoia tha sugkrinetai i pithanotita_apoxwrisis...kumainetai apo 0-100
			if( (pithanotita_apoxwrisis*100) > possibility ){	//an i sunthiki ginei alithis tote sigoura tha uparksei apoxwrisi
				float pithanotita_apoxwrisis_pelati = rand()%100;		//i pio ekseidikeumeni pithanotita (0-99) gia na OLOUS tous pelates...oso pio konta sto 99 toso pio pithano na apoxwrisei enas pelatis apo tin arxi...oso pio konta sto 0 toso pio pithano na apoxwrisei enas pelatis apo to telos 
				BankOura_apoxwrhsh(oura, pithanotita_apoxwrisis_pelati);
				pelates_se_anamoni--;
				pelates_stin_oura--;
/*kai auto to ebala twra*/	thesi--;
			printf("enas pelatis apoxwrise...i oura twn pelatwn pleon exei ws eksis\n");//na to kanw me arithmo
/*EXTRA*/		inspectQbyOrder (oura);			/*gia na ektupwnetai i oura opws einai mexri stigmis*/
			}
		}

		if ( enapomenwn_xronos == 0)			/*an einai eleutheros o tamias*/
			if (!BankOura_keni(ouraAmea)){			/*kai uparxei AMEA*/
				BankOura_apomakrunsh(&ouraAmea, &elements, &upoxeilisi);	/*tote pigainei sto tameio kai i oura twn AMEA meiwnetai kata mia thesi*/
				if(!upoxeilisi){		/*an kata tin apomakrunsi den upirkse upoxeilisi*/
					BankOura_UpdateThesi(oura, -1 );	/*metakinise ti thesi olwn twn pelatwn stin kanoniki oura mia thesi mprosta*/
/*kai auto to ebala twra*/		BankOura_UpdateThesi(ouraAmea, -1 );	/*metakinise ti thesi olwn twn pelatwn stin kanoniki oura mia thesi mprosta*/
					pelates_se_anamoni--;
/*kai auto twra to ebala*/		thesi--;
					anamoni_eksupiretithentwn += xronos - TSListasGetEisodos(&elements);	/*upologismos xronou anamonis stin oura tou sugkekrimenou pelati mesw sunartisis gia megaluteri apokrupsi*/
					eksupiretithentes_pelates++;	/*o arithmos twn eksupiretithentwn pelatwn auksanei kata 1*/
					enapomenwn_xronos = xronos_eksupiretisis;	/*epanarxikopoiisi tou enapomenontos xronou*/
/*na dw mipws xreiazetai kai edw sto shift +1*/printf("to prwto stin oura AMEA paei sto tameio kai i oura twn AMEA diamorfwnetai ws:\n");
					inspectQbyOrder (ouraAmea);	/*ektupwsi seiras AMEA meta tin apomakrunsi tou prwtou*/
				}
				else {
					printf("Ypoxeilisi ouras!\n");
                  			return 0;
				}
			}
			else if (!BankOura_keni(oura)){			/*kai uparxei pelatis*/		/*stin else if(efoson isxuei) tha mpei mono an den egine i proigoumeni if*/
				BankOura_apomakrunsh(&oura, &elements, &upoxeilisi);	/*tote pigainei sto tameio kai i oura meiwnetai kata mia thesi*/
				if(!upoxeilisi){		/*an kata tin apomakrunsi den upirkse upoxeilisi*/
					BankOura_UpdateThesi(oura, -1 );	/*metakinise ti thesi olwn twn pelatwn stin kanoniki oura mia thesi pisw*/
/*kai auto twra to ebala*/		thesi--;
					pelates_se_anamoni--;
					pelates_stin_oura--;
					anamoni_eksupiretithentwn += xronos - TSListasGetEisodos(&elements);	/*upologismos xronou anamonis stin oura tou sugkekrimenou pelati mesw sunartisis gia megaluteri apokrupsi*/
					eksupiretithentes_pelates++;
					enapomenwn_xronos = xronos_eksupiretisis;
					printf("o prwtos stin oura pelatis paei sto tameio kai i oura diamorfwnetai ws:\n");
					inspectQbyOrder (oura);		/*ektupwsi kanonikis seiras pelatwn meta tin apomakrunsi tou prwtou*/
				}
				else {
					printf("Ypoxeilisi ouras!\n");
                  			return 0;
				}
			}
			else{
				tamias++;	/**************auksanetai o xronos pou o tamias menei adranis[erwtima 4.iii-askisis 1]*/
				printf("O tamias einai adranis kai perimenei ton epomeno pelati\n");
			}
		xronos++; 	/*o xronos ayksanetai kata 1 lepto*/
		if ( enapomenwn_xronos > 0) enapomenwn_xronos --;/*o pelatis brisketai gia toulaxiston ena lepto akoma sto tameio*/	
		pelates_stin_oura = BankOura_megethos(oura); /*allazei o arithmos twn pelatwn pou einai stin oura,tin kalw sto telos gia na exoun prostethei oi tuxwn allages*/
		printf("to megethos tis kanonikis ouras twn pelatwn auti ti xroniki stigmi einai: %d \n",BankOura_megethos(oura));	
		printf("to megethos tis ouras AMEA twn pelatwn auti ti xroniki stigmi einai: %d \n",BankOura_megethos(ouraAmea));
		printf("telos enos leptou\n\n\n");
	} /*while( xronos < xronos_prosomoiosis )*/
	
	if (eksupiretithentes_pelates == 0)
		mesos_xronos = 0.0;
	else
		mesos_xronos = ((float)anamoni_eksupiretithentwn)/((float)eksupiretithentes_pelates);
	
	printf("H trapeza kleinei...\no arithmos twn pelatwn pou perimenoun akomi stin oura kai den exoun eksupiretithei einai: %d pelates\no arithmos twn pelatwn pou eksupiretithikan einai: %d pelates\no mesos xronos anamonis oswn eksupiretithikan einai: %4.2f lepta\no tamias kata ti diarkeia leitourgias tis trapezas emeine adranis gia: %d lepta\n\n", pelates_se_anamoni, eksupiretithentes_pelates, mesos_xronos, tamias );


/************************sto telos tis prosomoiwsis ektupwnontai kapoia epipleon statistika sto Statistics.txt [erwtima 4.iv]****************************/
	FILE * pFile;
	pFile = fopen ("Statistics.txt","a");
	if (pFile!=NULL){
		fprintf( pFile, "\n\nH trapeza kleinei...kapoia epipleon statistika einai:\no arithmos twn pelatwn pou perimenoun akomi stin oura kai den exoun eksupiretithei einai: %d pelates\no arithmos twn pelatwn pou eksupiretithikan einai: %d pelates\no mesos xronos anamonis oswn eksupiretithikan einai: %4.2f lepta\no tamias kata ti diarkeia leitourgias tis trapezas emeine adranis gia: %d lepta\n\n", pelates_se_anamoni, eksupiretithentes_pelates, mesos_xronos, tamias );
	fclose (pFile);
	}

	printf("Oura AMEA: ");
	BankOura_katastrofi(&ouraAmea);	/*katastrofi ouras AMEA*/
	printf("Oura pelatwn: ");
	BankOura_katastrofi(&oura);	/*katastrofi kanonikis ouras pelatwn*/

	getchar();		//gia t windows..dev-c++
	return 0;
}

//ennoeitai oti gia ola ta parapanw stin trapeza leitourgei mono 1 tameio


