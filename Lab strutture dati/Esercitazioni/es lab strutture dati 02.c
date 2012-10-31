/*Stefano Chiodino 39962*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"
#define CIFRE 10

void converti(int base, int cifre)
{
     int i,j,h,max=pow(base,cifre);
     char tmp[CIFRE];//uso un array di char per poter convertire basi superiori al 10
     for(i=0; i<max; i++)
     {
         h=i;
         for(j=cifre-1; j>=0; j--)
         {
             tmp[j]=h%base;
             if(tmp[j] > 9)
                 tmp[j]+=55;
             else
                 tmp[j]+=48;
             h/=base;
         }
         printf("%4d:  ",i);
         for(j=0; j<cifre; j++)
             printf("%c ",tmp[j]);
         printf("\n");
     }         
}

int main(){
	int base,cifre;
	do
    {
        printf("inserisci la base: ");
	    scanf("%d",&base);
	    if(base >35)
	        printf("base troppo grande!\n");
    }while(base > 35);
	do
   {
       printf("\ninserisci il numero di cifre (max %d): ", CIFRE);
		 scanf("%d",&cifre);
   }while(cifre>CIFRE || cifre<1);
	converti(base,cifre);
	pause();
	return 0;
}
