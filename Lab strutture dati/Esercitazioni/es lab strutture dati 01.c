/*Stefano Chiodino 39962*/
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int fatt_iter(int n){
	int i,fatt=1;
	for (i=2;i <= n; i++)
		fatt=fatt*i;
	return fatt;
}

int fatt_ric(int n){
	if(n==1 || n==0)
			return 1;
	else
		return n*fatt_ric(n-1);
}

int main(){
    int n,k;
    printf("Coefficente binomiale\n\n");
    do
    {
        printf("Inserisci n: ");
        scanf("%d",&n);
        if(n < 0)
            printf("n dev'essere maggiore di 0!\n");
    }while(n < 0);
    do
    {
        printf("\nInserisci k: ");
        scanf("%d",&k);
        if(k > n || k < 0)
            printf("k dev'essere maggiore di 0 e minore di n (%d)!",n);
    }while(k <0 || k > n);
    printf("\nil loro coefficente binomiale e': %d %d",fatt_ric(n)/(fatt_ric(k)*fatt_ric(n-k)),fatt_iter(n)/(fatt_iter(k)*fatt_iter(n-k)));
    pause();
    return 0;
}
