#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define MAX 20
#define M 5

void quick_sort(float a[], int, int);
int perno(float a[], int, int);
void scambia(float*, float*);
void inserzione(float a[], int primo, int ultimo);

main() {
float a[MAX];
int n=0,i;

	printf("\n\tInserire il numero di elementi -> ");
	scanf("%d", &n);
	for(i=0;i<n;i++) {
		printf("\ta[%2d]: ",i);
		scanf("%f", &a[i]);
	}

	printf("\n\tVettore: ");

	for(i=0;i<n;i++)
	 	printf("%.2f ",a[i]);

	quick_sort(a,0,n-1);

	printf("\n\tVettore ordinato: ");
	for(i=0;i<n;i++)
		printf("%.2f ",a[i]);

	fflush(stdin);
	getchar();
}

void quick_sort(float a[], int u, int v) {
int p;
	if((v-u)<= M) inserzione(a,u,v);
	p=perno(a,u,v);
	if(u<p) quick_sort(a,u,p-1);
	if(p<v) quick_sort(a,p+1,v);
}

int perno(float a[], int primo, int ultimo) {
int i=primo, j=ultimo+1, pivot=a[primo];

	do	{
		do i++; while(a[i]<pivot && i<j);
		do j--; while(a[j]>pivot && j>primo);
		if(i<j) scambia(&a[i],&a[j]);
	}
	while(i<j);
	scambia(&a[primo],&a[j]);
	return j;
}


void scambia(float *a1, float *a2) {
float park;
	park=*a1;
	*a1=*a2;
	*a2=park;
}

void inserzione(float a[],int primo,int ultimo) {
int i,j,prossimo;

	for(i=primo;i<ultimo;i++) {
		prossimo=a[i];
		for(j=i-1;j>=primo && prossimo<a[j];j--)
			a[j+1]=a[j];
		a[j+1]=prossimo;
	}
}
