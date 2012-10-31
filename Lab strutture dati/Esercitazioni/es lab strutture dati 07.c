/*Stefano Chiodino 39962*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define STRINGA_MAX 100
#define STACK_MAX 100

int priorita_out(char a)
{
    if(a=='+' || a=='-')
              return 12;
    if(a=='*' || a=='/' || a=='%')
              return 13;
    if(a=='(')
              return 20;
}

int priorita_in(char a)
{
    if(a=='+' || a=='-')
              return 12;
    if(a=='*' || a=='/' || a=='%')
              return 13;
    if(a=='(')
              return 0;
}

void pop(char *postfissa, int *count_p, char *simboli,int *count_s)
{
    while(*count_s>0 && simboli[(*count_s)-1]!='(')//copia finche non trova una parentesi o finishe l'array
        postfissa[(*count_p)++]=simboli[--(*count_s)];
    if(simboli[(*count_s)-1]=='(')
            (*count_s)--;
}

void postfix(char * operazione, char * postfissa)
{
     int count_p,count_o,count_s;
     char simboli[STRINGA_MAX];
     for(count_p=count_o=count_s=0; operazione[count_o]!='\0'; count_o++)
     {
               if(operazione[count_o]>='0' && operazione[count_o]<='9')//se è un numero
                   postfissa[count_p++]=operazione[count_o];
               else{
                    if(operazione[count_o]==')')
                        pop(postfissa,&count_p,simboli,&count_s);
                     else
                     {
                         if(count_s && priorita_out(operazione[count_o])<=priorita_in(simboli[count_s-1]))//verifica se l'operatore è di priorità minore della priorità corrente (se ci sono operatori attualmente) o se è una parentisi destra
                         {
                             pop(postfissa,&count_p,simboli,&count_s);//se cosi è svuoto la coda prima di...
                         }
                         simboli[count_s++]=operazione[count_o];//caricare in coda l'attuale operatore
                     }
               }
     }
     pop(postfissa,&count_p,simboli,&count_s);//vuota la coda alla fine di tutta l'operazione
     postfissa[count_p]='\0';
}
     
void valuta(char *postfissa,float risultato[])
{
     int count_p,count_r;
     for(count_p=count_r=0; postfissa[count_p]!='\0'; count_p++)
           if(postfissa[count_p]>='0' && postfissa[count_p]<='9'){
                                             risultato[count_r]=postfissa[count_p]-48;//-48 perchè seconda la tabella ASCII i numeri nei char cominciano da 48
                                             count_r++;
               }
               else{
                    switch(postfissa[count_p])
                    {
                          case '*':
                               risultato[count_r-2]*=risultato[count_r-1];
                               break;
                          case '/':
                               risultato[count_r-2]/=risultato[count_r-1];
                               break;
                          case '+':
                               risultato[count_r-2]+=risultato[count_r-1];
                               break;
                          case '-':
                               risultato[count_r-2]-=risultato[count_r-1];
                               break;
                          case '%':
                               risultato[count_r-2]=(int)risultato[count_r-2]%(int)risultato[count_r-1];
                               break;
                    }
                    count_r--;
               }
}

int check(char* operazione)
{
    int i,count;
    for(i=0; operazione[i]!='\0' && i!=STRINGA_MAX; i++)
        if( (i && operazione[i]>='0' && operazione[i]<='9' && operazione[i-1]>='0' && operazione[i-1]<='9') || !(operazione[i]>='0' && operazione[i]<='9') && operazione[i]!='(' && operazione[i]!=')' && operazione[i]!='+' && operazione[i]!='-' && operazione[i]!='*' && operazione[i]!='/' && operazione[i]!='%')
            return 0;//se un carattere non è un numero o un simbolo ammesso oppure contiene un numero a due cifre
    if(i==STRINGA_MAX)
        return 0;//se è troppo grande
    for(i=0, count=0; operazione[i]!='\0'; i++)//conto le parentesi aperte e chiuse...
        if(operazione[i]=='(')
            count++;
        else if(operazione[i]==')')
            count--;
    if(count!=0)
        return 0;//...se non sono pari
        
    return 1;
}

int main()
{
     char operazione[STRINGA_MAX], postfissa[STRINGA_MAX];
     float risultato[STRINGA_MAX];
     printf("Inserire l'operazione: ");
     scanf("%s",operazione);
     if(check(operazione))
     {
         postfix(operazione,postfissa);
         printf("\nIl suo equivalente postfisso e\': %s",postfissa);
     
         valuta(postfissa,risultato);
         printf("\nIl risultato e\': %f",risultato[0]);
     }
     else
         printf("Impossibile eseguire l'operazione sulla stringa inserita!");
     pause();
     return 0;
}
