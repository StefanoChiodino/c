#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

void combinazioni(int, int);
void converti(int, int);

int main()
{
		int b, n;

	printf("\n\t\t\tSistemi di numrazione");

	printf("\n\nInserire la base: ");
   scanf("%d",&b);

	printf("Inserire il numero di cifre: ");
   scanf("%d",&n);

   printf("\nNumeri in base %d con max %d cifre.\n",b,n);
	combinazioni(b,n);

	fflush(stdin);
   getchar();
}

void combinazioni(int b, int n)
{
		int i;

	for(i=0; i<pow(b,n); i++)
   {
      converti(i,b);
      printf(" - ");
   }
}

void converti(int num, int b)
{
	int r=num%b;

   if(num<b) printf("%d",r);
   else
   {
		converti(num/b,b);
    	printf("%d",r);
   }
}




