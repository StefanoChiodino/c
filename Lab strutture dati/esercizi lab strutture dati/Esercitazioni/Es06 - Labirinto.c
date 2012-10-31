#include <stdlib.h>
#include <stdio.h>

#define STACK_SIZE 300
#define MAX_RIGHE 10
#define MAX_COL 10
#define DIM 10

typedef struct
              {
               int vert;
               int oriz;
              }offset;

typedef struct
              {
               int riga;
               int col;
               int dir;
              }ele;

offset mossa[8]={ {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};

void init_stack(ele *);
void crea_lab(int (*lab)[DIM]);
void stampa_lab(int (*lab)[DIM]);
void percorso(int (*lab)[DIM],ele,ele);
ele del(int *);
void stack_full(void);
void add(ele,int *);

ele stack[STACK_SIZE];
int top=0;

main()
{
 ele inizio,fine;
 int lab[DIM][DIM];

 inizio.riga=1;
 inizio.col=1;
 fine.riga=8;
 fine.col=8;
 srand(time(NULL));
 system("cls");
 crea_lab(lab);
 printf("\t\t   [ Labirinto ]\n\n"); 
 stampa_lab(lab);

 init_stack(stack);
 percorso(lab,inizio,fine);

 fflush(stdin);
 getchar();
}


//Viene creato il labirinto proposto dall'esercizio
void crea_lab(int (*lab)[DIM])
{
 int i,j,cont,x,y;

 for (i=0;i<DIM;i++)
    for(j=0;j<DIM;j++)
       lab[i][j]=1;
       
for(cont=0;cont<40;cont++)
{
    do
    {
        x=rand()%MAX_RIGHE;
        y=rand()%MAX_COL;         
    }
    while(x==MAX_RIGHE-1 || y==MAX_COL-1 || x==0 || y==0);    
    lab[x][y]=0;
}     

lab[1][1]=lab[8][8]=0;
             
}             

//visualizza la matrice
void stampa_lab(int (*lab)[DIM])
{
 int i,j;

 printf("       Entrata->");
 for (i=1;i<MAX_COL-1;i++)
    {            
     for(j=1;j<MAX_RIGHE-1;j++)
        printf(" %d ",lab[i][j]);
     printf("\n\t\t");
    }
}


//azzera lo stack usato per memorizzare le coordinate
void init_stack(ele *s)
{
 int i;

 for (i=0;i<STACK_SIZE;i++)
    {
     s[i].riga=0;
     s[i].col=0;
     s[i].dir=0;
    } 
}


//cerca un percorso valido , lo memorizza nello stack e lo stampa a video
void percorso(int (*lab)[DIM],ele inizio,ele fine)
{
 int i,j,rigac,colc,rigan,coln,dir;
 int trovato=0;
 ele pos;
 int segna[MAX_RIGHE][MAX_COL];

 for(i=0;i<MAX_RIGHE;i++)
    for(j=0;j<MAX_COL;j++) segna[i][j]=lab[i][j];

 segna[inizio.riga][inizio.col]=1;
 top=0;
 pos.riga=inizio.riga; pos.col=inizio.col; pos.dir=0;
 add(pos,&top);

 while(top>-1 && !trovato)
    {
     pos=del(&top);
     rigac=pos.riga; colc=pos.col; dir=pos.dir;
     while(dir<8 && !trovato)
        {
	    	rigan=rigac+mossa[dir].vert;
	    	coln=colc+mossa[dir].oriz;
	    	if(rigan==fine.riga && coln==fine.col) trovato=1;
	    	else
         if(!lab[rigan][coln] && !segna[rigan][coln])
		  		{
		   	 segna[rigan][coln]=1;
		   	 pos.riga=rigac;
		   	 pos.col=colc;
		   	 pos.dir=++dir;
		   	 add(pos,&top);
		   	 rigac=rigan; colc=coln; dir=0;
		  		}
	      else dir++;
        }
    }
 if(trovato)
    {
     printf("\n\nIl percorso e': <Riga,Colonna,Direzione>\n\n");
     for(i=1;i<=top;i++)
        printf("-> [%d %d %d] ",stack[i].riga,stack[i].col,stack[i].dir-1);
        if(!i%6) printf("\n");
     printf("-> [%d %d %d] ",rigac,colc,dir);
     printf("-> [%d %d] ",fine.riga,fine.col);
    }
 else printf("\n[Warning] - Il labirinto non ha un percorso d'uscita!");
}


//aggiunge un elemento allo stack
void add(ele item,int *top)
{
 if(*top>=STACK_SIZE-1)
    {
	  stack_full();
     return;
    }
 stack[++(*top)]=item;
}


void stack_full()
{
 printf("Lo stack e' pieno!");
}


//cancella un elemento dallo stack
ele del(int *top)
{
 if(*top==-1) exit(1);
 return(stack[(*top)--]);
}
