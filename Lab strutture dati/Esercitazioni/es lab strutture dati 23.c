/*
Stefano Chiodino 39962

Il tempo di ordinamento per inserzione e selezione richiede tantissimo tempo per
agire su una lista della massima grandezza specialmente dato che si ripete il processo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "header.h"
#define MAX 25000//dimensione array  ######## Per liste molto grandi alcune funzioni potrebbero essere piuttosto instabili ######
#define MAX_CIFRE 5
#define RADICE_SIZE 10
#define PASSO_INSER 5//dimensione lista min per cui mergensort_inser e quicknsort_inser passano la sottolista alla funzione di inserzione
#define RIPETIZIONI 5// numero di volte che esegue gli algoritmi per determinarne il tempo di esecuzione

typedef struct ele
{
    int key[MAX_CIFRE];
    struct ele *next;
}
*lista;

int numero()
{
    int elementi;
    do
    {
        printf("Inserire il numero di elementi (max %d): ",MAX);
        scanf("%d",&elementi);
    }
    while(elementi > MAX || elementi < 2);
    return elementi;
}

int crea(int elementi, char *ordine, int lista[])
{
    int scelta,i;
    srand(time(NULL));
    do
    {
        printf("Scegliere il tipo di ordinamento:\n\n"
               "1)ordinato\n"
               "2)quasi ordinato\n"
               "3)casuale\n"
               "4)inversamente ordinato\n");
        scanf("%d",&scelta);
        switch(scelta)
        {
            case 1:
                for(i=0; i<elementi; i++)
                    lista[i]=i;
                strcpy(ordine,"ordinat1");
                break;
            case 2:
    				 for(i=0; i<MAX; i++)
        			 lista[i]=i+rand()%50;
                strcpy(ordine,"quasi ordinat1");
                break;
            case 3:
                for(i=0; i<elementi; i++)
                    lista[i]=rand()%MAX;
                strcpy(ordine,"casuali");
                break;
            case 4:
                for(i=0; elementi>=0; i++, elementi--)
                    lista[i]=elementi;
                strcpy(ordine,"inversamente ordinati");
                break;
            default:
                printf("Scelta sbagliata!\n\n");
        }
    }
    while(scelta<1 || scelta > 4);
    return scelta;
}

void check(int lista[],int elementi)
{
    int i;
    for(i=1; i<elementi; i++)
        if(lista[i]<lista[i-1])
        {
            printf("FAILED   (%d [%d] > %d [%d])", lista[i-1], i-1 , lista[i], i);
            return;
        }
    printf("    ok");
}

void stampa(int lista[],int elementi)
{
    int i;
    for(i=0; i<elementi; i++)
        printf("%d, ",lista[i]);
    printf("\n\n",lista[i]);
}

void copia(int lista[],int copia[],int elementi)
{
    for(elementi--; elementi >=0 ;elementi--)
        copia[elementi]=lista[elementi];
}

void scambia(int *a, int *b, int *park)
{
    *park=*a;
    *a=*b;
    *b=*park;
}

void check_dinamic(lista scroll)
{
    int i;
    while(scroll->next)
    {
        for(i=0; i<MAX_CIFRE && (scroll->key[i]) >= (scroll->next->key[i]); i++) //si ferma quando trova una cifra in scroll->key partendo dalle più significative
        {
            if((scroll->key[i]) > (scroll->next->key[i]))
            {
                printf("FAILED");
                return;
            }
        }
        scroll=scroll->next;
    }
    printf("    ok");
}

/*###################################################################################################################
#####################################################################################################################
           								  Funzioni di ordinamento
#####################################################################################################################
###################################################################################################################*/
//Inserzione
void inserzione(int *vettore,int ultimo)
{
    int i,j,prossimo;

    for(i=1; i<ultimo; i++)
    {
        prossimo=vettore[i];
        for(j=i-1; j>=0 && prossimo<vettore[j]; j--)
            vettore[j+1]=vettore[j];
        if(i!=j+1)
        vettore[j+1]=prossimo;
    }
}

//Quick sort
void quicksort_inserzione(int *vettore, int primo, int ultimo)
{
    int pivot, i, j, park;
    if(ultimo-primo < PASSO_INSER)
        inserzione(vettore+primo, ultimo+1-primo);
    else
    {
        pivot=vettore[primo];
        i=primo;
        j=ultimo+1;
        do
        {
            while(vettore[++i]<pivot);
            while(vettore[--j]>pivot);
            if(i < j)
                scambia(vettore+i, vettore+j, &park);
        }
        while(i < j);
        scambia(vettore+primo, vettore+j, &park);
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
        i=primo;
        j=ultimo+1;
        do
        {
            while(vettore[++i]<pivot);
            while(vettore[--j]>pivot);
            if(i < j)
                scambia(vettore+i, vettore+j, &park);
        }
        while(i < j);
        scambia(vettore+primo, vettore+j, &park);
        quicksort(vettore,primo,j-1);
        quicksort(vettore,j+1,ultimo);
    }
}

//Merge sort
void mergensort_inser(int *vettore, int *tmp, int elementi)
{
    int passo = PASSO_INSER;
    int i, j, k, medio, fine, *park;
    for(i=0; i<elementi-PASSO_INSER; i+=PASSO_INSER)
        inserzione(vettore+i, PASSO_INSER);
    inserzione(vettore+i, elementi-i);
    do//ciclo per aumentare il passo
    {
        for(k=0; k < elementi;)//ciclo per scorrere la lista e fondere i sottofile
        {
            medio=k+passo;
            fine=passo*2+k;
            if(medio>elementi)
                medio=fine=elementi;
            else if(fine>elementi)
                fine=elementi;
            for(i=k, j=medio; i < medio && j < fine;)
            {
                if(vettore[i] <= vettore[j])
                    tmp[k++]=vettore[i++];
                else
                    tmp[k++]=vettore[j++];
            }
            while(i<medio)
                tmp[k++]=vettore[i++];
            while(j<fine)
                tmp[k++]=vettore[j++];
        }
        park=tmp;//scambio la lista originale con quella appena ordinata
        tmp=vettore;
        vettore=park;
        passo*=2;//raddoppio il passo
    }
    while(passo < elementi*2);
}

void mergensort_iter(int *vettore, int *tmp, int elementi)
{
    int passo=1, i, j, k, medio, fine;
    int *park;
    do//ciclo per aumentare il passo
    {
        for(k=0; k < elementi;)//ciclo per scorrere la lista e fondere i sottofile
        {
            medio = k+passo;
            fine = passo*2+k;
            if(medio > elementi)
                medio = fine = elementi;
            else if(fine > elementi)
                fine = elementi;
            for(i=k, j=medio; i < medio && j < fine; )
            {
                if(vettore[i] <= vettore[j])
                    tmp[k++]=vettore[i++];
                else
                    tmp[k++]=vettore[j++];
            }
            while(i<medio)
                tmp[k++]=vettore[i++];
            while(j<fine)
                tmp[k++]=vettore[j++];
        }
        park=tmp;//scambio la lista originale con quella appena ordinata
        tmp=vettore;
        vettore=park;
        passo*=2;//raddoppio il passo
    }
    while(passo < elementi*2);
}

//Heap sort
void adatta(int *vettore,int padre,int size)
{
    int figlio, key;
    key=vettore[padre];
    figlio=2*padre;//figlio sinistro
    while(figlio<=size)
    {
        if((figlio<size) && vettore[figlio] < vettore[figlio+1] )//si sposta al figlio dx se è più grande
            figlio++;
        if(key < vettore[figlio])//se il padre è più piccolo del maggiore dei figli
        {
            vettore[figlio/2]=vettore[figlio];
            figlio*=2;
        }
        else
            break;
    }
    vettore[figlio/2]=key;
}

void heap_sort(int *vettore,int size)
{
    int i, park;
    vettore--;//cosi vettore[0] diventa vettore[1]
    for(i=size/2; i>0; i--)//adatta tutti i nodi i tali che 0<i<n/2 (non foglie)
        adatta(vettore,i,size);
    for(i=size; i>0; )//scambia il primo e l'ultimo elemento e riadatta il nuovo vettore escludendo gli elementi messi alla fine (già ordinati)
    {
        park=vettore[1];
        vettore[1]=vettore[i];
        vettore[i]=park;
        adatta(vettore,1,--i);
    }
}

//Radix sort
lista push(lista testa, int key)
{
    lista tmp;
    int i;
    tmp=(lista)malloc(sizeof(struct ele));
    for(i=MAX_CIFRE-1; i>=0; i--)
    {
        tmp->key[i]=key%10;
        key/=10;
    }
    tmp->next=testa;
    testa=tmp;
    return testa;
}

lista static_to_dinamic(int vettore[], lista testa, int elementi)
{
    int i;
    for(i=1; i<=elementi; i++)
        testa=push(testa,vettore[i]);
    return testa;
}

lista radix(lista scroll)
{
    lista davanti[RADICE_SIZE],dietro[RADICE_SIZE];
    int i,j,cifra;
    for(i=MAX_CIFRE-1;i>=0;i--)
    {
        for(j=0;j<RADICE_SIZE;j++)
            davanti[j]=dietro[j]=NULL;

        while(scroll)
        {
            cifra=scroll->key[i];
            if(!davanti[cifra])
                davanti[cifra]=scroll;
            else
                dietro[cifra]->next=scroll;

            dietro[cifra]=scroll;
            scroll=scroll->next;
        }

        scroll=NULL;
        for(j=RADICE_SIZE-1;j>=0;j--)
            if(davanti[j])
            {
                dietro[j]->next=scroll;
                scroll=davanti[j];
            }
    }
    return scroll;
}

lista empty(lista scroll)
{
    lista tmp;
    while(scroll)
    {
        tmp=scroll;
        scroll=scroll->next;
        free(tmp);
    }
    return NULL;
}

//Selezione
void selezione(int lista[],int elementi)
{
    int i,j,min,park;
    for(i=0; i<elementi; i++)
    {
        min=i;
        for(j=i+1; j<=elementi; j++)
            if(lista[j]<lista[min])
                min=j;
        if(min!=i)
        {
            park=lista[i];
            lista[i]=lista[min];
            lista[min]=park;
        }
    }
}

/*###################################################################################################################
#####################################################################################################################
             Queste funzioni sono modificate per cnoscere il numero di confronti e scambi
#####################################################################################################################
###################################################################################################################*/
//Inserzione
void inserzione_count(int *vettore,int ultimo, unsigned long int *confronti, unsigned long int *scambi)
{
    int i,j,prossimo;
    for(i=1; i<ultimo; i++)
    {
        prossimo=vettore[i];
        for(j=i-1; j>=0 && prossimo<vettore[j]; j--, (*confronti)++, (*scambi)++)
            vettore[j+1]=vettore[j];
        (*confronti)++;//per l'ultimo confronto di for
        if(i!=j+1)
        {
		    vettore[j+1]=prossimo;
            (*scambi)++;
        }
    }
}

//Quick sort
void quicksort_inserzione_count(int *vettore, int primo, int ultimo, unsigned long int *confronti, unsigned long int *scambi)
{
    int pivot, i, j, park;
    if(ultimo-primo < PASSO_INSER)
        inserzione_count(vettore+primo, ultimo+1-primo,confronti, scambi);
    else
    {
        pivot=vettore[primo];
        i=primo;
        j=ultimo+1;
        do
        {
            for(; vettore[++i]<pivot; (*confronti)++);
            (*confronti)++;//ultimo confronto di for
            for(; vettore[--j]>pivot; (*confronti)++);
            (*confronti)++;//ultimo confronto di for
            if(i < j)
            {
                scambia(vettore+i, vettore+j, &park);
                (*scambi)++;
            }
        }
        while(i < j);
        scambia(vettore+primo, vettore+j, &park);
        (*scambi)++;
        quicksort_inserzione_count(vettore,primo,j-1,confronti,scambi);
        quicksort_inserzione_count(vettore,j+1,ultimo,confronti,scambi);
    }
}

void quicksort_count(int *vettore, int primo, int ultimo, unsigned long int *confronti, unsigned long int *scambi)
{
    int pivot, i, j, park;
    if(primo<ultimo)
    {
        pivot=vettore[primo];
        i=primo;
        j=ultimo+1;
        do
        {
            for(; vettore[++i]<pivot; (*confronti)++);
            (*confronti)++;//ultimo confronto di for
            for(; vettore[--j]>pivot; (*confronti)++);
            (*confronti)++;//ultimo confronto di for
            if(i < j)
            {
                scambia(vettore+i, vettore+j, &park);
                (*scambi)++;
            }
        }
        while(i < j);
        scambia(vettore+primo, vettore+j, &park);
        (*scambi)++;
        quicksort_count(vettore,primo,j-1,confronti,scambi);
        quicksort_count(vettore,j+1,ultimo,confronti,scambi);
    }
}

//Merge sort
void mergensort_inser_count(int *vettore, int *tmp, int elementi, unsigned long int *confronti, unsigned long int *scambi)
{
    int passo = PASSO_INSER;
    int i, j, k, medio, fine, *park;
    for(i=0; i<elementi-PASSO_INSER; i+=PASSO_INSER)
        inserzione_count(vettore+i, PASSO_INSER,confronti,scambi);
    inserzione_count(vettore+i, elementi-i,confronti,scambi);
    do//ciclo per aumentare il passo
    {
        for(k=0; k < elementi;)//ciclo per scorrere la lista e fondere i sottofile
        {
            medio=k+passo;
            fine=passo*2+k;
            if(medio>elementi)
                medio=fine=elementi;
            else if(fine>elementi)
                fine=elementi;
            for(i=k, j=medio; i < medio && j < fine;)
            {
                if(vettore[i] <= vettore[j])
                    tmp[k++]=vettore[i++];
                else
                    tmp[k++]=vettore[j++];
                (*scambi)++;
                (*confronti)++;//per l'if o l'else e lo scambio
            }
            for(; i<medio; (*scambi)++)
                tmp[k++]=vettore[i++];
            for(; j<fine; (*scambi)++)
                tmp[k++]=vettore[j++];
        }
        park=tmp;//scambio la lista originale con quella appena ordinata
        tmp=vettore;
        vettore=park;
        (*scambi)++;
        passo*=2;//raddoppio il passo
    }
    while(passo < elementi*2);
}

void mergensort_iter_count(int *vettore, int *tmp, int elementi, unsigned long int *confronti, unsigned long int *scambi)
{
    int passo=1, i, j, k, medio, fine;
    int *park;
    do//ciclo per aumentare il passo
    {
        for(k=0; k < elementi;)//ciclo per scorrere la lista e fondere i sottofile
        {
            medio = k+passo;
            fine = passo*2+k;
            if(medio > elementi)
                medio = fine = elementi;
            else if(fine > elementi)
                fine = elementi;
            for(i=k, j=medio; i < medio && j < fine; )
            {
                if(vettore[i] <= vettore[j])
                    tmp[k++]=vettore[i++];
                else
                    tmp[k++]=vettore[j++];
                (*scambi)++;
                (*confronti)++;//per l'if o l'else e lo scambio
            }
            for(; i<medio; (*scambi)++)
                tmp[k++]=vettore[i++];
            for(; j<fine; (*scambi)++)
                tmp[k++]=vettore[j++];
        }
        park=tmp;//scambio la lista originale con quella appena ordinata
        tmp=vettore;
        vettore=park;
        (*scambi)++;
        passo*=2;//raddoppio il passo
    }
    while(passo < elementi*2);
}

//Heap sort
void adatta_count(int *vettore,int padre,int size, unsigned long int *confronti, unsigned long int *scambi)
{
    int figlio, key;
    key=vettore[padre];
    figlio=2*padre;//figlio sinistro
    while(figlio<=size)
    {
        if((figlio<size) && vettore[figlio] < vettore[figlio+1])//si sposta al figlio dx se è più grande
            figlio++;
        (*confronti)++;//per l'if sopra
        (*confronti)++;//per l'if-else sotto
        if(key < vettore[figlio])//se il padre è più piccolo del maggiore dei figli
        {
            vettore[figlio/2]=vettore[figlio];
            (*scambi)++;
            figlio*=2;
        }
        else
            break;
    }
    vettore[figlio/2]=key;
    (*scambi)++;
}

void heap_sort_count(int *vettore,int size, unsigned long int *confronti, unsigned long int *scambi)
{
    int i, park;
    vettore--;//cosi vettore[0] diventa vettore[1]
    for(i=size/2; i>0; i--)//adatta tutti i nodi i tali che 0<i<n/2 (non foglie)
        adatta_count(vettore,i,size,confronti,scambi);
    for(i=size; i>0; )//scambia il primo e l'ultimo elemento e riadatta il nuovo vettore escludendo gli elementi messi alla fine (già ordinati)
    {
        park=vettore[1];
        vettore[1]=vettore[i];
        vettore[i]=park;
        (*scambi)++;
        adatta_count(vettore,1,--i,confronti,scambi);
    }
}

//Selezione
void selezione_count(int lista[],int elementi, unsigned long int *confronti, unsigned long int *scambi)
{
    int i,j,min,park;
    for(i=0; i<elementi; i++)
    {
        min=i;
        for(j=i+1; j<=elementi; j++)
        {
            (*confronti)++;//if
            if(lista[j]<lista[min])
            {
                min=j;
            }
        }
        (*confronti)++;//if
        if(min!=i)
        {
            park=lista[i];
            lista[i]=lista[min];
            lista[min]=park;
            (*scambi)++;
        }
    }
}
/*###################################################################################################################
#####################################################################################################################
                                           Analisi delle funzioni
#####################################################################################################################
###################################################################################################################*/

void analisi(int lista[], int elementi)
{
    int tmp[MAX],tmp2[MAX],i;
    unsigned long int scambi,confronti;
    struct ele *testa=NULL;
    clock_t start,end;
    float tempo;

    printf("Ordinamento                 tempo      confronti      scambi  verifica\n");

    for(i=0, tempo=0; i<RIPETIZIONI; i++)
    {
        copia(lista,tmp,elementi);
        start=clock();
        quicksort(tmp,0,elementi-1);
        end=clock();
        tempo+=((double)(end-start))/CLK_TCK;
    }
    confronti=scambi=0;
    copia(lista,tmp,elementi);
    quicksort_count(tmp, 0, elementi-1, &confronti, &scambi);
    printf("Quick sort               %3.6f   %12u%12u    ", tempo/RIPETIZIONI, confronti, scambi);
    check(tmp,elementi);

    for(i=0, tempo=0; i<RIPETIZIONI; i++)
    {
        copia(lista,tmp,elementi);
        start=clock();
        quicksort_inserzione(tmp,0,elementi-1);
        end=clock();
        tempo+=((double)(end-start))/CLK_TCK;
    }
    confronti=scambi=0;
    copia(lista,tmp,elementi);
    quicksort_inserzione_count(tmp, 0, elementi-1, &confronti, &scambi);
    printf("\nQuicksort ed inserzione  %3.6f   %12u%12u    ", tempo/RIPETIZIONI, confronti, scambi);
    check(tmp,elementi);

    for(i=0, tempo=0; i<RIPETIZIONI; i++)
    {
        copia(lista,tmp,elementi);
        start=clock();
        mergensort_iter(tmp, tmp2, elementi);
        end=clock();
        tempo+=((double)(end-start))/CLK_TCK;
    }
    confronti=scambi=0;
    copia(lista,tmp,elementi);
    mergensort_iter_count(tmp, tmp2, elementi, &confronti, &scambi);
    printf("\nMerge sort iterativo     %3.6f   %12u%12u    ", tempo/RIPETIZIONI, confronti, scambi);
    check(tmp,elementi);

    for(i=0, tempo=0; i<RIPETIZIONI; i++)
    {
        copia(lista,tmp,elementi);
        start=clock();
        mergensort_inser(tmp, tmp2, elementi);
        end=clock();
        tempo+=((double)(end-start))/CLK_TCK;
    }
    confronti=scambi=0;
    copia(lista,tmp,elementi);
    mergensort_inser_count(tmp, tmp2, elementi, &confronti, &scambi);
    printf("\nMerge sort ed inserzione %3.6f   %12u%12u    ", tempo/RIPETIZIONI, confronti, scambi);
    check(tmp,elementi);

    for(i=0, tempo=0; i<RIPETIZIONI; i++)
    {
        copia(lista,tmp,elementi);
        start=clock();
        heap_sort(tmp,elementi+1);
        end=clock();
        tempo+=((double)(end-start))/CLK_TCK;
    }
    confronti=scambi=0;
    copia(lista,tmp,elementi);
    heap_sort_count(tmp,elementi+1, &confronti, &scambi);
    printf("\nHeap sort                %3.6f   %12u%12u    ", tempo/RIPETIZIONI, confronti, scambi);
    check(tmp,elementi);

    for(i=0, tempo=0; i<RIPETIZIONI; i++)
    {
        testa=static_to_dinamic(lista,testa,elementi);
        start=clock();
        testa=radix(testa);
        end=clock();
        tempo+=((double)(end-start))/CLK_TCK;
    }
    printf("\nRadix sort               %3.6f\t\t\t\t", tempo/RIPETIZIONI);
    check_dinamic(testa);
    empty(testa);

    for(i=0, tempo=0; i<RIPETIZIONI; i++)
    {
        copia(lista,tmp,elementi);
        start=clock();
        inserzione(tmp,elementi);
        end=clock();
        tempo+=((double)(end-start))/CLK_TCK;
    }
    confronti=scambi=0;
    copia(lista,tmp,elementi);
    inserzione_count(tmp,elementi, &confronti, &scambi);
    printf("\nInserzione               %3.6f   %12u%12u    ", tempo/RIPETIZIONI, confronti, scambi);
    check(tmp,elementi);

    for(i=0, tempo=0; i<RIPETIZIONI; i++)
    {
        copia(lista,tmp,elementi);
        start=clock();
        selezione(tmp,elementi);
        end=clock();
        tempo+=((double)(end-start))/CLK_TCK;
    }
    confronti=scambi=0;
    copia(lista,tmp,elementi);
    selezione_count(tmp,elementi, &confronti, &scambi);
    printf("\nSelezione                %3.6f   %12u%12u    ", tempo/RIPETIZIONI, confronti, scambi);
    check(tmp,elementi);
}

int main()
{
    int scelta,elementi,lista[MAX];
    char ordine[20];
    elementi=numero();
    crea(elementi,ordine,lista);
    do
    {
        pulisci;
        printf("Confronto tra metodi d'ordinamento\n\n"
               "%d elementi %s\n\n"
               "1)Cambia numero di elementi ed ordinamento\n"
               "2)cambia tipo d'ordinamento\n"
               "3)confronta i metodi d'ordinamento\n"
               "0)esci\n",elementi,ordine);
        scanf("%d",&scelta);
        pulisci;
        switch(scelta)
        {
            case 1:
                elementi=numero();
            case 2:
                crea(elementi,ordine,lista);
                break;
            case 3:
                analisi(lista,elementi);
                break;
            case 0:
                return 0;
        }
        pause();
    }
    while(1);
}

