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

void push(vertice elemento,int vert)
{
    vertice nuovo=(vertice)malloc(sizeof(struct nodo));
    nuovo->next=elemento->next;
    nuovo->key=vert;
    elemento->next=nuovo;
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
                    push(grafo[i],h);
                }
                else
                    printf(">>> Vertice gia\' connesso!\n\a");
            }
            else
                printf(">>> Vertice inesistente!\n\a");
        }
    }
    return n_vertici;
}

void azzera_visitato(int n_vertici, int visitato[])
{
    while(n_vertici)
        visitato[--n_vertici]=0;
}

int cammino(vertice grafo[], int visitato[],int index, int n_vertici)
{
    int n;
    vertice scroll=grafo[index]->next;
    visitato[index]=1;
    for(n=0; scroll; scroll=scroll->next)
    {
        index=key_to_index(grafo, n_vertici, scroll->key);
        if(!visitato[index])
        {
            n++;
            n+=cammino(grafo,visitato,index,n_vertici);
        }
    }
    return n;
}

void cammino_orientato(vertice grafo[],int n_vertici,int visitato[])
{
    int i;
    for(i=0; i<n_vertici; i++)
    {
        azzera_visitato(n_vertici,visitato);
        printf("Dal vertice %d sono raggiungibili %d vertici\n\n",grafo[i]->key,cammino(grafo,visitato,i,n_vertici));
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

int main()
{
    vertice grafo[MAX_VERT];
    int n_vertici, visitato[MAX_VERT];
    n_vertici=crea_grafo(grafo);
    pulisci;
    
    lista_adiacenza(n_vertici,grafo);
    pause();
    pulisci;
    
    cammino_orientato(grafo,n_vertici,visitato);
    pause();
    return 0;
}

