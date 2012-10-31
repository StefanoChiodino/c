/*Esercitazione 4: Matrici Sparse*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define DIM 100

typedef struct
{
    int r;
    int c;
    int info;
}
ele;

typedef struct trasposta
{
    int termini_riga;
    int pos_iniziale;
}
trasp;

void init(ele *);
void genera_matrice(ele *);
void visualizza(ele *);
int ricerca(ele *,int);
void ordinamento(ele *);
int menu(void);
void trasposta_2(ele *,ele *);
void trasposta_1(ele *a,ele *b);
int vuoto(ele *);
int termini_riga(ele *a,int,int);

void main(void)
{
    ele v[DIM],t[DIM];
    int s,x,y;

    randomize();

    init(v);

    do
    {
        s=menu();

        clrscr();
        switch(s)
        {
            case 1:
            {
                //Creazione matrice sparsa e la ordina
                genera_matrice(v);
                break;
            }
            case 2:
            {
                //Visualizza matrice
                if(!vuoto(v))
                    visualizza(v);
                else
                    printf("\nLa matrice e' vuota. Creare la matrice e riprovare.");
                break;
            }
            case 3:
            {
                //Crea trasposta e la visualizza
                if(!vuoto(v))
                {
                    trasposta_2(v,t);
                    visualizza(t);
                }
                else
                    printf("\nLa matrice e' vuota. Creare la matrice e riprovare.");
                break;
            }
            case 4:
            {
                //Crea trasposta e la visualizza
                if(!vuoto(v))
                {
                    trasposta_1(v,t);
                    visualizza(t);
                }
                else
                    printf("\nLa matrice e' vuota. Creare la matrice e riprovare.");
                break;
            }
            case 5:
            {
                //Ricerca di un elemento all'interno di una matrice sparsa
                if(!vuoto(v))
                {
                    printf("Inserisci l'elemento da ricercare: ");
                    scanf("%d",&x);
                    y=ricerca(v,x);
                    if (y==-1)
                        printf("L'elemento non e' presente nella matrice.");
                    else
                        printf("L'elemento e' presente e si trova in posizione [%d,%d].",v[y].r,v[y].c);
                }
                else
                    printf("\nLa matrice e' vuota. Creare la matrice e riprovare.");
                break;
            }
            case 0:
            {
                //uscita
                break;
            }
        }

        if (s!=0)
        {
            fflush(stdin);
            printf("\n\nPremi INVIO per tornare al Menu'.");
            getchar();
        }
    }
    while(s!=0);
}


void init(ele *w)
{
    int i;

    for (i=0;i<DIM;i++)
    {
        w[i].r=0;
        w[i].c=0;
        w[i].info=0;
    }
}

int menu()
{
    int err,s;

    do
    {
        clrscr();
        printf("----- MENU' -----");
        printf("\n1) Creazione Matrice");
        printf("\n2) Stampa Matrice");
        printf("\n3) Stampa Trasposta (2 vettori)");
        printf("\n4) Stampa Trasposta (1 vettore)");
        printf("\n5) Ricerca");
        printf("\n0) Esci");

        printf("\n\nFai la tua scelta: ");

        do
        {
            fflush(stdin);
            err=scanf("%d",&s);
        }
        while(!err && (s<1 || s>DIM));

    }
    while((s<0 || s>5) && !err);

    return(s);
}

void genera_matrice(ele *w)
{
    int err,i;

    do
    {
        fflush(stdin);
        printf("Inserisci il numero di righe della matrice sparsa: ");
        err=scanf("%d",&w[0].r);
    }
    while(!err && (w[0].r<1 || w[0].r>DIM));

    do
    {
        fflush(stdin);
        printf("\nInserisci il numero di colonne della matrice sparsa: ");
        err=scanf("%d",&w[0].c);
    }
    while(!err && (w[0].c<1 || w[0].c>DIM));

    do
    {
        fflush(stdin);
        printf("\nInserisci il numero di elementi non nulli della matrice sparsa: ");
        err=scanf("%d",&w[0].info);
    }
    while(!err && (w[0].info<1 || w[0].info>(w[0].r*w[0].c)));

    clrscr();

    printf("Inserisci le triple della matrice sparsa (Riga, Colonna, Valore)\n");
    for(i=1;i<=w[0].info;i++)
    {
        do
        {
            printf("Riga: ");
            fflush(stdin);
            scanf("%d", &w[i].r);
        }
        while(w[i].r>w[0].r || w[i].r<0);
        do
        {
            printf("Colonna: ");
            scanf("%d", &w[i].c);
        }
        while(w[i].c>w[0].c || w[i].c<0);

        printf("Dato: ");
        scanf("%d", &w[i].info);
    }

    ordinamento(w);
}

void visualizza(ele *w)
{
    int i,j,k;

    k=1;
    for(i=0;i<w[0].r;i++)
    {
        for(j=0;j<w[0].c;j++)
            if(w[k].r==i && w[k].c==j)
                printf("%d ",w[k++].info);
            else
                printf("0 ");
        printf("\n");
    }
}

int ricerca(ele *w,int x)
{
    int i,n;

    n=w[0].info;
    i=1;
    while(w[i].info!=x && i<=n)
        i++;

    if (w[i].info!=x)
        return(-1);
    else
        return(i);
}

void ordinamento(ele *w)
{
    ele app;
    int i,j,min;

    for(i=1;i<w[0].info;i++)
    {
        min=i;
        for(j=i+1;j<=w[0].info;j++)
            if(w[j].r<w[min].r || (w[j].r==w[min].r && w[j].c<w[min].c))
                min=j;

        app=w[i];
        w[i]=w[min];
        w[min]=app;
    }
}

int vuoto(ele *w)
{
    if (w[0].info!=0)
        return(0);
    else
        return(1);
}

void trasposta_2(ele *a,ele *b)
{
    int termini_riga[DIM*DIM],pos_iniziale[DIM];
    int i,j,num_col=a[0].c,num_termini=a[0].info;

    b[0].r=num_col;
    b[0].c=a[0].r;
    b[0].info=a[0].info;

    if(num_termini>0)
    {
        for(i=0;i<num_col;i++)
            termini_riga[i]=0;
        for(i=1;i<=num_termini;i++)
            termini_riga[a[i].c]++;
        pos_iniziale[0]=1;
        for(i=1;i<num_col;i++)
            pos_iniziale[i]=pos_iniziale[i-1]+termini_riga[i-1];
        for(i=1;i<=num_termini;i++)
        {
            j=pos_iniziale[a[i].c]++;
            b[j].r=a[i].c;
            b[j].c=a[i].r;
            b[j].info=a[i].info;
        }
    }
}

void trasposta_1(ele *a,ele *b)
{
    trasp vett_app[DIM];
    int i,j,num_col=a[0].c,num_termini=a[0].info;

    b[0].r=num_col;
    b[0].c=a[0].r;
    b[0].info=num_termini;

    if(num_termini>0)
    {
        for(i=0;i<a[0].c;i++)
            vett_app[i].termini_riga=0;
        for(i=1;i<=num_termini;i++)
            vett_app[a[i].c].termini_riga++;
        vett_app[0].pos_iniziale=1;
        for(i=1;i<num_col;i++)
            vett_app[i].pos_iniziale=vett_app[i-1].termini_riga+vett_app[i-1].pos_iniziale;
        for(i=1;i<=num_termini;i++)
            //for(i=1;i<num_col;i++) pos_iniziale[i]=pos_iniziale[i-1]+termini_riga(a,i-1,num_termini);
            //for(i=1;i<=num_termini;i++)
        {
            j=vett_app[a[i].c].pos_iniziale++;
            //j=pos_iniziale[a[i].c]++;
            b[j].r=a[i].c;
            b[j].c=a[i].r;
            b[j].info=a[i].info;
        }
    }
}

int termini_riga(ele *a,int k,int num)
{
    int n=0,i;

    for(i=1;i<=num;i++)
        if(k==a[i].c)
            n++;
    return(n);
}
