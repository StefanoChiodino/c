/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "header.h"

typedef struct nodo
{
    int dato;
    struct nodo *sx,*dx;
}*albero;

albero genera()
{
    albero tmp=(albero)malloc(sizeof(struct nodo));
    char scelta;
    printf("inserire il dato: ");
    scanf("%d",&(tmp->dato));
    fflush(stdin);
    printf("\n\n%d ha un figlio sinistro? (s per si,qualsiasi altro tasto per no)",tmp->dato);
    scelta=getch();
    if(scelta=='s' || scelta=='S')
    {
        printf("\nFiglio sinistro ");
        tmp->sx=genera();
    }
    else
        tmp->sx=NULL;
    fflush(stdin);
    printf("\n%d ha un figlio destro? (s per si,qualsiasi altro tasto per no)",tmp->dato);
    scelta=getch();
    if(scelta=='s' || scelta=='S')
    {
        printf("\nFiglio destro ");
        tmp->dx=genera();
    }
    else
        tmp->dx=NULL;
    return tmp;    
}

void inorder(albero tmp){
     if(tmp){
             inorder(tmp->sx);
             printf("%d ",tmp->dato);
             inorder(tmp->dx);             
     }
}
void preorder(albero tmp){
     if(tmp){
             printf("%d ",tmp->dato);
             preorder(tmp->sx);
             preorder(tmp->dx);             
     }
}
void postorder(albero tmp){
     if(tmp){
             postorder(tmp->sx);
             postorder(tmp->dx);             
             printf("%d ",tmp->dato);
     }
}

int main(){
    albero radice=NULL;
    int scelta;
    printf("Creazione dell'albero binario\n\nPrimo elemento ");
    radice=genera();
    do
    {
        pulisci;
        printf("Gestione di un albero binario\n\n"
               "1)visita inorder\n"
               "2)visita preorder\n"
               "3)visita postorder\n"
               "0)esci\n");
        scanf("%d",&scelta);
        printf("\n");
        switch(scelta)
        {
            case 1:
                inorder(radice);
                break;
            case 2:
                preorder(radice);
                break;
            case 3:
                postorder(radice);
                break;
            case 0:
                return 0;
            default:
                printf("Scelta sbagliata!");
            }
     pause();
     }while(scelta);
}
