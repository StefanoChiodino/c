/*Stefano Chiodino 39962*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#define MAX_TERMINI 101
#define MAX_RAND 101

typedef struct elemento
{
    int riga,colonna,valore;
}
termine;

void stampa_(termine matrice[])
{
    int i;
    printf("\n\n");
    for(i=1; i<=matrice[0].valore; i++)
        printf("%d x %d -> %d\n",matrice[i].riga,matrice[i].colonna,matrice[i].valore);
}

void ordina(termine matrice[])
{
    int i,j,min;
    termine park;
    for(i=1; i<=matrice[0].valore; i++)
    {
        min=i;
        for(j=i+1; j<=matrice[0].valore; j++)
            if(matrice[j].riga*matrice[0].colonna+matrice[j].colonna < matrice[min].riga*matrice[0].colonna+matrice[min].colonna)
                min=j;
        if(min!=i)
        {
            park=matrice[i];
            matrice[i]=matrice[min];
            matrice[min]=park;
        }
    }
}

void inserisci(termine matrice[])
{
     int i;
     for(i=1; i<=matrice[0].valore; i++)
    {
        do
        {
            printf("\nElemento num. %d, inserisci la riga: ",i);
            scanf("%d",&matrice[i].riga);
            printf("colonna: ");
            scanf("%d",&matrice[i].colonna);
        }
        while(matrice[i].riga > matrice[0].riga || matrice[i].colonna > matrice[0].colonna);
        //verifica se i dati inseriti sono compresi nei limiti della matrice
        printf("valore: ");
        scanf("%d",&matrice[i].valore);
    }
}

void random(termine matrice[])
{
    srand(time(NULL));
    int i,j,flag;
    for(i=1; i<=matrice[0].valore; i++)
    {
        do
        {
            matrice[i].riga=rand()%matrice[0].riga;
            matrice[i].colonna=rand()%matrice[0].colonna;
            flag=0;
            for(j=1; j<i && !flag; j++)
                if(matrice[i].riga==matrice[j].riga && matrice[i].colonna==matrice[j].colonna)
                    flag=1;
        }while(flag);
        matrice[i].valore=rand()%MAX_RAND;
    }
}
void crea(termine matrice[])
{
     int scelta;
    do
    {
        do
        {
            printf("Quanti termini fanno parte di questa matrice sparsa(max %d): ",MAX_TERMINI-1);
            scanf("%d",&matrice[0].valore);
        }
        while(matrice[0].valore > MAX_TERMINI-1);//verifica se si supera il limite di termini
        printf("\nQuante righe ha la matrice sparsa: ");
        scanf("%d",&matrice[0].riga);
        printf("\nQuante colonne ha la matrice sparsa: ");
        scanf("%d",&matrice[0].colonna);
        printf("Righe e colonne iniziano da 0\n");
    }while(matrice[0].valore>matrice[0].riga*matrice[0].colonna);//la matrice non può avere più elementi di quanti effettivamente ne può contenere
    do
    {
        printf("\nSi desirera\n"
               "1)inserire i numeri\n"
               "2)creare valore casuali\n");
        scanf("%d",&scelta);
    }while(scelta < 1 || scelta > 2);
    if(scelta == 1)
        inserisci(matrice);
    else
        random(matrice);
    stampa_(matrice);
    ordina(matrice);
    stampa_(matrice);
}

void stampa(termine a[])
{
    stampa_(a);
    int i,j,h;//h scorre l'array
    for(i=0,h=1; i<a[0].riga; i++)
    {
        for(j=0; j<a[0].colonna; j++)
            if(a[h].riga==i && a[h].colonna==j)
            {
                printf("%4d",a[h].valore);
                h++;
            }
            else
                printf("   0");
        printf("\n");
    }

}

void cerca(termine matrice[])
{
    int i,count=0,numero;//count è usato anche come flag
    printf("\nInserire il dato ricercato: ");
    scanf("%d",&numero); 
    printf("\nRicerca del numero %d\n",numero);
    for(i=1; i<=matrice[0].valore; i++)
        if(numero==matrice[i].valore)
        {
            count++;
            printf("\nIl valore e\' stato trovato a riga %d, colonna %d",matrice[i].riga,matrice[i].colonna);
        }
    if(count)
        printf("\n\nSono stati trovati %d elementi di valore %d",count,numero);
    else
        printf("\n%d non e\' presente in questa matrice",numero);
}

void trasposizione_rapida(termine matrice[])
{
    int i,park;
    for(i=1; i<=matrice[0].valore; i++)
    {
       park=matrice[i].colonna;
       matrice[i].colonna=matrice[i].riga;
       matrice[i].riga=park;
    }
    park=matrice[0].colonna;
    matrice[0].colonna=matrice[0].riga;
    matrice[0].riga=park;
    ordina(matrice);
}

void trasponi(termine matrice[],termine trasposta[])
{
    int i,j,count;
    trasposta[0].colonna=matrice[0].riga;
    trasposta[0].riga=matrice[0].colonna;
    trasposta[0].valore=matrice[0].valore;
    for(j=0, count=1; j < matrice[0].colonna; j++)
        for(i=1; i <= matrice[0].valore; i++)
            if(matrice[i].colonna == j)
            {
                trasposta[count].colonna=matrice[i].riga;
                trasposta[count].riga=matrice[i].colonna;
                trasposta[count].valore=matrice[i].valore;
                count++;
            }
    for(i=1; i <= matrice[0].valore; i++)
        matrice[i]=trasposta[i];
}

int main()
{
    int scelta,numero;
    termine matrice[MAX_TERMINI],trasposta[MAX_TERMINI];
    crea(matrice);
    do
    {
        pulisci;
        printf("Programma per la gestione delle matrici sparse\n"
               "1)stampa la matrice\n"
               "2)cerca un numero all'interno della matrice\n"
               "3)trasponi\n"
               "4)trasposizione rapida\n"
               "0)esci\n");
        scanf("%d",&scelta);
        pulisci;
        switch(scelta)
        {
            case 1:
                stampa(matrice);
                break;
            case 2:
                cerca(matrice);
                break;
            case 3:
                stampa(matrice);
                printf("\n\n");
                trasponi(matrice,trasposta);
                stampa(matrice);
                break;
            case 4:
                stampa(matrice);
                printf("\n\n");
                trasposizione_rapida(matrice);
                stampa(matrice);
                break;
            case 0:
                return 0;
            default:
                printf("\nScelta non corretta\n");
        }
        pause();
        }while(1);
    }
