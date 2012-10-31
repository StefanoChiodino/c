#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


#define MAX	3
#define RMAX 50
#define CMAX 50


void getdim(int *, int *);
void generamat(int , int, int [][CMAX]);
void somma(int [][CMAX], int [][CMAX], int [][CMAX], int, int, int);
void prodotto(int [][CMAX], int, int, int [][CMAX], int, int, int [][CMAX]);
void trasponi(int [][CMAX], int, int, int [][CMAX]);
void printm(int, int, int m[][CMAX]);


int main() {
char s;
int a[RMAX][CMAX], b[RMAX][CMAX],ris[RMAX][CMAX];
int row,col,row2,col2;


	do {
      printf("\n\t\tOPERAZIONI SULLE MATRICI\n\n");
   	printf("\n1- Somma matrici");
   	printf("\n2- Differenza matrici");
   	printf("\n3- Moltiplicazione matrici");
   	printf("\n4- Trasponi matrice");
      printf("\n0- Esci");
      printf("\n\nScelta: ");
      scanf("%c",&s);


      switch(s) {
      	case '1': {
         	printf("\nSOMMA");
            printf("\n- Le dimensioni delle matrici per la somma devono essere uguali.\n- Verranno richieste solo una volta");
            getdim(&row,&col);

            generamat(row,col,a);
            printf("\n\nMATRICE GENERATA\n");
            printm(row,col,a);

            generamat(row,col,b);
            printf("\n\nMATRICE GENERATA\n");
            printm(row,col,b);

            somma(a,b,ris,row,col,1);
            printf("\n\nMATRICE SOMMA\n");
            printm(row,col,ris);
            break;
         }
      	case '2': {
         	printf("\nDIFFERENZA");
            printf("\n- Le dimensioni delle matrici per la differenza devono essere uguali.\n- Verranno richieste solo una volta");
            getdim(&row,&col);

            generamat(row,col,a);
            printf("\n\nMATRICE GENERATA\n");
            printm(row,col,a);

            generamat(row,col,b);
            printf("\n\nMATRICE GENERATA\n");
            printm(row,col,b);

            somma(a,b,ris,row,col,-1);
            printf("\n\nMATRICE DIFFERENZA\n");
            printm(row,col,ris);
            break;

         }
      	case '3': {
         	printf("\nPRODOTTO");
            do {
            	printf("\n\nIL NUMERO COLONNE DEL I FATTORE DEVE ESSERE \nUGUALE AL NUM RIGHE DEL II FATTORE	\n");
	            getdim(&row,&col);
   	         getdim(&row2,&col2);
            }
            while(col!=row2);


            generamat(row,col,a);
            printf("\n\nMATRICE GENERATA\n");
            printm(row,col,a);


            generamat(row2,col2,b);
            printf("\n\nMATRICE GENERATA\n");            
            printm(row2,col2,b);

            prodotto(a,row,col,b,row2,col2,ris);
            printf("\n\nMATRICE PRODOTTO\n");
            printm(row,col2,ris);

            break;
         }
      	case '4': {
         	printf("\nTRASPOSTA");
            getdim(&row,&col);
            row2=col; col2=row;

            generamat(row,col,a);
            printf("\n\nMATRICE GENERATA\n");
            printm(row,col,a);

            trasponi(a,row,col,ris);
            printf("\n\nMATRICE TRASPOSTA\n");
            printm(row2,col2,ris);


            break;
         }
      }

		fflush(stdin);
	   getchar();
   }
   while(s!='0');

}



void printm(int r, int c, int m[][CMAX]) {
int i,j;

	for(i=0;i<r;i++) {
   	for(j=0;j<c;j++)
      	printf(" %3d",m[i][j]);
      printf("\n");
   }



}



void getdim(int *r, int *c) {

	printf("\n\nAcquisizione dimensioni matrice");

   do {
   	printf("\n\nNumero Righe: ");
      scanf("%d",r);

		printf("\nNumero Colonne: ");
      scanf("%d",c);

   }
   while(*r<=0 || *r>RMAX || *c<=0 || *c>CMAX);


}


void generamat(int r, int c, int m[][CMAX]) {
int i,j;


	for(i=0;i<r;i++)
   	for(j=0;j<c;j++)
      	m[i][j]=rand()%MAX;

}


void somma(int a[][CMAX], int b[][CMAX], int s[][CMAX], int r, int c, int op) {

int i,j;

	for(i=0;i<r;i++)
   	for(j=0;j<c;j++)
      	if(op==1)
	      	s[i][j]=a[i][j]+b[i][j];
         else
				s[i][j]=a[i][j]-b[i][j];
}



void prodotto(int a[][CMAX], int row, int col, int b[][CMAX], int row2, int col2, int ris[][CMAX] ) {
int i,j,k;

	for(i=0;i<row;i++)
   	for(j=0;j<col2;j++)
      	ris[i][j]=0;


	for(i=0;i<row;i++)
	  for(k=0;k<col2;k++)
	  	for(j=0;j<col;j++)
  		 ris[i][k]+=(a[i][j]*b[j][k]);



}


void trasponi(int a[][CMAX], int row, int col, int ris[][CMAX]) {
int i,j;

	for(i=0;i<row;i++)
   	for(j=0;j<col;j++)
      	ris[j][i]=a[i][j];

}
