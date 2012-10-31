/*Stefano Chiodino 39962*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define MAX_STRING 30
#define MAX_CONTATTI 100
#define PASSO_INSER 5

typedef struct ele
{
    char cognome[MAX_STRING],nome[MAX_STRING],indirizzo[MAX_STRING],telefono[MAX_STRING];
}
contatto;

void add(contatto agenda[], int *n_contatti)
{
    if(*n_contatti < MAX_CONTATTI)
        do
        {
            printf("Inserisci il cognome(q per uiscire): ");
            scanf("%s",&agenda[*n_contatti].cognome);
            if(!((agenda[*n_contatti].cognome[0]=='q' || agenda[*n_contatti].cognome[0]=='Q') && agenda[*n_contatti].cognome[1]=='\0'))
            {
                fflush(stdin);
                printf("Inserisci il nome: ");
                gets(agenda[*n_contatti].nome);
                printf("Inserisci l'indirizzo: ");
                gets(agenda[*n_contatti].indirizzo);
                printf("Inserisci il numero di telefono: ");
                gets(agenda[*n_contatti].telefono);
                (*n_contatti)++;
            }
        }
        while(!((agenda[*n_contatti].cognome[0]=='q' || agenda[*n_contatti].cognome[0]=='Q') && agenda[*n_contatti].cognome[1]=='\0') && *n_contatti < MAX_CONTATTI);
    if(*n_contatti == MAX_CONTATTI)
        printf("E' stato raggiunto il limite massimo di contatti!");
}

void stampa(contatto agenda[], int n_contatti)
{
    int i;
    if(n_contatti)
    {
        for(i=0; i<n_contatti;i++)
        {
            printf("%d) %s  %s\n"
                   "    %s\n"
                   "    %s\n\n",i+1,agenda[i].cognome,agenda[i].nome,agenda[i].indirizzo,agenda[i].telefono);
        }
        printf("\n%d contatti in rubrica", n_contatti);
    }
    else
        printf("Nessun contatto in rubrica");
}

void inserzione(contatto *vettore,int elementi)
{
    int i,j;
	char tmp[MAX_STRING];
    for(i=0; i<elementi; i++)
    {
        strcpy(tmp,vettore[i].cognome);
        for(j=i-1; j>=0 && strcmp(tmp,vettore[j].cognome)<0; j--)
            vettore[j+1]=vettore[j];
        strcpy(vettore[j+1].cognome,tmp);
    }
}

void mergensort_inser(contatto rubrica[], contatto tmp[], int n_contatti)
{
    int passo = PASSO_INSER;
    int i, j, k, medio, fine;
    contatto *park;
    for(i=0; i<n_contatti-PASSO_INSER; i+=PASSO_INSER)
        inserzione(rubrica+i, PASSO_INSER);
    inserzione(rubrica+i, n_contatti-i);
   	do//ciclo per aumentare il passo
    {
	    for(k=0; k < n_contatti;)//ciclo per scorrere la lista e fondere i sottofile
	    {
		 	medio=k+passo;
		 	fine=passo*2+k;
		 	if(medio>n_contatti)
		 	    medio=fine=n_contatti;
            else if(fine>n_contatti)
                fine=n_contatti;
	        for(i=k, j=medio; i < medio && j < fine;)
	        {
	            if(strcmp(rubrica[i].cognome,rubrica[j].cognome)<=0)
	                tmp[k++]=rubrica[i++];
	            else
	                tmp[k++]=rubrica[j++];
	        }
            while(i<medio)
                tmp[k++]=rubrica[i++];
            while(j<fine)
                tmp[k++]=rubrica[j++];
	    }
		park=tmp;//scambio la lista originale con quella appena ordinata
		tmp=rubrica;
		rubrica=park;
	    passo*=2;//raddoppio il passo
	}while(passo < n_contatti*2);
    printf("Contatti correttamente ordinati!");
}

void mergensort_iter(contatto *rubrica, contatto *tmp, int n_contatti)
{
 	int passo=1, i, j, k, medio, fine;
	contatto *park;
	do//ciclo per aumentare il passo
    {
	    for(k=0; k < n_contatti;)//ciclo per scorrere la lista e fondere i sottofile
	    {
		 	medio=k+passo;
		 	fine=passo*2+k;
		 	if(medio>n_contatti)
		 	    medio=fine=n_contatti;
            else if(fine>n_contatti)
                fine=n_contatti;
	        for(i=k, j=medio; i < medio && j < fine; )
	        {
	            if(strcmp(rubrica[i].cognome,rubrica[j].cognome)<=0)
	                tmp[k++]=rubrica[i++];
	            else
	                tmp[k++]=rubrica[j++];
	        }
            while(i<medio)
                tmp[k++]=rubrica[i++];
            while(j<fine)
                tmp[k++]=rubrica[j++];
	    }
		park=tmp;//scambio la lista originale con quella appena ordinata
		tmp=rubrica;
		rubrica=park;
	    passo*=2;//raddoppio il passo
	}while(passo < n_contatti*2);
    printf("Contatti correttamente ordinati!");
}

int main()
{
    contatto rubrica[MAX_CONTATTI], tmp[MAX_CONTATTI];
    int scelta,n_contatti=0;
    do
    {
        pulisci
        printf("Gestione di una rubrica con mergesort\n\n"
               "1)Inserire un nuovo elemento\n"
               "2)Stampare la rubrica\n"
               "3)Ordinare gli elementi per cognome con il mergesort iterativo\n"
               "4)Ordinare gli elementi per cognome con il mergesort con inserzione\n"
               "0)uscire\n");
        scanf("%d",&scelta);
        pulisci
        switch(scelta)
        {
            case 0:
            return 0;
            case 1:
            add(rubrica, &n_contatti);
            break;
            case 2:
            stampa(rubrica, n_contatti);
            break;
            case 3:
            mergensort_iter(rubrica, tmp, n_contatti);
            break;
            case 4:
            mergensort_inser(rubrica, tmp, n_contatti);
            break;
            default :
            printf("Scelta errata!");
        }
        pause();
    }while(1);
}
