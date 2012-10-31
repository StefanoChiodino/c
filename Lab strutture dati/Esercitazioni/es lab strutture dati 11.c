/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "header.h"

typedef struct ele{
        int key;
        struct ele *sx,*dx;
}*albero;

albero genera()
{
    albero tmp=(albero)malloc(sizeof(struct ele));
    char scelta;
    printf("inserire il dato: ");
    scanf("%d",&(tmp->key));
    fflush(stdin);
    printf("\n\n%d ha un figlio sinistro? (s per si,qualsiasi altro tasto per no)",tmp->key);
    scelta=getch();
    if(scelta=='s' || scelta=='S')
    {
        printf("\nFiglio sinistro ");
        tmp->sx=genera();
    }
    else
        tmp->sx=NULL;
    fflush(stdin);
    printf("\n%d ha un figlio destro? (s per si,qualsiasi altro tasto per no)",tmp->key);
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

void pesa(albero tmp, int *peso){
    if(tmp->dx){
               (*peso)++;
               pesa(tmp->dx,peso);
    }
    if(tmp->sx){
               (*peso)++;
               pesa(tmp->sx,peso);
    }
}

void visita_mod(albero tmp,int *peso){
     if(tmp){
             pesa(tmp,peso);
             visita_mod(tmp->dx,peso);
             visita_mod(tmp->dx,peso);
     }
}

int main(){
    albero radice=NULL;
    int peso=0;
    printf("Creazione dell'albero binario\n\nPrimo elemento ");
    radice=genera();
    visita_mod(radice,&peso);
    printf("\n\nLa somma dei pesi dell'albero e\' %d",peso);
    pause();
    return 0;
}
