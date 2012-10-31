/* Stefano Chiodino 39962
1_2_3
4_O_6   tabella spostamenti
7_8_9
 
Lo spostamento Y+1 è inteso verso il basso

Invece che rappresentare il labirinto con 0 ed 1 ho usato lo stesso principio ma
usando numeri che stampati a video come caratteri sembrano blocchi bianchi o neri,
tutte le coordinate visitate diventano invece grigie.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#define n 20
#define m 20

typedef struct nodo
{
    int x,y;
    struct nodo *next;
}* coda;

coda push(coda testa, int x, int y)
{
    coda tmp=(struct nodo*)malloc(sizeof(struct nodo));
    tmp->x=x;
    tmp->y=y;
    tmp->next=testa;
    return tmp;
}

coda pop(coda testa, int *x, int *y)
{
    coda tmp;
    *x=testa->x;
    *y=testa->y;
    tmp=testa->next;
    free(testa);
    return tmp;
}

void mostra(int labirinto[n][m])
{
    int i,j;
    pulisci;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            printf("%c",labirinto[i][j]);
        printf("\n");
    }
    printf("\n\n\n");
}

void genera(int labirinto[n][m])
{
    int i,j;
    printf("\n\n\nGenero....\n");
    for(i=1;i<n-1;i++)
        for(j=1;j<m-1;j++)
            if(rand()%2)
                labirinto[i][j]=219;
            else
                labirinto[i][j]=0;
    labirinto[1][1]=labirinto[n-2][m-2]=0;
    for(i=0;i<n;i++)
        labirinto[0][i]=labirinto[n-1][i]=labirinto[i][0]=labirinto[i][m-1]=219;
}

void parti(int labirinto[n][m])
{
    int eunnodo, x=1,y=1, mosse=0;
    clock_t start, end;
    coda testa=NULL;
    start=clock();
    do
    {
        labirinto[x][y]=176;
        eunnodo=0;
        if(labirinto[x+1][y+1]==0)//quanti spostamenti diversi può effettuare da quelle coordinate?
            eunnodo++;
        if(labirinto[x][y+1]==0)
            eunnodo++;
        if(labirinto[x+1][y]==0)
            eunnodo++;
        if(labirinto[x-1][y+1]==0)
            eunnodo++;
        if(labirinto[x+1][y-1]==0)
            eunnodo++;
        if(labirinto[x-1][y]==0)
            eunnodo++;
        if(labirinto[x][y-1]==0)
            eunnodo++;
        if(labirinto[x-1][y-1]==0)
            eunnodo++;
            
        if(eunnodo>1)//se ci sono almeno due possibilità lo carica in coda come nodo
            testa=push(testa, x, y);
            
        if(labirinto[x+1][y+1]==0)//si sposta, prediligendo la direzione sud-est
        {
            x+=1;
            y+=1;
        }
        else if(labirinto[x][y+1]==0)
            y+=1;
        else if(labirinto[x+1][y]==0)
            x+=1;
        else if(labirinto[x-1][y+1]==0)
        {
            x-=1;
            y+=1;
        }
        else if(labirinto[x+1][y-1]==0)
        {
            x+=1;
            y-=1;
        }
        else if(labirinto[x-1][y]==0)
            x-=1;
        else if(labirinto[x][y-1]==0)
            y-=1;
        else if(labirinto[x-1][y-1]==0)
        {
            x-=1;
            y-=1;
        }
        else if(testa)//se non si può spostare torna all'ultimo nodo con più uscite
            testa=pop(testa, &x, &y);//se necessario verrà caricato e scaricato dalla memoria finchè non vengono provate tutte le vie
        else//diversamente vuol dire che il labirinto non ha soluzioni
        {
            end=clock();
            printf("\n\nNon trovo soluzioni (%d mosse e %f secondi)", mosse, (double)(end-start)/CLK_TCK);
            return;
        }
        mosse++;
    }while(x!=n-2 || y!=m-2);
    labirinto[x][y]=176;
    end=clock();
    mostra(labirinto);
    printf("Soluzione trovata in %d mosse e %f secondi\n", mosse, (double)(end-start)/CLK_TCK);
}

int main()
{
    char scelta;
    int labirinto[n][m];
    srand(time(NULL));

    do
    {
        genera(labirinto);
    	  mostra(labirinto);
        pause();

        parti(labirinto);
        pause();
        fflush(stdin);
        printf("\n\nCreare e cercare di risolvere un altro labirinto? ( S per si qualsiasi altro tasto per no)");
        scelta=getch();
    }while(scelta=='s' || scelta=='S');
    return 0;
}

