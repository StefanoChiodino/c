
/* <<<<<<<< Albero binario contenente una espressione aritmetica >>>>>>>>>>>  */

/* -	Scrivere un algoritmo in C che legge una espressione numerica in formato
		postfix con gli operatori "+, -, *, /" e la rappresenta secondo un albero
      binario.																					 - */
//
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MaxStackSize 50
#define MaxEsprSize 20
#define MaxCodaSize 20

/* STRUTTURA ALBERO */
typedef char elemento;
typedef struct albero
{
	elemento key;
   albero *figlio_sx;
   albero *figlio_dx;
} tree;
typedef tree *tree_ptr;

/* PROTOTIPI FUNZIONI */
void get_espr(char *);
void crea_albero(tree_ptr *, char *);
void inorder(tree_ptr);
void preorder(tree_ptr);
void postorder(tree_ptr);
void levelorder(tree_ptr);

/* DEFINIZIONE STACK */
void push(int *, tree_ptr);
tree_ptr pop(int *);
int stack_full(int);
int stack_empty(int);

tree_ptr stack[MaxStackSize];

/* DEFINIZIONE CODA */
void addc(int, int *, tree_ptr);
tree_ptr delc(int *, int);

tree_ptr coda[MaxCodaSize];

int main()
{
		char espr[MaxEsprSize];    /* ESPRESSIONE aritmetica in ingresso */
      tree_ptr radice=NULL;		/* RADICE dell'albero */

  	get_espr(espr);
   crea_albero(&radice,espr);
   printf("\nINORDER:   ");
   inorder(radice);
   printf("\nPREORDER:  ");
   preorder(radice);
   printf("\nPOSTORDER: ");
   postorder(radice);
   printf("\nLVL-ORDER: ");
   postorder(radice);

	fflush(stdin);
   getchar();
}

void get_espr(char *espr)
{
	printf("\nInserire una espressione in formato postfisso: ");
   gets(espr);
}

void crea_albero(tree_ptr *radice, char *espr)
{
		char c;
      int top=-1;
      int i=0;
      tree_ptr app;

	while((c=espr[i]) != '\0')
   {
   	app=(tree_ptr)malloc(sizeof(tree));
      app->key=c;
      app->figlio_sx=app->figlio_dx=NULL;
      if(c== '+' || c== '-' || c== '*' || c== '/')
      {
      	app->figlio_dx=pop(&top);
      	app->figlio_sx=pop(&top);
      }
      push(&top,app);
      i++;
   }
   *radice=stack[top];
}

void inorder(tree_ptr radice)
{
	if(radice)
   {
   	inorder(radice->figlio_sx);
		printf("%c ",radice->key);
   	inorder(radice->figlio_dx);
   }
}

void preorder(tree_ptr radice)
{
	if(radice)
   {
		printf("%c ",radice->key);
   	preorder(radice->figlio_sx);
   	preorder(radice->figlio_dx);
   }
}

void postorder(tree_ptr radice)
{
	if(radice)
   {
   	postorder(radice->figlio_sx);
   	postorder(radice->figlio_dx);
		printf("%c ",radice->key);
   }
}

void levelorder(tree_ptr radice)
{
		int davanti=0;
      int dietro=0;

	if(!radice)	return;
   addc(davanti,&dietro,radice);
   for(;;)
   {
   	radice=delc(&davanti,dietro);
      if(radice)
      {
      	printf("%c ",radice->key);
         if(radice->figlio_sx)
         	addc(davanti,&dietro,radice->figlio_sx);
         if(radice->figlio_dx)
         	addc(davanti,&dietro,radice->figlio_dx);
      }
      else break;
   }
}

/*FUNZIONI STACK */

void push(int *top, tree_ptr ele)
{
	if(!stack_full(*top))
   	stack[++(*top)]=ele;
   else printf("\nERRORE: Stack PIENO");
}

tree_ptr pop(int *top)
{
	if(!stack_empty(*top))
   	return(stack[(*top)--]);
   else
   	printf("\nERRORE: Stack VUOTO");
   return(NULL);
}

int stack_full(int top)
{
	if(top==MaxStackSize) return(1);
	return(0);
}

int stack_empty(int top)
{
	if(top==-1) return(1);
	return(0);
}

/* FUNZIONI CODA */

void addc(int davanti, int *dietro, tree_ptr item)
{
	*dietro=(*dietro+1)%MaxCodaSize;
   if(davanti==*dietro) return;
   coda[*dietro]=item;
}

tree_ptr delc(int *davanti, int dietro)
{
	if(*davanti==dietro) return(NULL);
	*davanti=(*davanti+1)%MaxCodaSize;
	return(coda[*davanti]);
}

