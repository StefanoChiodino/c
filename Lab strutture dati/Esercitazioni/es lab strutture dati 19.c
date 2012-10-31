/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "header.h"
#define MAX_ARRAY 200
#define MAX_RAND 100
#define M 5

int crea_vettore(int *vettore)
{
    int n_elementi,i;
    char scelta;
    do
	{
        printf("Quanti elementi fanno parte del vettore (max %d)?\n",MAX_ARRAY);
    	scanf("%d",&n_elementi);
	}while(n_elementi < 1 || n_elementi > MAX_ARRAY);
    do
    {
        fflush(stdin);
        printf("\npremere i per inserire gli elementi manualmente, r per inserire elementi random");
        scelta=getch();
    }
    while(scelta!='r' && scelta!='R' && scelta!='i' && scelta!='I');
    if(scelta=='r' || scelta=='R')
    {
        srand(time(NULL));
        for(i=0; i<n_elementi; i++)
            vettore[i]=rand()%MAX_RAND;
    }
    else if(scelta=='i' || scelta=='I')
    {
        for(i=0; i<n_elementi; i++)
        {
            printf("\ninserisci l'elemento numero %d: ",i+1);
            scanf("%d",&vettore[i]);
        }
    }
    return n_elementi;
}

void stampa(int *vettore,int n_elementi)
{
    int i;
    for(i=0; i<n_elementi; i++)
        printf("%4d",vettore[i]);
}

void scambia(int *a, int *b, int *park)
{
    *park=*a;
    *a=*b;
    *b=*park;
}


void inserzione(int *vettore,int elementi)
{
    int i,j,tmp;
    for(i=0; i<elementi; i++)
    {
        tmp=vettore[i];
        for(j=i-1; j>=0 && tmp<vettore[j]; j--)
            vettore[j+1]=vettore[j];
        vettore[j+1]=tmp;
    }
}

void check(int *vettore,int n)
{
 	while(--n)
 	    if(vettore[n] < vettore[n-1])
 	    {
 		    printf("\n\n\n\tFAILED");
 		    return;
		}
    printf("\n\n\n\tOK");
}

void quicksort_inserzione(int *vettore, int primo, int ultimo)
{
    int pivot, i, j, park;
    if(ultimo-primo < M)
        inserzione(vettore+primo, ultimo+1-primo);
    else
    {
        pivot=vettore[primo];
	 	printf("\npivot=%d, primo=%d, ultimo=%d\n",pivot,primo,ultimo);
        i=primo;
        j=ultimo+1;
        do
        {
	  	   stampa(vettore+primo,ultimo+1-primo);
		   while(vettore[++i]<pivot);
		   while(vettore[--j]>pivot);
 		   if(i < j)
		   {
		   	   printf("  %d[%d] -> %d[%d]",vettore[i],i,vettore[j],j);
 		       scambia(vettore+i, vettore+j, &park);
		   }
		   printf("\n");
 		}while(i < j);
 		scambia(vettore+primo, vettore+j, &park);
        stampa(vettore+primo,ultimo+1-primo);
        printf("\n");

 		quicksort_inserzione(vettore,primo,j-1);
 		quicksort_inserzione(vettore,j+1,ultimo);
	}
}

void quicksort(int *vettore, int primo, int ultimo)
{
    int pivot, i, j, park;
    if(primo<ultimo)
    {
        pivot=vettore[primo];
	 	printf("\npivot=%d, primo=%d, ultimo=%d\n",pivot,primo,ultimo);
        i=primo;
        j=ultimo+1;
        do
        {
	  	   stampa(vettore+primo,ultimo+1-primo);
		   while(vettore[++i]<pivot);
		   while(vettore[--j]>pivot);
 		   if(i < j)
		   {
		   	   printf("  %d[%d] -> %d[%d]",vettore[i],i,vettore[j],j);
 		       scambia(vettore+i, vettore+j, &park);
		   }
		   printf("\n");
 		}while(i < j);
 		scambia(vettore+primo, vettore+j, &park);
        stampa(vettore+primo,ultimo+1-primo);
        printf("\n");

 		quicksort(vettore,primo,j-1);
 		quicksort(vettore,j+1,ultimo);
	}
}

int main()
{
    int vettore[MAX_ARRAY],n_elementi,scelta;
    printf("Ordinamento di un vettore tramite quicksort!\n\n");
    
    n_elementi=crea_vettore(vettore);
    pulisci;
    
    stampa(vettore,n_elementi);
    pause();
    
    do
	{
		printf("Ordinare il file con:\n\n"
	           "1)Quicksort ricorsivo\n"
	           "2)Quicksort ed inserzione\n");
	    scanf("%d",&scelta);
	}while(scelta<1 || scelta > 2);
    if(scelta==1)
        quicksort(vettore,0,n_elementi-1);
    else
        quicksort_inserzione(vettore,0,n_elementi-1);
    pause();
    pulisci;
    stampa(vettore,n_elementi);
    check(vettore,n_elementi);
    pause();
    return 0;
}
