/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define MAX_STRING 20

typedef struct alb
{
        char key;
        struct alb *sx,*dx;
}*albero;

typedef struct ele
{
    albero link;
    struct ele *next;
}*coda;

coda push(albero link, coda testa)
{
    coda tmp=(coda)malloc(sizeof(struct ele));
    tmp->link=link;
    tmp->next=testa;
    return tmp;
}

albero pop(coda *testa)
{
    albero tmp1=(*testa)->link;
    coda tmp2=(*testa);
    (*testa)=(*testa)->next;
    free(tmp2);
    return tmp1;    
}

albero crea_nodo(char a)
{
	albero tmp=(albero)malloc(sizeof(struct alb));
	tmp->key=a;
	tmp->sx=tmp->dx=NULL;
	return tmp;
}

albero crea_albero(char *espressione)
{
    coda testa=NULL;
    albero radice=NULL;
    int i;
    for(i=0; espressione[i]!='\0'; i++)
    {
        if(espressione[i]=='*' || espressione[i]=='/' || espressione[i]=='+' || espressione[i]=='-')
        {
	        radice=crea_nodo(espressione[i]);
	        radice->sx=pop(&testa);
	        radice->dx=pop(&testa);
            testa=push(radice,testa);
        }
        else
            testa=push(crea_nodo(espressione[i]),testa);
    }
    return radice;
}

void inorder(albero tmp)
{
     if(tmp)
     {
             inorder(tmp->sx);
             printf("%c ",tmp->key);
             inorder(tmp->dx);             
     }
}
void preorder(albero tmp)
{
     if(tmp)
     {
             printf("%c ",tmp->key);
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
             printf("%c ",tmp->key);
     }
}

void visita(albero radice)
{
         printf("Inorder:\t");
         inorder(radice);
         printf("\nPreorder:\t");
         preorder(radice);
         printf("\nPostorder:\t");
         postorder(radice);
}

int main(int argc, char *argv[]){
    albero radice;
    if(argv[1])
               radice=crea_albero(argv[1]);
    else
    {
         char stringa[MAX_STRING];
         printf("Inserisci l'operazione postfissa: ");
         scanf("%s",stringa);
         radice=crea_albero(stringa);         
    }
    visita(radice);
    pause();
    return 0;
}
