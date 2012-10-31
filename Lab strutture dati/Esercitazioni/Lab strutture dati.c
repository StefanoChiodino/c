/* Stefano Chiodino 39962

Ho analizzato il tempo necessario per la ricerca con una funzione tipo

############################################################################################################
void tour(vertice *albero)
{
    int nodi,i,j,h, altezza, altezza_totale, ripetizioni;
    float tempo[2];
    clock_t start,end;
    for(nodi=10, ripetizioni=500, tempo[0]=tempo[1]=0, h=0; nodi<MAX_SIZE ;nodi*=2 ,ripetizioni/=1.4, h=(h+1)%2)
    {
        for(j=0, tempo[h]; j<ripetizioni; j++)
        {
            rand_albero(albero,nodi);
            start=clock();
            for(i=altezza_totale=0; i<nodi/2; i++)//analizzo solo i vertici di grado 1 e 2
            {
                altezza=altezza_minima(albero, i);
                altezza_totale+=altezza;
            }
            end=clock();
            tempo[h]+=(double)(end-start)/CLK_TCK;
        }
        tempo[h]/=ripetizioni;
        printf("%5d nodi: altezza minima %6d in %3f secondi (%2f volte più dell'ultimo passo)\n", nodi, altezza_totale, tempo[h], tempo[h]/tempo[(h+1)%2]);
    }
}
############################################################################################################

ed è risultato che il tempo t aumenta in modo maggiore rispetto al numero di nodi (nel caso della funzione mentre i nodi raddoppiano il tempo si moltiplica di circa 2.2/2.3)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#define MAX_SIZE 100000

typedef struct nodo
{
    int key;
    struct nodo* next;
}
*vertice;

int pop(vertice *top)
{
    int n;
    vertice padre;
    padre=*top;
    n=padre->key;
    *top=(*top)->next;
    free(padre);
    return n;
}

vertice push(int n, vertice top)
{
    vertice tmp=(vertice)malloc(sizeof(struct nodo));
    tmp->key=n;
    tmp->next=top;
    return tmp;
}

int altezza_minima(vertice albero[],int nodo)
{
    int altezza;
    vertice testa[2],scroll;//utilizzo due liste concatenate riempiedone una con tutti i figli..
    testa[1]=NULL;//..dell'altra alternativamente fino a trovare una foglia (grafo[h]=NULL)
    testa[0]=push(nodo,NULL);
    for(altezza=0; testa[altezza%2] ; altezza++)
    {
        while(testa[altezza%2])//finche la lista non è vuota...
        {
            nodo=pop(&testa[altezza%2]);//scarico numeri da una lista
            if(!albero[nodo])
                return altezza;
            for(scroll=albero[nodo]; scroll; scroll=scroll->next)
                testa[(altezza+1)%2]=push(scroll->key,testa[(altezza+1)%2]);//e metto i figli nell'altra
        }
    }
}

void somma_altezze_minime(vertice albero[],int vertici)
{
    int i, altezza, altezza_totale;
    for(i=altezza_totale=0; i<vertici/2; i++)//analizzo solo i vertici di grado 1 e 2
    {
        altezza=altezza_minima(albero, i);
        printf("L'altezza minima di %d e\' %3d\n", i, altezza);
        altezza_totale+=altezza;
    }
    printf("\n\nL'altezza totale e\' di %d", altezza_totale);
}

vertice crea_lista(int nodi_figli, int n_nodi)
{
    vertice top=NULL;
    int n;
    while(nodi_figli)
    {
		printf("\ninserisci i vertici: ");
        scanf("%d",&n);
        if(n<0 || n>=n_nodi)
            printf(">\t\til nodo %d non fa parte di questo albero\n\a");
        else
        {
            top=push(n,top);
            nodi_figli--;
        }
    }
    return top;
}

void crea_albero(vertice *albero, int n_nodi)
{
    int nodi_figli,i;
    for(i=0; i<n_nodi; i++)
    {
        do
        {
            printf("\nQuanti figli ha %d? ",i);
            scanf("%d",&nodi_figli);
        }
        while(nodi_figli >= n_nodi);//non può avere più figli di tutti i nodi meno se stesso
        albero[i]=crea_lista(nodi_figli, n_nodi);
    }
}

void rand_albero(vertice *albero, int n_nodi)//per semplicità crea semplicemente un albero con nodi di grado 2 (figli= padre*2 e padre*2+1)
{
    int i, j;
	for(i=0, j=1; j<n_nodi-1; i++)//riempio i nodi di grado 2
	    albero[i]=push(j++,push(j++,NULL));//2 push concatenati in cui al primo passo NULL
	if(n_nodi%2==0)//se esiste uin nodo di grado 1
        albero[i++]=push((j),NULL);
    for(; i<n_nodi; i++)
        albero[i]=NULL;
}

void stampa(vertice albero[], int n_vertici)
{
    vertice tmp;
    int i;
    for(i=0; i<n_vertici; i++)
    {
        tmp=albero[i];
        printf("[%d] : ",i);
        while(tmp)
        {
            printf("%d - > ",tmp->key);
            tmp=tmp->next;
        }
        printf("NULL\n");
    }
}

void stampa_profondita(vertice albero[],int radice)
{
    int altezza;
    vertice testa[2],scroll;//utilizzo due liste concatenate riempiedone una con tutti i figli..
    testa[1]=NULL;//..dell'altra alternativamente fino a trovare una foglia (grafo[h]=NULL)
    testa[0]=push(radice,NULL);
    for(altezza=0; testa[altezza%2] ; altezza++)
    {
        printf("%d) ",altezza);
        while(testa[altezza%2])//finche la lista non è vuota...
        {
            radice=pop(&testa[altezza%2]);//scarico numeri da una lista
            printf("%5d",radice);
            for(scroll=albero[radice]; scroll; scroll=scroll->next)
                testa[(altezza+1)%2]=push(scroll->key,testa[(altezza+1)%2]);//e metto i figli nell'altra
        }
        printf("\n");
    }
}

int main()
{
    int n_nodi,scelta;
    clock_t start,end;
    vertice albero[MAX_SIZE];
    pulisci;
    printf("Creazione dell'albero mediante liste d'adiacenza\n");
    do
	{
	  	printf("\nInserisci il numero di nodi (max %d): ", MAX_SIZE);
    	scanf("%d",&n_nodi);
	}while(n_nodi > MAX_SIZE);
    pulisci;
    printf("1)creare l'albero manualmente\n"
           "2)creare un albero massimo random\n");
    do
    {
        scanf("%d",&scelta);
    }while(scelta<1 || scelta> 2);
    if(scelta==1)
        crea_albero(albero,n_nodi);
    else
        rand_albero(albero,n_nodi);
    printf("\t>>> Lista d'adiacenza\n");
    stampa(albero,n_nodi);
    pause();
    pulisci;
    printf("\t>>> Vista in profondita\'\n");
    stampa_profondita(albero,0);
    pause();
    pulisci;
    printf("\t>>> Cacolo altezze minime e somme altezza minime\n");
    start=clock();
    somma_altezze_minime(albero,n_nodi);
    end=clock();
    printf("\n\nL'algoritmo ha impiegato %f secondi a trovare la somma delle altezze minime",(double)(end-start)/CLK_TCK);
    pause();
    return 0;
}
