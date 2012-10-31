/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define M 50

typedef struct nodo
{
    int key;
    struct nodo* next;
}
*vertice;

void push(int n,vertice * coda_top,vertice * coda_end)
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

void azzera_visitato(int visitato[],int n_vertici)
{
    int i;
    for(i=0;i<n_vertici;i++)
        visitato[i]=0;
}

void visita_profondita(int n,vertice grafo[],int visitato[])
{
    vertice tmp;
    visitato[n]=1;
    printf("%5d",n);
    for(tmp=grafo[n]; tmp; tmp=tmp->next)
        if(!visitato[tmp->key])
            visita_profondita(tmp->key,grafo,visitato);

}

void visita_livello(vertice grafo[],int n_vertici,int visitato[])
{
    vertice coda_top=NULL,coda_end=NULL,tmp;
    int start;
    azzera_visitato(visitato,n_vertici);
    do
	{
	    printf("\nDa qualche vertice si vuole iniziare la visita per livello : ");
    	scanf("%d",&start);
	}while(start<0 || start >= n_vertici);
	push(start,&coda_top,&coda_end);
    visitato[start]=1;
    printf("\n\n");
    while(coda_top)
    {
        for(tmp=grafo[pop(&coda_top)]; tmp; tmp=tmp->next)
            if(!visitato[tmp->key])
            {
                visitato[tmp->key]=1;
                push(tmp->key,&coda_top,&coda_end);
            }
    }
    printf("NULL");
}

void stampa_grafo(int n_vertici, vertice grafo[])
{
    vertice tmp;
    int i;
    system("cls");
    for(i=0; i<n_vertici; i++)
    {
        tmp=grafo[i];
        printf("%d : ",i);
        while(tmp)
        {
            printf("%d - > ",tmp->key);
            tmp=tmp->next;
        }
        printf("NULL\n");
    }
}

vertice crea_lista(int ver_adi)
{
    vertice testa,tmp;
    testa=NULL;
    for(;ver_adi;ver_adi--)
    {
        printf("\ninserisci i vertici: ");
        tmp=(vertice)malloc(sizeof(struct nodo));
        tmp->next=testa;
        scanf("%d",&tmp->key);
        testa=tmp;
    }
    return testa;
}

int crea_grafo(vertice grafo[])
{
    int n_vertici,ver_adi,i;
    system("cls");
    printf("inserisci il numero di vertici: ");
    scanf("%d",&n_vertici);
    for(i=0; i<n_vertici; i++)
    {
        printf("\nInserisci il numero di vertici adiacenti a %d: ",i);
        scanf("%d",&ver_adi);
        grafo[i]=crea_lista(ver_adi);
    }
    return n_vertici;
}

int main()
{
    int n_vertici,scelta,visitato[M];
    vertice grafo[M];
    n_vertici=crea_grafo(grafo);
    do
    {
        system("cls");
        printf("Gestione di un grafo\n\n"
               "1)stampa lista d'adiacenza\n"
               "2)visita in profondita\'\n"
               "3)visita in ampiezza\n"
               "0)esci\n");
        scanf("%d",&scelta);
        switch(scelta)
        {
            case 1:
                stampa_grafo(n_vertici,grafo);
                break;
            case 2:
                printf("\n\ninserisci il nodo radice: ");
                scanf("%d",&scelta);
                azzera_visitato(visitato,n_vertici);
                visita_profondita(scelta,grafo,visitato);
                break;
            case 3:
                visita_livello(grafo,n_vertici,visitato);
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
