/* Stefano Chiodino 39962 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

#define MAX_NUM 100
#define MAX_CODA 10

typedef struct elemento {
	int key;
   struct elemento *next;
} *ele;

int check(ele scroll, int n)
{
    for(; scroll->next; scroll=scroll->next, n--)
        if(scroll->key > scroll->next->key)
        {
            printf(" FAILED");
            return 0;
        }
    if(n!=1)
    {
         printf(" FAILED");
         return 0;
    }
    printf(" ok");
    return 1;
}

void stampa(ele scroll){
     printf("\n\n");
     for(; scroll; scroll=scroll->next)
              printf("%d -> ",scroll->key);
}

ele crea(){
    ele tmp,scroll,top;
    int i;
    top=(ele)malloc(sizeof(struct elemento));
    top->key=rand()%MAX_NUM;
    top->next=NULL;
    for(i=1; i<MAX_CODA; i++){
                            tmp=(ele)malloc(sizeof(struct elemento));
                            tmp->key=rand()%MAX_NUM;
                            if(tmp->key <= top->key){
                                          tmp->next=top;
                                          top=tmp;
                            }
                            else{
                                 scroll=top;
                                 while(scroll->next && scroll->next->key < tmp->key)
                                                   scroll=scroll->next;
                                 tmp->next=scroll->next;
                                 scroll->next=tmp;
                            }
    }
    return top;
}

ele fondi(ele a,ele b){
    ele tmp,c;
    if(a->key<=b->key)
    {
        c=a;
        a=a->next;
    }
    else
    {
        c=b;
        b=b->next;
    }
    tmp=c;
    while(a && b){
        if(a->key<=b->key)
        {
            tmp->next=a;
            a=a->next;
            tmp=tmp->next;                               
        }
        else
        {
            tmp->next=b;
            b=b->next;
            tmp=tmp->next;                               
        }
    }
    if(a)
         tmp->next=a;
    else if(b)
         tmp->next=b;
    return c;
}

int main(){
    ele x,y,z;
    srand(time(NULL));

    x=crea();
    y=crea();
    
    stampa(x);
    check(x,MAX_CODA);
    stampa(y);
    check(y,MAX_CODA);
    
    z=fondi(x,y);
    stampa(z);
    check(z,MAX_CODA*2);
    
    pause();
    return 0;
}
