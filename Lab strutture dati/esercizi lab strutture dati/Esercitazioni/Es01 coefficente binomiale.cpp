#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


int fact(int);
int coefbinit(int, int);
int coefbinric(int, int);

void main()
{
		int n,k;


	printf("\n\t\t  Calcolo del coefficente binomiale (N su K)\n\n");

   do {
	   printf("\nInserire il numero di elementi N: ");
	   scanf("%d",&n);
		printf("Inserire il numero di gruppi K (k<n): ");
	   scanf("%d",&k);
   }
   while(n<k);

   printf("\n\nVersione Iterativa.\nIl coefficente binomiale di %d elementi su %d gruppi e' %d\n",n,k,coefbinit(n,k));
   printf("\n\nVersione Ricorsiva.\nIl coefficente binomiale di %d elementi su %d gruppi e' %d",n,k,coefbinric(n,k));

	fflush(stdin);
   getchar();
}

int fact(int n)
{
	if(n==0) return(1);
   return(n*fact(n-1));
}

int coefbinit(int n, int k)
{
  return(fact(n)/(fact(k)*fact(n-k)));
//  return(fact(k)/fact(n-k));
}

int coefbinric(int n, int k)
{
	if(n==k || k==0) return(1);
	return(coefbinric(n-1,k)+coefbinric(n-1,k-1));
}

