/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "header.h"
#define MAX_VERT 50

typedef struct nodo
{
    int key;
    struct nodo* next;
}
*vertice;

int key_to_index(vertice grafo[], int n_vertici, int key)//se non trova l'elemento ritorna n_vertici
{
    int i;
    for(i=0; i<n_vertici && grafo[i]->key!=key; i++)
        ;
    return i;
}

int connesso(vertice scroll, int key)
{
    for(scroll=scroll->next; scroll && scroll->key!=key; scroll=scroll->next)
        ;
    if(scroll)
        return 1;
    return 0;
}

void push_crea(int index, vertice testa)
{
    vertice tmp=(vertice)malloc(sizeof(struct nodo));
    tmp->key=index;
    tmp->next=testa->next;
    testa->next=tmp;
}

vertice push_distanze(int index, vertice testa)
{
    vertice tmp=(vertice)malloc(sizeof(struct nodo));
    tmp->key=index;
    tmp->next=testa;
    return tmp;;
}

int crea_grafo(vertice grafo[])
{
    int n_vertici,i,j,h;
    do
    {
        printf("Inserisci il numero di vertici (max %d): ",MAX_VERT);
        scanf("%d",&n_vertici);
    }
    while(n_vertici >MAX_VERT);
    for(i=0; i<n_vertici; i++)
    {
        do
        {
            printf("inserisci il vertice numero %d: ",i+1);
            scanf("%d",&j);
        }
        while(key_to_index(grafo,i,j)!=i);
        grafo[i]=(vertice)malloc(sizeof(struct nodo));
        grafo[i]->key=j;
        grafo[i]->next=NULL;
    }
    for(i=0; i<n_vertici; i++)
    {
        printf("\n\nQuanti vertici sono connessi a %d: ",grafo[i]->key);
        scanf("%d",&j);
        while(j)
        {
            printf("inserisci i vertici: ");
            scanf("%d",&h);
            if(key_to_index(grafo, n_vertici, h)!=n_vertici)
            {
                if(!connesso(grafo[i],h))
                {
                    j--;
                    push_crea(h, grafo[i]);
                }
                else
                    printf(">>> Vertice gia\' connesso!\n");
            }
            else
                printf(">>> Vertice inesistente!\n");
        }
    }
    return n_vertici;
}

void azzera_visitato(int n_vertici,int visitato[])
{
    while(n_vertici)
        visitato[--n_vertici]=0;
}

int lung_min(vertice grafo[],int i,int f,int n_vertici,int visitato[])//crea tutti i percorsi possibili in modo ricorsivo e ne valuta la lunghezza
{
    int min=MAX_VERT,tmp,index;
    vertice scroll;
    visitato[i]=1;
    if(i==f)
        return 0;
    for(scroll=grafo[i]->next; scroll; scroll=scroll->next)
    {
        index=key_to_index(grafo,n_vertici,scroll->key);
        if(!visitato[index])
        {
            tmp=lung_min(grafo,index,f,n_vertici,visitato);
            if(tmp<min)
            {
                min=tmp;
            }
        }
    }
    return 1+min;
}

void distanze_ric(vertice grafo[],int n_vertici,int visitato[])
{
    int i, f, lng;
    for(i=0; i<n_vertici; i++)
        for(f=0; f<n_vertici; f++)
            if(i!=f)
            {
                azzera_visitato(n_vertici,visitato);
                lng=lung_min(grafo,i,f,n_vertici,visitato);
                if(lng!=MAX_VERT+1)//se il percorso non esiste la funzione lung_min restituisce MAX_VERT+1
                {
                    printf("La distanza tra i vertici %d e %d e\' di %d\n\n",grafo[i]->key,grafo[f]->key,lng);
                    printf("\n\n");
                }
                else
                    printf("Non esiste un percorso da %d a %d!\n\n",grafo[i]->key,grafo[f]->key);
            }
}

void lista_adiacenza(int n_vertici, vertice grafo[])
{
    vertice scroll;
    int i;
    for(i=0; i<n_vertici; i++)
    {
        printf("%d : ",i);
        for(scroll=grafo[i]; scroll; scroll=scroll->next)
            printf("%d - > ",scroll->key);
        printf("NULL\n");
    }
}

int pop(vertice *testa)
{
    vertice padre=*testa;
    int key=padre->key;
    *testa=padre->next;
    free(padre);
    return key;
}

void distanze_iter(vertice grafo[],int n_vertici,int visitato[])
{
    int distanze[MAX_VERT][MAX_VERT], i, j, h, index;
    vertice testa[2],scroll;
    for(i=0; i<n_vertici; i++)//azzero tutta la matrice
        for(j=0; j<n_vertici; j++)
            distanze[i][j]=0;
            
    for(i=0; i<n_vertici; i++)//uso una vista per livello modificata
    {
        testa[0]=testa[1]=NULL;
        azzera_visitato(n_vertici,visitato);
        testa[0]=push_distanze(i,testa[0]);
        visitato[i]=1;
        for(j=0; testa[j%2]; j++)
        {
            while(testa[j%2])
            {
                h=pop(&testa[j%2]);
                distanze[i][h]=j;
                for(scroll=grafo[h]->next; scroll; scroll=scroll->next)
                {
                    index=key_to_index(grafo,n_vertici,scroll->key);
                    if(!visitato[index])
                    {
                        testa[(j+1)%2]=push_distanze(index,testa[(j+1)%2]);
                        visitato[index]=1;
                    }
                }
            }
        }
    }
    printf("ORIG\\ARRIV");
    for(i=0; i<n_vertici; i++)
        printf("%4d",grafo[i]->key);
    printf("\n\n");
    for(i=0; i<n_vertici; i++)
    {
        printf("%6d    ",grafo[i]->key);
        for(j=0; j<n_vertici; j++)
            if(distanze[i][j])
                printf("%4d",distanze[i][j]);
            else
                printf("   \\");
        printf("\n");
    }
    
}

void distanza_2_vertici(vertice *grafo,int n_vertici, int *visitato)
{
    int i,f,lng;
    printf("Inserisci il nodo di partenza: ");
    scanf("%d",&i);
    printf("Inserisci il nodo di arrivo: ");
    scanf("%d",&f);
    i=key_to_index(grafo,n_vertici,i);
    f=key_to_index(grafo,n_vertici,f);
    if(i!=n_vertici && f!=n_vertici)//se esistono
    {
        azzera_visitato(n_vertici,visitato);
        lng=lung_min(grafo,i,f,n_vertici,visitato);
        if(lng!=MAX_VERT+1)//se il percorso non esiste la funzione lung_min restituisce MAX_VERT+1
            printf("La distanza tra i vertici %d e %d e\' di %d\n\n",grafo[i]->key,grafo[f]->key,lng);
        else
            printf("Non esiste un percorso da %d a %d!\n\n",grafo[i]->key,grafo[f]->key);
    }
    else
        printf("Valori non validi!");
}

int main()
{
    vertice grafo[MAX_VERT];
    int scelta, n_vertici, visitato[MAX_VERT];
    n_vertici=crea_grafo(grafo);
    do
    {
        pulisci;
        printf("Calcolo delle distanze dei nodi di un grafo\n\n"
               "1)Crea un nuovo grafo\n"
               "2)stampa la lista d'adiacenza\n"
               "3)inserisci due nodi e calcolane la distanza\n"
               "4)stampa la distanza di tutti i nodi (funzione ricorsiva)\n"
               "5)stampa la distanza di tutti i nodi (funzione iterativa)\n"
               "0)esci\n");
        scanf("%d",&scelta);
        pulisci;
        switch(scelta)
        {
            case 1:
                n_vertici=crea_grafo(grafo);
            	 break;
            case 2:
            	 lista_adiacenza(n_vertici,grafo);
                break;
            case 3:
                distanza_2_vertici(grafo, n_vertici,visitato);
                break;
            case 4:
                azzera_visitato(n_vertici, visitato);
                distanze_ric(grafo,n_vertici,visitato);
                break;
            case 5:
                distanze_iter(grafo,n_vertici,visitato);
                break;
            case 0:
                return 0;
            default :
                printf("Scelta sbagliata");
        }
        pause();
    }
    while(1);
}

