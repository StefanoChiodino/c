/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "header.h"
#define MAX_STRING 30

typedef struct ele
{
    char key[MAX_STRING];
    struct ele *sx, *dx;
}
*albero;

int empty(albero radice)
{
    if(radice!=NULL)
        return 1;
    printf("\nL'albero e\' vuoto!\n");
    return 0;
}

int grado(albero nodo)
{
	 if(nodo->dx && nodo->sx)
	     return 2;
	 if(!nodo->dx && !nodo->sx)
	     return 0;
     return 1;
}

void cancella_cpy(albero *radice, char *key)
{
    albero scroll, padre, tmp, padre_tmp;
    for(scroll=*radice, padre=NULL; scroll!=NULL && strcmp(key,scroll->key); )//cerca l'elemento
    {
        padre=scroll;
        if(strcmp(key,scroll->key) >0)
            scroll=scroll->dx;
        else
            scroll=scroll->sx;
    }
    if(scroll)//se lo trova
    {
	    switch(grado(scroll))
	    {
		    case 0:
				if(!padre)
				    *radice=NULL;
	            else if(scroll==padre->sx)
			        padre->sx=NULL;
		        else
		            padre->dx=NULL;
                break;
            case 1:
                if(scroll->sx)//mette in tmp l'indirizzo del nodo figlio di scroll
				        tmp=scroll->sx;
				else
				        tmp=scroll->dx;
				if(!padre)
				    *radice=tmp;
	            else if(scroll==padre->sx)
			        padre->sx=tmp;
		        else
		            padre->dx=tmp;
                break;
            case 2:
				for(tmp=scroll->sx, padre_tmp=scroll; tmp->dx; padre_tmp=tmp, tmp=tmp->dx);//cerca la chiave più grande del sottoalbero sinistro
				if(padre_tmp->sx == tmp)
				    padre_tmp->sx=NULL;
				else
				    padre_tmp->dx=NULL;
                strcpy(scroll->key,tmp->key);
                scroll=tmp;
                break;
        }
                free(scroll);//cancella il nodo (nel caso del nodo di grado due cancella in realtà la foglia con cui è stata cambiata la chiave)
	}
    else
        printf("\nL'albero corrente non contiene l'elemento %s", key);
}

void cancella_merge(albero *radice, char *key)
{
    albero scroll, padre, tmp, padre_tmp;
    for(scroll=*radice, padre=NULL; scroll!=NULL && strcmp(key,scroll->key); )//cerca l'elemento
    {
        padre=scroll;
        if(strcmp(key,scroll->key) >0)
            scroll=scroll->dx;
        else
            scroll=scroll->sx;
    }
    if(scroll)//se lo trova
    {
	    switch(grado(scroll))
	    {
		    case 0:
				if(!padre)
				    *radice=NULL;
	            else if(scroll==padre->sx)
			        padre->sx=NULL;
		        else
		            padre->dx=NULL;
                break;
            case 1:
                if(scroll->sx)//mette in tmp l'indirizzo del nodo figlio di scroll
				        tmp=scroll->sx;
				else
				        tmp=scroll->dx;
				if(!padre)
				    *radice=tmp;
	            else if(scroll==padre->sx)
			        padre->sx=tmp;
		        else
		            padre->dx=tmp;
                break;
            case 2:
				for(tmp=scroll->sx, padre_tmp=scroll; tmp->dx; padre_tmp=tmp, tmp=tmp->dx);//cerca la chiave più grande del sottoalbero sinistro
				if(padre_tmp->sx == tmp)
				    padre_tmp->sx=NULL;
				else
				    padre_tmp->dx=NULL;
                tmp->sx=scroll->sx;
                tmp->dx=scroll->dx;
                break;
        }
                free(scroll);
	}
    else
        printf("\nL'albero corrente non contiene l'elemento %s", key);
}


albero ricerca_iter(albero scroll,char* key)
{
    while(scroll)
    {
        if(strcmp(scroll->key,key)>0)
            scroll=scroll->sx;
        else if(strcmp(scroll->key,key)<0)
            scroll=scroll->dx;
        else
        {
            return scroll;
        }
    }
    return NULL;
}

albero ricerca_ric(albero scroll,char* key)
{
    if(scroll)
    {
        if(strcmp(scroll->key,key)>0)
            return ricerca_ric(scroll->sx,key);
        else if(strcmp(scroll->key,key)<0)
            return ricerca_ric(scroll->dx,key);
        else
            return scroll;
    }
    return NULL;
}

albero ricerca_inserimento(albero scroll,char* key)
{
    albero app;
    while(scroll)
    {
        app=scroll;
        if(strcmp(scroll->key,key)>0)
            scroll=scroll->sx;
        else if(strcmp(scroll->key,key)<0)
            scroll=scroll->dx;
        else
        {
            printf("\n\nElemento gia\' presente!");
            return NULL;
        }
    }
    return app;
}

void inserisci(albero *radice)
{
    char key[MAX_STRING];
    albero tmp, scroll;
    do
    {
        printf("\n\nInserisci l'elemento (\"exit\" per uscire): ");
        fflush(stdin);
        gets(key);
        if(strcmp(key,"exit"))
		{
		    scroll = ricerca_inserimento(*radice, key);
		    if(scroll || !(*radice))
		    {
		        tmp = (albero)malloc(sizeof(struct ele));
		        strcpy(tmp->key,key);
		        tmp->dx=tmp->sx=NULL;
		        if(*radice)
		        {
		            if(strcmp(key,scroll->key)<0)
		                scroll->sx = tmp;
		            else
		                scroll->dx = tmp;
		        }
		        else
		            *radice = tmp;
			}
        }
    }
    while(strcmp(key,"exit"));
}

void inorder(albero tmp)
{
    if(tmp)
    {
        inorder(tmp->sx);
        printf("%s -> ",tmp->key);
        inorder(tmp->dx);
    }
}
void preorder(albero tmp)
{
    if(tmp)
    {
        printf("%s -> ",tmp->key);
        preorder(tmp->sx);
        preorder(tmp->dx);
    }
}
void postorder(albero tmp)
{
    if(tmp)
    {
        postorder(tmp->sx);
        postorder(tmp->dx);
        printf("%s -> " ,tmp->key);
    }
}

char *chiave(char key[])
{
    printf("\nInserisci la chiave: ");
    scanf("%s",key);
	return key;
}

void visita(albero radice)
{
    if(empty(radice))
    {
        printf("inorder:\n");
	    inorder(radice);
        printf("\n\npreorder:\n");
        preorder(radice);
        printf("\n\npostorder:\n\n");
        postorder(radice);
    }

}

int main()
{
    albero radice=NULL;
    int scelta;
    char key[MAX_STRING];
    while(1)
    {
        pulisci;
        printf(">>> Gestione di un albero binario <<<\n\n"
               "1)inserisci elementi\n"
               "2)visita\n"
               "3)ricerca iterativa\n"
               "4)ricerca ricorsiva\n"
               "5)cancella per copiatura\n"
               "6)cancella per fusione\n"
               "0)esci\n");
        scanf("%d",&scelta);
        pulisci;
        switch(scelta)
        {
            case 0:
		        return 0;
            case 1:
	            inserisci(&radice);
	            break;
            case 2:
		        visita(radice);
	            break;
            case 3:
	            if(ricerca_iter(radice,chiave(key)))
	                printf("\nl'elemento e\' presente nell'albero corrente");
	            else
	                printf("\nl'elemento non e\' presente nell'albero corrente");
	            break;
            case 4:
	            if(ricerca_ric(radice,chiave(key)))
	                printf("\nl'elemento e\' presente nell'albero corrente");
	            else
	                printf("\nl'elemento non e\' presente nell'albero corrente");
	            break;
            case 5:
	            cancella_cpy(&radice,chiave(key));
	            break;
            case 6:
	            cancella_merge(&radice,chiave(key));
	            break;
            default:
	            printf("\n\nScelta errata!");
        }
        pause();
    }
}
