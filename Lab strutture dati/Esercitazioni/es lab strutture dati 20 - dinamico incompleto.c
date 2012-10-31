#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define MAX_STRING 30
#define CONTATTI_X_PARTE 5

typedef struct contatto
{
    char cognome[MAX_STRING],nome[MAX_STRING],indirizzo[MAX_STRING],telefono[MAX_STRING];
    struct contatto *next,*prev;
}
*agenda;

int empty(agenda testa)
{
    if(testa)
        return 1;
    printf("L'agenda è vuota!");
    fflush(stdin);
    getchar();
    return 0;
}

void push(agenda *testa,char *cognome,char *nome,char *indirizzo,char *telefono)
{
    agenda tmp=(agenda)malloc(sizeof(struct contatto));
    strcpy(tmp->cognome,cognome);
    strcpy(tmp->nome,nome);
    strcpy(tmp->indirizzo,indirizzo);
    strcpy(tmp->telefono,telefono);
    if(*testa)
    {
        (*testa)->prev=tmp;
        tmp->next=*testa;
        *testa=tmp;
    }
    else
    {
        *testa=tmp;
        tmp->next=NULL;
    }
    tmp->prev=NULL;
}

void add(agenda *testa, int *n_contatti)
{
    char cognome[MAX_STRING],nome[MAX_STRING],indirizzo[MAX_STRING],telefono[MAX_STRING];
    do
    {
        printf("Inserisci il cognome(q per uiscire): ");
        scanf("%s",cognome);
        if(cognome[0]!='q' && cognome[0]!='Q')
        {
            fflush(stdin);
            printf("Inserisci il nome: ");
            gets(nome);
            printf("%s",nome);
            printf("Inserisci l'indirizzo: ");
            gets(indirizzo);
            printf("Inserisci il numero di telefono: ");
            gets(telefono);
            push(testa,cognome,nome,indirizzo,telefono);
            (*n_contatti)++;
        }
    }
    while(cognome[0]!='q' && cognome[0]!='Q');
}

void stampa(agenda testa, int n_contatti)
{
    if(empty(testa))
    {
        while(testa)
        {
            printf("%s  %s\n"
                   "%s\n"
                   "%s\n\n",testa->cognome,testa->nome,testa->indirizzo,testa->telefono);
            testa=testa->next;
        }
    }
    printf("\n%d contatti in rubrica", n_contatti);
}

agenda sort(agenda testa)//per inserzione
{
    agenda app,tmp,scroll=testa->next;//comincio dal secondo elemento
    int counter;
    for(counter=CONTATTI_X_PARTE-1; counter,scroll; counter--)//counter=CONTATTI_X_PARTE-1 perchè comincio dal secondo
    {
        app=scroll->next;
        if(strcmp(scroll->cognome,scroll->prev->cognome)<0)
        {
            printf("\nsposto %s(<%s)",scroll->cognome,scroll->prev->cognome);
            app=scroll->next;//per non perdere il segno
            tmp=scroll->prev;
            //taglio l'elemento dalla lista
            if(scroll->prev)
                scroll->prev->next=scroll->next;
            if(scroll->next)
                scroll->next->prev=scroll->prev;
            //cerco il punto in cui inserire l'elemento
            while((strcmp(scroll->cognome,tmp->cognome)<0) && tmp!=testa)
                tmp=tmp->prev;
            if(strcmp(scroll->cognome,scroll->prev->cognome)<0)//nel caso sia arrivato al primo elemento ed anche questo è maggiore
            {//in questo caso devo inserire l'elemento prima di tmp;
                if(tmp->prev)//se non è il primo elemento in lista e dunque il suo prev non punta a NULL
                    tmp->prev->next=scroll;
                scroll->prev=tmp->prev;
                scroll->next=tmp;
                tmp->prev=scroll;
                testa=scroll;
            }
            else
            {
                scroll->next=tmp->next;
                scroll->prev=tmp;
                tmp->next->prev=scroll;
                tmp->next=scroll;
            }
        }
        scroll=app;
    }
    printf("\n\nHo appena ordinato:\n");
    stampa(testa,CONTATTI_X_PARTE);
    return testa;
}

void merge(agenda lista1, agenda lista2,int contatti_x_parte)
{
    int counter1=contatti_x_parte,counter2=contatti_x_parte;
    agenda scroll1=lista1,scroll2=lista2,tmp;
    while(scroll1 && scroll2 && counter1 && counter2)
    {
        if(strcmp(lista1->cognome,lista2->cognome)>0)
        {

            if(scroll1->prev)
                scroll1->prev->next=scroll2;
            tmp=scroll2->next;
            scroll2->next=scroll1->next;
            scroll1->next=tmp;
            tmp=scroll2->prev;
            scroll2->prev=scroll1->prev;
            scroll1->prev=tmp;
            scroll1=scroll1->next;
        }
        scroll2=scroll2->next;
    }

}

void mergensort(agenda *testa,int n_contatti)
{
    if(empty(*testa))
    {
        agenda scroll=*testa;
        int n_parti=(n_contatti/CONTATTI_X_PARTE)+1,i,j;
        for(i=0; i<n_parti,scroll; i++)//passa a sort l'indirizzo del primo elemento di ogni gruppo
        {
            scroll=sort(scroll);
            for(j=0; j<CONTATTI_X_PARTE, scroll; j++)
                scroll=scroll->next;
        }
    }
}

int main()
{
    agenda testa=NULL;
    int scelta,n_contatti=0;
    do
    {
        pulisci;
        printf("Gestione di una rubrica con mergesort\n\n"
               "1)Inserire un nuovo elemento\n"
               "2)Stampare la rubrica\n"
               "3)Ordinare gli elementi per cognome con il mergesort\n"
               "0)uscire\n");
        scanf("%d",&scelta);
        pulisci;
        switch(scelta)
        {
            case 0:
            return 0;
            case 1:
            add(&testa, &n_contatti);
            break;
            case 2:
            stampa(testa, n_contatti);
            break;
            case 3:
            mergensort(&testa, n_contatti);
            break;
            default :
            printf("Scelta errata!");
        }
        pause();
    }
    while(1);
}
