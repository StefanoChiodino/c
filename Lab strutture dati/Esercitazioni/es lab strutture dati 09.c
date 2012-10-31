/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "header.h"

#define MAX_NUM 20
#define MAX_NOME 30

typedef struct ele
{
    char nome[MAX_NOME],numero[MAX_NUM];
    struct ele * prev,*next;
}*agenda;

typedef struct app
{
    char nome[MAX_NOME];
    char numero[MAX_NUM];
} app;

void pushnsort(char *nome,char *numero, agenda *testa, agenda* coda)
{
          agenda scroll,tmp=(agenda)malloc(sizeof(struct ele));
          strcpy(tmp->nome,nome);
          strcpy(tmp->numero,numero);
          if(*testa)
          {
                    if(strcmp((*testa)->nome,nome)>=0)
                    {
                        tmp->prev=*coda;
                        tmp->next=*testa;
                        (*testa)->prev=tmp;
                        *testa=tmp;
                        (*coda)->next=*testa;
                    }
                    else if(strcmp((*testa)->nome,nome)<0)
                    {
                        scroll=*testa;
                        do
                            scroll=scroll->next;
                        while(scroll!=*testa && strcmp(scroll->nome,nome)<0);
                        tmp->prev=scroll->prev;
                        tmp->next=scroll;
                        tmp->prev->next=tmp;
                        scroll->prev=tmp;
                    }
          }
          else
          {
               *coda=*testa=tmp;
               (*testa)->prev=(*testa)->next=*testa;
          }
}


void push(app contatto, agenda *testa, agenda *coda)
{
          agenda tmp=(agenda)malloc(sizeof(struct ele));
          strcpy(tmp->nome,contatto.nome);
          strcpy(tmp->numero,contatto.numero);
          if(*testa){
                    (*coda)->next=tmp;
                    tmp->prev=*coda;
                    *coda=tmp;
          }
          else{
               *testa=*coda=tmp;
               (*testa)->prev=(*testa)->next=NULL;
          }
          (*coda)->next=*testa;
          (*testa)->prev=*coda;
}



void load(agenda *testa,agenda *coda)
{
       app tmp;
       int i=0;
       FILE * rubrica;
       rubrica=fopen("rubrica.txt","rb");
       if(rubrica)
       {
           printf("\nE' stata trovata una rubrica, caricamento dati...");
           while(!feof(rubrica))
           {
               fread(&tmp,sizeof(app),1,rubrica);
               if(!feof(rubrica))
               {
                   push(tmp,testa,coda);
                   printf("\n%s, %s",tmp.nome,tmp.numero);
                   i++;
               }
           }
           printf("\n%d dati caricati\n",i);
           fclose(rubrica);
       }
       else
           printf("\n\nNessuna rubbrica trovata\n\n");
}

void stampa(agenda testa){
     agenda scroll=testa;
     pulisci;
     if(scroll)
               do{
                  printf("%s\n%s\n\n",scroll->nome,scroll->numero);
                  scroll=scroll->next;
               }while(scroll!=testa);
     else
         printf("Nessun contatto presente in rubbrica\n");
}
      
void save(agenda testa){
       FILE * rubrica;
       app tmp;
       agenda scroll=testa;
       rubrica=fopen("rubrica.txt","wb");
       if(scroll){
                  do{
                     strcpy(tmp.nome,scroll->nome);
                     strcpy(tmp.numero,scroll->numero);
                     fwrite(&tmp,sizeof(app),1,rubrica);
                     scroll=scroll->next;
                  }while(scroll!=testa);
       }
       fclose(rubrica);
}

void add(agenda *testa, agenda * coda){
       char nome[MAX_NOME],numero[MAX_NUM];
       int flag=1;
       pulisci;
       do{
            fflush(stdin);
            printf("Inserisci nome e numero, scrivi exit per uscire\n"
            "nome: ");
            gets(nome);
            if(!strcmp(nome,"exit"))
                flag=0;
            else{
                 printf("numero: ");
                 gets(numero);
                 pushnsort(nome,numero,testa,coda);
            }
       }while(flag);
}

void del(agenda *tmp,agenda *testa, agenda *coda){
     if(*coda==*testa){
                       *coda=*testa=NULL;
                       printf("\nSono stati eliminati tutti i contatti\n");
     }
     else{
          if(*tmp==*testa)
                          *testa=(*testa)->next;
          else if(*tmp==*coda)
               *coda=(*coda)->prev;
          (*tmp)->prev->next=(*tmp)->next;
          (*tmp)->next->prev=(*tmp)->prev;
     }
     free(*tmp);
     *tmp=NULL;
}

void edit(agenda * tmp, agenda *testa, agenda *coda){
     char nome[MAX_NOME], numero[MAX_NUM];
     pulisci;
     printf("Modifica del contatto\n"
     "%s\n%s\n\n"
     "Inserisci il nome: ",(*tmp)->nome,(*tmp)->numero);
     del(tmp, testa, coda);
     fflush(stdin);
     gets(nome);
     printf("Inserisci il numero: ");
     gets(numero);
     pushnsort(nome, numero, testa, coda);
}

agenda cerca(agenda scroll){
       agenda tmp=scroll;
       char key[MAX_NOME];
       printf("Inserisci il nome o il numero da cercare: ");
       fflush(stdin);
       gets(key);
       if(scroll){
                 do{
                                      scroll=scroll->next;
                 }while(strcmp(scroll->nome,key)!=0 && strcmp(scroll->numero,key)!=0 && scroll && scroll!=tmp);
                 if(!strcmp(scroll->nome,key)){
                                               printf("Contatto trovato!\n"
                                               "%s\n%s\n",scroll->nome,scroll->numero);
                                               return scroll;
                 }
                 else{
                      printf("\nNessun contatto in rubrica con questo numero\nome!\n\n");
                      return NULL;
                 }
       }
       else{
            printf("\nNessun contatto in rubrica!\n\n");
            return NULL;
       }
}

void erase(agenda *testa, agenda *coda){
     if(*testa){
             do{
                *testa=(*testa)->next;
                free((*testa)->prev);
             }while(*testa!=*coda);
             free(*testa);
             *testa=*coda=NULL;
             printf("\nLa rubbrica e\' stata eliminata con successo\n");
     }
     else
         printf("\nLa rubbrica è vuota!\n");
}


void scroll(agenda scroll,agenda *testa,agenda *coda){
       agenda tmp;
       char scelta;
       do{
            if(scroll){
                  pulisci;
                  printf("%s\n%s\n\n"
                  "%c Z per il contatto precedente %s <--\n"
                  "%c X per il contatto successivo --> %s\n"
                  "%c D per cancellare il contatto\n"
                  "%c Q per uscire\n"
                  "%c M per modificare il contatto\n\n",scroll->nome,scroll->numero,30,scroll->prev->nome,31,scroll->next->nome,158,17,15);
                  scelta=getch();
                  if(scelta=='z' || scelta=='Z')
                                 scroll=scroll->prev;          
                  else if(scelta=='x' || scelta=='X')
                                 scroll=scroll->next;                  
                  else if(scelta=='m' || scelta=='M')
                                 edit(&scroll,testa, coda);                  
                  else if(scelta=='d' || scelta=='D'){
                                         tmp=scroll->next;
                                         del(&scroll,testa,coda);
                                         if(*testa)
                                                  scroll=tmp;
                  }
            }
       }while(scelta!='q' && scelta !='Q' && scroll);
}

int main(){
    agenda testa=NULL,coda=NULL,tmp=NULL;
    int scelta;
    load(&testa,&coda);
    pause();
    do{
        pulisci;
        printf("Gestione di una rubbrica\n"
        "1)inserire un numero\n"
        "2)cercare un numero\n"
        "3)eliminare un numero\n"
        "4)modificare un contatto\n"
        "5)stampare tutta la rubbrica\n"
        "6)scorrere la rubbrica\n"
        "7)cancellare tutta la rubbrica\n"
        "0)salva ed esci\n");
        scanf("%d",&scelta);
        switch(scelta){
                   case 0:
                        save(testa);
                        return 0;
                   case 1:
                        add(&testa,&coda);
                        break;
                   case 2:
                        cerca(testa);
                        break;
                   case 3:
                        tmp=cerca(testa);
                        if(tmp)
                               del(&tmp,&testa,&coda);
                        break;                        
                   case 4:
                        tmp=cerca(testa);
                        if(tmp)
                               edit(&tmp,&testa,&coda);
                        break;
                   case 5:
                        stampa(testa);
                        break;
                   case 6:
                        scroll(testa,&testa,&coda);
                        break;
                   case 7:
                        erase(&testa,&coda);
                        break;
                   default:
                           printf("Scelta errata!");
                           pause();
        }
    }while(1);
}
