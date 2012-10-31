/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define MAX_STRING 30

typedef struct ele{
        char nome[MAX_STRING];
        struct ele *next;
}*coda;

int empty(coda testa)
{
     if(testa)
         return 1;
     else
         printf("Nessun elemento in lista!\n\n");
         return 0;
}

void pushnsort(char *nome, coda *testa)
{
	coda tmp=(coda)malloc(sizeof(struct ele));
	strcpy(tmp->nome,nome);
	if(strcmp((*testa)->nome,nome)>=0 || !(*testa))
	{
		tmp->next=*testa;
		*testa=tmp;
	}
	else
	{
		coda scroll=*testa;
		while(scroll->next && strcmp(scroll->next->nome,nome)<0)
		    scroll=scroll->next;
		tmp->next=scroll->next;
		scroll->next=tmp;
	}
}

void save(coda testa){
       if(empty(testa))
       {
                       FILE * nomi;
                       nomi=fopen("nomi.txt","wb");
                       while(testa){
                                    fwrite(testa->nome,sizeof(testa->nome),1,nomi);
                                    testa=testa->next;
                       }
                       fclose(nomi);
       }
}

void del(coda *testa){
     coda tmp;
     if(*testa){
                       tmp=*testa;
                       *testa=tmp->next;
                       printf("\nPrimo elemento (\"%s\") eliminato\n",tmp->nome);
                       free(tmp);
     }
     else{
          printf("\nNessun elemento in lista!\n");
     }
}

void push(char *nome, coda *testa, coda *coda)
{
          struct ele *tmp=(struct ele *)malloc(sizeof(struct ele));
          strcpy(tmp->nome,nome);
          if(*testa)
          {
                     (*coda)->next=tmp;
                     *coda=tmp;
          }
          else
               *testa=*coda=tmp;
          tmp->next=NULL;
}

void load(coda *testa){
       coda coda=NULL;
       char nome[MAX_STRING];
       int i=0;
       FILE * nomi;
       nomi=fopen("nomi.txt","rb");
       if(nomi){
                                            printf("\nE' stata trovata una lista, caricamento dati...");
                                            while(!feof(nomi)){
                                                                   fread(nome,sizeof(nome),1,nomi);
                                                                   if(!feof(nomi)){
                                                                                push(nome,testa,&coda);
                                                                   }
                                                                   i++;
                                            }
       printf("\n%d dati caricati\n",i);
       fclose(nomi);
       }
       else
           printf("\n\nNessuna rubbrica trovata\n\n");
       pause();
}

void inserisci(coda *testa)
{
     char nome[MAX_STRING];
     system("cls");
     printf("digita exit per uscire in qualsiasi momento\n\n");
     fflush(stdin);
     printf("Inserisci un nuovo nome: ");
     gets(nome);
     while(strcmp(nome,"exit")!=0)
     {
            pushnsort(nome,testa);
            fflush(stdin);
            printf("\nInserisci un nuovo nome: ");
            gets(nome);
     }
}

void stampa(coda scroll){
     pulisci;
     if(empty(scroll))
               while(scroll)
               {
                            printf("%s\n",scroll->nome);
                            scroll=scroll->next;
               }
}

int main()
{
    coda testa=NULL;
    int scelta;
    load(&testa);
    pulisci;
    do{
        printf("Gestione di una rubbrica\n"
        "1)inseririsci nomi\n"
        "2)eliminare il primo nome\n"
        "3)stampare tutta la lista\n"
        "0)salva ed esci\n");
        scanf("%d",&scelta);
        switch(scelta)
        {
                   case 0:
                        save(testa);
                        return 0;
                   case 1:
                        inserisci(&testa);
                        break;
                   case 2:
                        del(&testa);
                        break;
                   case 3:
                        stampa(testa);
                        break;
                   default:
                           printf("Scelta errata!");
        }
         pause();
         pulisci;
    }while(1);
}
