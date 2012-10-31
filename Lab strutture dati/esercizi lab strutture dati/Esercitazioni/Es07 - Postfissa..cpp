#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum {parensx,parendx,plus,meno,per,dividi,mod,eos,operando}precedenza;
int stack[MAX_STACK_SIZE];
char espr[MAX_EXPR_SIZE];
char espr_post[MAX_EXPR_SIZE];
static int prd[]={0,9,12,12,13,13,13,0};
static int prf[]={20,19,12,12,13,13,13,0};

void postfix(void);
int valuta(void);
void add(int *,int);
int del(int *);
char print_token(precedenza);
int get_token(char *,int *);

main()
{
 int tot;

 printf("Inserisci l'espressione: ");
 scanf("%[^\n]",espr);
 espr[strlen(espr)]=' ';
 puts(espr);
 getchar();
 postfix();
 strcpy(espr,espr_post);
 tot=valuta();
 printf("Risultato: %d", tot);

 fflush(stdin);
 getchar();
}

void postfix(void)
{
 char simbolo,buf;
 precedenza token;
 int n=0,top=0,counter=-1;

 stack[0]=eos;
 for(token=get_token(&simbolo,&n);token!=eos;token=get_token(&simbolo,&n))
 {
  if(token==operando)
   espr_post[++counter]=simbolo;
  else
   if (token==parendx)
   {
    while (stack[top]!=parensx)
    {
     buf=print_token(del(&top));
     espr_post[++counter]=buf;
    }
    del(&top);
   }
   else
   {
    while(prd[stack[top]] >= prf[token])
    {
     buf=print_token(del(&top));
     espr_post[++counter]=buf;
    }
    add(&top,token);
   }
 }
 while ((buf=print_token(del(&top))) != '\0')
 	espr_post[++counter]=buf;
 espr_post[++counter]='\0';

 printf("espressione post_fix: ");
 for(n=0;n<=counter;n++)
  	printf("%c",espr_post[n]);
}

int valuta(void)
{
 precedenza token;
 char simbolo;
 int op1,op2,n=0,top=-1;

 token=get_token(&simbolo, &n);
 while(token != eos)
 {
  if(token == operando)
  	add(&top,simbolo-'0');
  else
  {
  	op2=del(&top);
   op1=del(&top);
   switch (token)
   {
    case plus   : add(&top, op1+op2);
    				   break;
    case meno   : add(&top, op1-op2);
    				   break;
    case per    : add(&top, op1*op2);
    				   break;
    case dividi : add(&top, op1/op2);
    				   break;
    case mod    : add(&top, op1%op2);
    				   break;
   }
  }
  token=get_token(&simbolo, &n);
 }
 return del(&top);
}


int get_token(char *simbolo,int *n)
{
 *simbolo=espr[(*n)++];
 switch(*simbolo)
 {
  case '(' : return parensx;
  case ')' : return parendx;
  case '+' : return plus;
  case '-' : return meno;
  case '/' : return dividi;
  case '*' : return per;
  case '%' : return mod;
  case ' ' : return eos;
  default  : return operando;
 }
}

char print_token(precedenza simbolo)
{
 switch(simbolo)
 {
  case parensx : return '(';
  case parendx : return ')';
  case plus    : return '+';
  case meno    : return '-';
  case dividi  : return '/';
  case per     : return '*';
  case mod     : return '%';
  case eos     : return ' ';
  default      : return '\0';
 }
}


void add(int *top,int item)
{
 if(*top>=MAX_STACK_SIZE-1)
 {
  printf("\nStack pieno!");
  return;
 }
 stack[++*top]=item;
}

int del(int *top)
{
 if(!(*top==-1))
	 return stack[(*top)--];
}
