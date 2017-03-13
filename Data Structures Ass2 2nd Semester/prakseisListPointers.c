/*******************************************************************************
Arxeio ylopoihshs	: prakseisListPointers.c
Onoma			: N.Mpegetis
A.M			: 1115200700281
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "prakseisListPointers.h"

typedef struct tupos_komvou{
	TStoixeiouListas dedomena;	/*to dedomeno*/
	tupos_deikti    epomenos; 	/*deikths sto epomeno dedomeno*/
} tupos_komvou;	   /*o tupos tou kombou ths listas*/

void eisagwgi_arxi(tupos_deikti * const,TStoixeiouListas, int *);
void eisagwgi_meta(TStoixeiouListas, tupos_deikti, int *);

void LIST_dimiourgia(tupos_deikti *lista)
{
	*lista=NULL;		//i lista den exei kanena dedomeno kai kanena epomeno
}

void LIST_katastrofi(tupos_deikti *lista)
{
	tupos_deikti todel;
	
	while(*lista!=NULL)
	{
		todel=*lista;
		*lista=(*lista)->epomenos;
		free(todel);
	}
}

int LIST_keni(const tupos_deikti lista)
{/*	
 *	Pro: 		Dhmiourgia Listas
 *	Meta:		Epistrefei 1 an h lista einai kenh, diaforetika 0 */
 
	return ( lista == NULL );
}

void LIST_periexomeno(const tupos_deikti p, TStoixeiouListas *val)
{/*	
 *	Pro: 		O deikths p deixnei ena kombo sth lista
 *	Meta:		Epistrefei ta dedomena ston komvo pou deixnei o p*/
 
	TSListasSetValue(val, p->dedomena);
}

void LIST_allagi(tupos_deikti * const p, TStoixeiouListas stoixeio)	//allazei to stoixeio pou einai se mia thesi me ena allo
{
	if(!LIST_keni(*p))
		TSListasSetValue(&(*p)->dedomena, stoixeio);
}

void LIST_diadromi(const tupos_deikti lista, int * const error)	//ektupwnei ta panta apo ti lista
{
	tupos_deikti temp;
	temp=lista;
	*error=0;
	
	if(LIST_keni(temp))
	{
		*error=1;
		return;
	}
	
	while(!LIST_keni(temp))
	{
		TSListasPrintValue(temp->dedomena);
		temp=temp->epomenos;
	}
}

void LIST_eisagwgi(tupos_deikti * const lista, TStoixeiouListas stoixeio,
					tupos_deikti prodeiktis, int *error)
{
	*error=0;
	if(prodeiktis==NULL)
		eisagwgi_arxi(lista, stoixeio, error);
	else
		eisagwgi_meta(stoixeio, prodeiktis, error);		 
}


void eisagwgi_arxi(tupos_deikti * const lista,TStoixeiouListas stoixeio, int *error)
{
/*Pro: O deikths *lista einai h arxh ths listas. Meta: O kombos me ta dedomena stoixeio exei eisax8ei sthn arxh ths listas*/
 
	tupos_deikti prosorinos; /*Deixnei ton neo kombo pou prokeitai na eisax8ei*/

	prosorinos = malloc(sizeof(tupos_komvou));	//desmeusi xwrou gia ton kombo
	if ( prosorinos == NULL )
	{
		*error=1;
		return;
	}
	TSListasSetValue(&prosorinos->dedomena, stoixeio);
   	prosorinos->epomenos = *lista;	// epomenos tou kombou pou edeixne i *lista
    	*lista = prosorinos;	//kai pleon i lista einai o prosorinos 
}


void eisagwgi_meta(TStoixeiouListas stoixeio, tupos_deikti prodeiktis, int *error)
{/*	
 *	Pro: 		O prodeikths deixnei ena kombo sth lista
 *	Meta: 		O komboe me ta dedomena exei eisax8ei meta ton kombo pou
 				deixnei o prodeikths*/
 
	tupos_deikti prosorinos; /*Deixnei ton neo kombo pou prokeitai na eisax8ei*/

	prosorinos = malloc(sizeof(tupos_komvou));
	if (prosorinos == NULL)
	{
		*error=1;
		return;
	}
	TSListasSetValue(&prosorinos->dedomena, stoixeio);
	prosorinos->epomenos = prodeiktis->epomenos;		//omoiws me oti periegrapsa sto eisagwgi_arxi
	prodeiktis->epomenos = prosorinos;
}

void LIST_diagrafi(tupos_deikti * const lista, tupos_deikti *deiktis, int * const error)
{
	tupos_deikti prosorinos;
	*error=0;
	if(LIST_keni(*lista))
	{
		*error=1;
		return;
	}
	if(*lista==*deiktis)
	{
		*lista=(*deiktis)->epomenos;
		free(*deiktis);
		*deiktis=NULL;
	}
	else
	{
	 	if((*lista)->epomenos==*deiktis)
	 		prosorinos=*lista;
 		else
 		{
		 	prosorinos=*deiktis;
 			LIST_proigoumenos(*lista, &prosorinos, error);
			if(*error==1)
				return;
		}
		prosorinos->epomenos=(*deiktis)->epomenos;
		free(*deiktis);
		*deiktis=NULL;
	}
}

void LIST_epomenos(const tupos_deikti lista, tupos_deikti * const p, int * const error)
{     
	*error = 0;
	if((*p)!=NULL)
		*p=(*p)->epomenos;
	else
		*error=1;
}

void LIST_proigoumenos (const tupos_deikti lista, tupos_deikti * const p, int * const error)
{
	tupos_deikti prosorinos=lista;
	*error = 0;
	if((*p)!=NULL)             /* List not empty */
	{
		if((*p)==lista)           /* p points at head of list */
			*p=NULL;                 
		else                       /* there are more nodes between head and *p */
		{
			tupos_deikti prosorinos=lista;
			while(prosorinos->epomenos != *p)
				prosorinos=prosorinos->epomenos;
			*p=prosorinos;
		}
	}
	else
		*error=1;  
}

void LIST_first (const tupos_deikti lista, tupos_deikti * const first, int * const error)
{
	*error=0;
	*first=lista;
	if (lista==NULL)
		*error=1;
}

void LIST_last (const tupos_deikti lista, tupos_deikti * const last, int * const error)
{
	tupos_deikti prosorinos=lista;
	*error = 0;
	*last=NULL;
	if (lista==NULL)           /* list is empty */
		*error=1;                 
	else                       /* not empty*/
	{
		tupos_deikti prosorinos=lista;
		while (prosorinos->epomenos != NULL)
			prosorinos=prosorinos->epomenos;
		*last=prosorinos;
	} 
}

void LIST_anazitisi(const tupos_deikti lista, TStoixeiouListas stoixeio,
					tupos_deikti *prodeiktis, int *vrethike)
{
	TStoixeiouListas temp;
	tupos_deikti trexon;
	int error;

	error=0;
	trexon = lista;
	*prodeiktis = NULL;
	*vrethike = 0;
	while ( (!(*vrethike)) && (!LIST_keni(trexon)))
	{
		LIST_periexomeno(trexon,&temp);
		if (TSListasIso(temp, stoixeio))
			*vrethike =1;
		else
		{
			*prodeiktis = trexon;
			LIST_epomenos(lista, &trexon, &error);
		}
	}
}
