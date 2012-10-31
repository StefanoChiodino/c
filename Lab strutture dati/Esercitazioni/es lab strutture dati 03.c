/*Stefano Chiodino 39962*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#define dim 30
#define max 100

void random(int A[][dim],int B[][dim],int colonne1,int righe1,int colonne2,int righe2){
     srand(time(NULL));
     int i,j;
     for(i=0;i<righe1;i++)
                     for(j=0;j<colonne1;j++){
                                      A[i][j]=rand()%max;
                     } 
     for(i=0;i<righe2;i++)
                     for(j=0;j<colonne2;j++){
                                      B[i][j]=rand()%max;
                     }
}

void riempi(int A[][dim],int B[][dim],int colonne1,int righe1,int colonne2,int righe2){
     int i,j;
     for(i=0;i<righe1;i++)
                     for(j=0;j<colonne1;j++){
                                      printf("inserisci A[%d][%d]: ",i,j);
                                      scanf("%d",&A[i][j]);
                     }         
     for(i=0;i<righe2;i++)
                     for(j=0;j<colonne2;j++){
                                      printf("inserisci B[%d][%d]: ",i,j);
                                      scanf("%d",&B[i][j]);
                     }         
}

void somma(int A[][dim],int B[][dim],int C[][dim],int colonne1,int righe1,int colonne2,int righe2){
     if(righe1==righe2 && colonne1==colonne2){
         int i,j;
         for(i=0;i<righe1;i++)
                         for(j=0;j<colonne1;j++)
                                         C[i][j]=B[i][j]+A[i][j];
     }
     else
         printf("\nsu queste matrici non si possono operare somme");
}

void differenza(int A[][dim],int B[][dim],int C[][dim],int colonne1,int righe1,int colonne2,int righe2){
     if(righe1==righe2 && colonne1==colonne2){
         int i,j;
         for(i=0;i<righe1;i++)
                         for(j=0;j<colonne1;j++)
                                         C[i][j]=A[i][j]-B[i][j];
                                         
     }
     else
         printf("\nsu queste matrici non si possono operare differenze");
}

void prodotto(int A[][dim],int B[][dim],int C[][dim],int colonne1,int righe1,int colonne2,int righe2){
     if(righe1==colonne2 && righe2==colonne1)
     {
         int i,j,h;
         for(i=0;i<righe1;i++)
             for(h=0;h<colonne2;h++)
  		         C[i][h]=0;

	      for(i=0;i<righe1;i++)
	          for(h=0;h<colonne2;h++)
	  	          for(j=0;j<colonne1;j++)
  		              C[i][h]+=(A[i][j]*B[j][h]);
     }
     else
         printf("\nsu queste matrici non si possono operare prodotti");
}

void trasposizione(int A[][dim],int B[][dim],int colonne1,int righe1,int colonne2,int righe2){
     int i,j,tmp;
     for(i=0;i<colonne1;i++)
                     for(j=i+1;j<righe1;j++){
                                      tmp=A[i][j];
                                      A[i][j]=A[j][i];
                                      A[j][i]=tmp;
                     }
     for(i=0;i<colonne2;i++)
                     for(j=0;j<righe2;j++){
                                      tmp=B[i][j];
                                      B[i][j]=B[j][i];
                                      B[j][i]=tmp;
                     }                                                                          
}

void stampa(int A[][dim],int colonne,int righe){
     printf("\n\n");
     int i,j;
          for(i=0;i<righe;i++){
                     for(j=0;j<colonne;j++)
                                     printf("%7d",A[i][j]);
                     printf("\n");
     }
}


int main(){
    int A[dim][dim],B[dim][dim],i,j,C[dim][dim],colonne1,righe1,colonne2,righe2;
    //dimensione delle matrici
    printf("Programma per la gestione di matrici");
    printf("\n Le matrici devono essere:\n"
           "- di pari righe e colonne per operare differenze ed addizioni\n"
           "- le righe dell'una devono corrispondere alle colonne dell'altra per i prodotti\n"
           "- di qualsiasi dimensione per le trasposizioni\n\n"
           "Inserisci la dimensione della prima matrice\n"
           "colonne: ");
    scanf("%d",&colonne1);
    printf("righe: ");
    scanf("%d",&righe1);
    printf("\nInserisci la dimensione della seconda matrice\n"
           "colonne: ");
    scanf("%d",&colonne2);
    printf("righe: ");
    scanf("%d",&righe2);  
    //riempimento delle matrici 
    do
    {
        printf("\nSi desidera\n"
               "1)creare due matrici random\n"
               "2)riempire le matrici manualmente?\n");
        scanf("%d",&i);
        switch(i){
                  case 1:
                       random(A,B,colonne1,righe1,colonne2,righe2);
                       break;
                  case 2:
                       riempi(A,B,colonne1,righe1,colonne2,righe2);
                       break;
                  default:
                          printf("\nhai sbagliato selezione");
        }
    }while(i<1 || i>2);
    stampa(A,colonne1,righe1);stampa(B,colonne2,righe2);
    //menu
    do
    {
        printf("\n\nSi desidera\n"
               "1)sommare le matrici\n"
               "2)sottrarre B da A\n"
               "3)fare il prodotto delle matrici\n"
               "4)trasporre le matrici\n");
        scanf("%d",&i);
        switch(i){
                  case 1:
                       somma(A,B,C,colonne1,righe1,colonne2,righe2);
                       stampa(C,colonne1,righe1);
                       break;
                  case 2:
                       differenza(A,B,C,colonne1,righe1,colonne2,righe2);
                       stampa(C,colonne1,righe1);
                       break;
                  case 3:
                       prodotto(A,B,C,colonne1,righe1,colonne2,righe2);
                       stampa(C,colonne1,righe1);
                       break;
                  case 4:
                       trasposizione(A,B,colonne1,righe1,colonne2,righe2);
                       i=colonne1;
                       colonne1=righe1;
                       righe1=i;
                       i=colonne2;
                       colonne2=righe2;
                       righe2=i;
                       stampa(A,colonne1,righe1);stampa(B,colonne2,righe2);
                       break;
                  default:
                          printf("\nhai sbagliato selezione");
        }
    }while(i<1 || i>4);
    pause();
    return 0;
}
