/*Stefano Chiodino 39962*/
#include <stdio.h>
#include "header.h"
#define MAX_SIZE  100

void crea(int * giocatori, int * salto, int * coda){
     int i;
     do{
         printf("Quante persone partecipano alla competizione (da 1 a %d): ",MAX_SIZE-1);
            scanf("%d",giocatori);
     }while(*giocatori<0 || *giocatori >MAX_SIZE);
     do{
        printf("A quanto equivale il passo: ");
        scanf("%d",salto);
     }while(*salto<0 || *salto>=*giocatori);
     
     for(i=0; i<*giocatori; i++)
                              *(coda+i)=i+1;                                    
}

int eliminazione(int giocatori, int salto, int coda[]){
    int i=salto-1, j=giocatori,h;
    printf("\nSequenza delle eliminazioni:\n");
    while(j > 1){
                    if(coda[i]){
                                  printf("%4d",coda[i]);
                                  coda[i]=0;
                                  j--;
                                  for(h=salto;h>0;){
                                                    i=(i+1)%giocatori;
                                                    if(coda[i])
                                                               h--;
                                  }
                    }
                    else
                        i=(i+1)%giocatori;
    }
    
    return coda[i];
}

int main(){
    int giocatori,salto,coda[MAX_SIZE];
    crea(&giocatori,&salto,coda);
    printf("\nIl vincitore e' il giocatore %d",eliminazione(giocatori,salto,coda));
    pause();
    return 0;
}
