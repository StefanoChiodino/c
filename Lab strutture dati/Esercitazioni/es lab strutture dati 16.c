/*Stefano Chiodino 39962*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "header.h"
#define MAX_VERT 50

typedef struct nodo
{
    int key;
    struct nodo *next;
}
*vertice;

void push(int n, vertice * coda_top, vertice * coda_end)
{
    vertice tmp=(vertice)malloc(sizeof(struct nodo));
    tmp->key=n;
    tmp->next=NULL;
    if(*coda_top)
        (*coda_end)->next=tmp;
    else
        *coda_top=tmp;
    *coda_end=tmp;
}

int pop(vertice *coda_top)
{
    int n;
    vertice tmp=*coda_top;
    n=(*coda_top)->key;
    *coda_top=(*coda_top)->next;
    free(tmp);
    printf("%d -> ",n);
    return n;
}

int key_to_index(vertice grafo[], int n_vertici, int key)//se non trova l'elemento ritorna n_vertici
{
 	int i;
    for(i=0; i<n_vertici && grafo[i]->key!=key; i++);
    return i;
}

int connesso(vertice scroll, int key)
{
    for(scroll=scroll->next; scroll && scroll->key!=key; scroll=scroll->next);
    if(scroll)
        return 1;
    return 0;
}

void push_crea(vertice grafo, int key)
{ 	
    vertice tmp;
    tmp=(vertice)malloc(sizeof(struct nodo));
    tmp->next=grafo->next;
    tmp->key=key;
    grafo->next=tmp;
}

int crea_grafo(vertice grafo[])
{
    int n_vertici,key1,key2,i,j;
    char flag;
    do
	 {
        printf("Inserisci il numero di vertici (max %d): ",MAX_VERT);
    	  scanf("%d",&n_vertici);
	 }while(n_vertici >MAX_VERT);
    for(i=0;i<n_vertici;i++)
    {
        do
		  {
	         printf("inserisci il vertice numero %d: ",i+1);
        	   scanf("%d",&j);
		  }while(key_to_index(grafo,i,j)!=i);
        grafo[i]=(vertice)malloc(sizeof(struct nodo));
        grafo[i]->key=j;
        grafo[i]->next=NULL;
    }
    do
    {
        printf("\n\ninserisci i vertici di un lato: ");
        scanf("%d",&key1);
        scanf("%d",&key2);
    	i=key_to_index(grafo, n_vertici, key1);
    	j=key_to_index(grafo, n_vertici, key2);
    	if(i!=n_vertici && j!=n_vertici)//se esistono e non sono connessi tra loro
    	{
			if(!connesso(grafo[i],key2) && !connesso(grafo[j],key1))
			{
		        push_crea(grafo[i],key2);
		        push_crea(grafo[j],key1);
			}
			else
			    printf(">>> Vertici gia\' connesso!\n");
        }
		else
		    printf(">>> Vertice inesistente!\n");
        fflush(stdin);
        printf("Premi q per uscire, qualsiasi altro tasto per immettere altri lati");
        flag=getch();
    }
    while(flag!='q' && flag!='Q');
    return n_vertici;
}

void azzera_visitato(int visitato[],int n_vertici)
{
    int i;
    for(i=0;i<n_vertici;i++)
        visitato[i]=0;
}

void visita_profondita(int n, vertice grafo[], int visitato[], int n_vertici)
{
    vertice scroll;
    printf("%d -> ",n);//stampo il valore della chiave
    n=key_to_index(grafo,n_vertici,n);//faccio diventare n l'indice dell'array
    visitato[n]=1;
    for(scroll=grafo[n]->next; scroll; scroll=scroll->next)
        if(!visitato[key_to_index(grafo,n_vertici,scroll->key)])
		    visita_profondita(scroll->key,grafo,visitato,n_vertici);
}

void visita_livello(vertice grafo[],int n_vertici,int visitato[])
{
    vertice coda_top=NULL,coda_end=NULL,tmp;
    int start, i;
    azzera_visitato(visitato,n_vertici);
    printf("Da qualche vertice si vuole iniziare la visita per livello : ");
    scanf("%d",&start);
    push(start,&coda_top,&coda_end);
    visitato[key_to_index(grafo,n_vertici,start)]=1;
    printf("\n\n");
    while(coda_top)
    {
        tmp=grafo[key_to_index(grafo,n_vertici,pop(&coda_top))]->next;
        while(tmp)
        {
		    i=key_to_index(grafo,n_vertici,tmp->key);
            if(!visitato[i])
            {
                visitato[i]=1;
                push(tmp->key,&coda_top,&coda_end);
            }
            tmp=tmp->next;
        }
    }
    printf("NULL");
}

void stampa_grafo(int n_vertici, vertice grafo[])
{
    vertice tmp;
    int i;
    for(i=0; i<n_vertici; i++)
    {
        tmp=grafo[i];
        printf("[%d] : ",i);
        while(tmp)
        {
            printf("%d - > ",tmp->key);
            tmp=tmp->next;
        }
        printf("NULL\n");
    }
}

void pop_delete(vertice scroll, int key)
{
    vertice tmp;
    for(; scroll->next && scroll->next->key!=key; scroll=scroll->next);
    tmp=scroll->next;
    scroll->next=tmp->next;
    free(tmp);
}

void delete_lato(vertice grafo[], int n_vertici)
{
    int i,j,key1,key2;
    printf("Inserisci i vertici connessi dal lato da cancellare: ");
    scanf("%d",&key1);
    scanf("%d",&key2);
    i=key_to_index(grafo, n_vertici, key1);
    j=key_to_index(grafo, n_vertici, key2);
   	if(i!=n_vertici && j!=n_vertici && connesso(grafo[i],key2) && connesso(grafo[j],key1))//se esistono e sono connessi tra loro
    {
		pop_delete(grafo[i],key2);
		pop_delete(grafo[j],key1);
      printf("\nLato correttamente eliminato");
    }
    else
        printf("elementi non trovati o non connessi!");
}

void componenti_connesse(vertice grafo[], int n_vertici, int visitato[])
{
    int i;
    azzera_visitato(visitato, n_vertici);
    for(i=0; i<n_vertici; i++)
    {
 		if(!visitato[key_to_index(grafo, n_vertici, grafo[i]->key)])
 		{
            visita_profondita(grafo[i]->key, grafo, visitato, n_vertici);
        	printf("\n");
		}
    }
}

int main()
{
    vertice grafo[MAX_VERT];
    int scelta,n_vertici=crea_grafo(grafo),visitato[MAX_VERT];
    do
    {
        pulisci;
        printf("Gestione di un grafo\n\n"
               "1)stampa lista d'adiacenza\n"
               "2)visita in profondita\'\n"
               "3)visita in ampiezza\n"
               "4)cancella un lato\n"
               "5)vedi le componenti connesse\n"
               "0)esci\n");
        scanf("%d",&scelta);
        pulisci;
        switch(scelta)
        {
            case 1:
            	 stampa_grafo(n_vertici,grafo);
            	 break;
            case 2:
            	 printf("inserisci il nodo radice: ");
           		 scanf("%d",&scelta);
            	 azzera_visitato(visitato,n_vertici);
            	 visita_profondita(scelta,grafo,visitato,n_vertici);
	        	 break;
            case 3:
            	 visita_livello(grafo,n_vertici,visitato);
            	 break;
            case 4:
				 delete_lato(grafo,n_vertici);
				 break;
            case 5:
				 componenti_connesse(grafo,n_vertici,visitato);
				 break;
            case 0:
            	 return 0;
            default :
          		 printf("\nscelta errata!");
        }
        pause();
    }
    while(1);
}
