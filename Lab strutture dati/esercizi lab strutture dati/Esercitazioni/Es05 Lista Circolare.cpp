#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define Nmax 100

int main()
{
		int v[Nmax];
		int ind=-1,n,m,i,np;

   do
   {
		printf("\nInserisci il numero di giocatori: ");
	   scanf("%d",&n);
		printf("\nInserisci il passo di eliminazione: ");
	   scanf("%d",&m);
   }
   while(n<=0 || n>Nmax || m<1);

   for(i=0; i<n; i++)
   {
		v[i]=i+1;
   	printf("  %d",v[i]);
   }

  	np=n;
   while(np)
   {
   	for(i=0;i<m;)
      {
       	ind=(ind+1)%n;
         if(v[ind]!=0) i++;
      }
         printf("\n%d ",v[ind]);
         v[ind]=0;
         np--;
   }

	fflush(stdin);
   getchar();
}



