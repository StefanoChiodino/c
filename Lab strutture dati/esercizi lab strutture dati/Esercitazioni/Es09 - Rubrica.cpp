#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MaxNumSize 15
#define MaxNameSize 40



typedef struct elemento
{
	char num[MaxNumSize];
	char nome[MaxNameSize];
   struct elemento *next;
   struct elemento *prev;
} ele;

typedef struct elemento *ptr;

typedef struct t_rec {
	char nome[MaxNameSize];
   char num[MaxNumSize];
} rec;

void menu(void);
void printrub(ptr);
void scroll_rub(ptr *, ptr *);
void addvoce_sort(ptr *, ptr *, char *nome, char *num);
void inserisci(ptr *, ptr *);
void edit(ptr *, ptr *);
void load(ptr *, ptr *, FILE *);
void save(ptr, FILE *);
void ricerca(ptr);
void edit2(ptr);
void getdato(char *);
int del(ptr *, ptr *, char *);

void main() {

ptr inizio=NULL;
ptr fine=NULL;

FILE *fp;

int scelta;
char dato[MaxNameSize];
int canc;
   do
   {
		menu();
      scanf("%d",&scelta);
      switch(scelta)
      {
   		case 1: { inserisci(&inizio,&fine);  break; }
			case 2: { ricerca(inizio);  break; }
      	case 3: { edit(&inizio,&fine); break; }
			case 4: { if (inizio!=NULL) {
         				getdato(dato);
         			 	canc=del(&inizio,&fine,dato);
                   	if(canc==0) printf("\n\nNominativo Non Presente!");
                     if(canc==1) printf("\n\nNominativo Eliminato");
         			 }
                   else printf("\n\nRubrica Vuota! Premere un tasto per tornare al menu principale");
                   break;
         			}
      	case 5: { scroll_rub(&inizio,&fine); break; }
      	case 6: { printrub(inizio); break; }
      	case 7: { save(inizio,fp); break; }
      	case 8: {load(&inizio,&fine,fp); break; }
      	case 0: break;
         default: { printf("\nScelta errata!"); break; }
      }
    	fflush(stdin);
      getchar();
		fflush(stdin);
   }
   while(scelta!=0);

}

void menu(void)
{
   clrscr();
	printf("\n # # # # # # # # # # # # RUBRICA TELEFONICA # # # # # # # # # # # #\n\n");
   printf("\n1 - Inserire nuovi nominativi");
   printf("\n2 - Ricerca Nominativo");   
   printf("\n3 - Modifica Nominativo");
   printf("\n4 - Cancella Nominativo");   
   printf("\n5 - Scorri Rubrica");
   printf("\n6 - Visualizza il contenuto della rubrica");
	printf("\n7 - Salva Modifiche");
	printf("\n8 - Carica Rubrica");
   printf("\n0 - Esci");
   printf("\n\nScelta: ");
}

void printrub(ptr p) {

   if(p)
	while(p)
   {
   	printf("\n\nNome:   %s",p->nome);
   	printf("\nNumero: %s",p->num);
      p=p->next;
   }
   else printf("\nRubrica vuota");
}

void addvoce_sort(ptr *inizio, ptr * fine, char *nome, char *num) {

	ptr p=*inizio;
	ele *app;

	app=(ele *)malloc(sizeof(ele));
   app->next=NULL;
   app->prev=NULL;
   strcpy(app->nome,nome);
   strcpy(app->num,num);

	if (p==NULL) {
   	*inizio=*fine=app;
   }
   else {

	   while(p!=NULL && strcmp(p->nome,nome)<0) p=p->next;
      if(p==NULL) {
      	app->prev=*fine;
         app->prev->next=app;
         *fine=app;
      }
      else
      	if(p==*inizio) {
         	app->next=*inizio;
            p->prev=app;
            *inizio=app;
         }
         else {
         	app->next=p;
            app->prev=p->prev;
            p->prev->next=app;
            p->prev=app;
         }

   }

}


void scroll_rub(ptr *inizio, ptr *fine) {
char scelta;
ptr p=*inizio;

   if (p!=NULL) {
		do {
     		clrscr();
	     	printf("\nPremi 'q' per tornare al menu principale.");
  	     	printf("\nPremi 'e' per accedere alla modalita di modifica del nome visualizzato\n\n\n");
	      printf("\t\t\t\t      /\\ w \n\n");
	      printf("\t\t\t      %s: %s",p->nome,p->num);
	      printf("\n\n\t\t\t\t      \\/ s\n\n");
	      scelta=getch();
	     	if(scelta=='s') {
     	 		if(p->next==NULL) p=*inizio;
	     	 	else p=p->next;
   	  	}
     	 	else
     	 		if(scelta=='w') {
     	    		if(p->prev==NULL) p=*fine;
     	     	  	else p=p->prev;
     	    	}
            else {
            	if(scelta=='e') {
               	edit2(p);
               }
            }

   	}
   	while(scelta!='q');
   }
   else printf("Rubrica Vuota! Premere un tasto per tornare al menu principale");



}


void inserisci(ptr *inizio, ptr *fine) {
char nome[MaxNameSize], num[MaxNumSize];
int flag;
	do {
		fflush(stdin);
      clrscr();
      printf("\nPer Terminare l'inserimento scrivere 'quit' nel nome\n");
		printf("\nNome: ");
		gets(nome);
      if((flag = strcmp(nome,"quit"))!=0) {
			printf("Numero: ");
			gets(num);
			addvoce_sort(inizio,fine,nome,num);
      }
   }
   while(flag!=0);

}


void edit(ptr *inizio, ptr *fine) {
char nome[MaxNameSize];
char num[MaxNumSize];
ptr p=*inizio;
   clrscr();
   fflush(stdin);
	if(p!=NULL) {
		printf("\n\t\tMODIFICA NOMINATIVO");
	   printf("\nInserisci il nome relativo al contatto che vuoi modifiacare\n Nome: ");
	   gets(nome);
      while(p!=NULL && strcmp(p->nome,nome)!=0) p=p->next;
      if(p==NULL) {
      	printf("\nNominativo non presente in rubrica!! Premere un tasto per tornare al menu principale.");
         getchar();
      }
      else {
         printf("\nInserire NUOVO numero: ");
         gets(num);
			strcpy(p->num,num);
         printf("\nNominativo Modificato! Premere un tasto per tornare al menu principale");
      }
	}
   else printf("\nRubrica vuota! Premere un tasto per tornare al menu principale");
}



void load(ptr *inizio, ptr *fine, FILE *fp) {
rec app;
	fp=fopen("rubrica.bin","rb");
   if(fp==NULL) {printf("Impossibile caricare la rubrica. FILE NON PRESENTE.\n");}
   else {
   	clrscr();
   	while(!feof(fp)) {
         fread(&app,sizeof(rec),1,fp);
         if(!feof(fp)) addvoce_sort(inizio,fine,app.nome,app.num);
      }
      printf("\nLa rubrica e' stata caricata in memoria");

   }
   fclose(fp);
}


void save(ptr inizio, FILE *fp) {
rec app;
	if(inizio==NULL) printf("La rubrica e' vuota! Impossibile Salvare.");
   else {
	   fp=fopen("rubrica.bin","wb");
		while(inizio!=NULL) {
   	   strcpy(app.nome,inizio->nome);
	      strcpy(app.num,inizio->num);
   		fwrite(&app,sizeof(rec),1,fp);
     		inizio=inizio->next;
   	}
      fclose(fp);
      printf("\nSALVATAGGIO AVVENUTO CON SUCCESSO!");
   }
}


void ricerca(ptr inizio) {
char find[80];

	clrscr();

   if(inizio==NULL) printf("RUBRICA VUOTA! Premi un tasto per tornare al menu principale");
   else {
   	fflush(stdin);
	   printf("\nInserisci il nome o il numero da ricercare all'interno della rubrica");
   	printf("\nCerca: ");
	   gets(find);
      while(inizio!=NULL && strcmp(find,inizio->nome)!=0 && strcmp(find,inizio->num)!=0) {
      	inizio=inizio->next;
      }

      if(inizio==NULL) {
      	printf("\nNessun dato trovato per la ricerca %s",find);
      }
      else {
      	printf("\n %s\n %s",inizio->nome, inizio->num);
      }
   }


}



void edit2(ptr p) {
char num[MaxNumSize];
   fflush(stdin);
	printf("\n\nModalita modifica\n");
	printf("%s: %s",p->nome,p->num);
	printf("\nNuovo numero: ");
   gets(num);
   strcpy(p->num,num);
   printf("\nModifica eseguita! Continua a scorrere con w o s o torna al menu principale con q");
}


void getdato(char *dato) {
   fflush(stdin);
	printf("\nInserire nome o numero del contatto che si vuole cancellare.");
   printf("\nCancella: ");
   gets(dato);


}


int del(ptr *inizio, ptr *fine, char *dato) {
ptr p=*inizio;
	if(inizio!=NULL) {
   	while(p!=NULL && strcmp(p->nome,dato)!=0 && strcmp(p->num,dato)!=0)
      	p=p->next;
      if(p==NULL) return(0);
      	else {
         	if(p==*inizio && *inizio==*fine) {
            	*inizio=NULL; *fine=NULL;
               free(p);
            }
            else if(p==*inizio) {
                  	*inizio=p->next;
                     p->next->prev=NULL;
                     free(p);
            		}
                  else if(p==*fine) {
                        	*fine=p->prev;
                           p->prev->next=NULL;
                           free(p);
                  		}
                        else {
                        	p->prev->next=p->next;
                           p->next->prev=p->prev;
                           free(p);
                        }
         return(1);
         }

   }
   else
   	return(-1);



}
