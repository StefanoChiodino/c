#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_ELEMENTI 200
#define MAX_STR_SIZE 80


typedef struct t_ele {
	char chiave[MAX_STR_SIZE];
} elemento;

elemento heap[MAX_ELEMENTI];
int n=0;


int heap_full(int);
int insert(void);
void upheap(void);
elemento delheap(int *);
void printheap(void);

void load();
void save(void);

void menu(void);


int main() {
int scelta;

	load();
   printf("");

	do {
   	fflush(stdin);
		menu();
      scanf("%d",&scelta);
      switch(scelta) {
      	case 1: { insert(); break; }
         case 2: { delheap(&n); break;
         }
         case 3: { printheap(); break; }
         case 0: { save(); printf("\nPREMERE UN TASTO PER USCIRE..."); break;}

      	default: { printf("\nATTENZIONE! SCELTA ERRATA!"); }
      }
      fflush(stdin);
      getchar();
   }
   while(scelta != 0);

}



void menu(void) {
   printf("\n\t\t^^^^^^^^^^^^^^^^^^ HEAP ^^^^^^^^^^^^^^^^^^");
	printf("\n\n\n\t\t\t1- INSERIRE NUOVO NOME");
	printf("\n\t\t\t2- ELIMINARE PRIMO NOME");
	printf("\n\t\t\t3- VISUALIZZA LISTA");
	printf("\n\t\t\t0- ESCI");
   printf("\n\n\t\tScelta: ");
}


int heap_full(int n) {
	return(n==MAX_ELEMENTI-1);
}


int insert(void) {

	if (heap_full(n)) return 1;
	printf("Nome da inserire (max 80 carat.): ");
	scanf("%s", heap[++n].chiave);
	if(n>0) upheap();
	return 0;
}

void upheap(void) {
  char item[20];
  int i;

  i=n;
  strcpy(item,heap[n].chiave);
  while (i !=1 && (strcmp(item,heap[i/2].chiave) >0) ) {
  		strcpy(heap[i].chiave,heap[i/2].chiave);i=i/2;
  }
  strcpy(heap[i].chiave,item);
}


elemento delheap(int *n)
{
		int padre, figlio;
		elemento item, temp;

	if(*n>0)
   {
   	item=heap[1];
      temp=heap[(*n)--];
	 	padre=1;
      figlio=2;
      while(figlio<=*n)
      {
      	if(figlio<*n && heap[figlio].chiave < heap[figlio+1].chiave)
         	figlio++;
         if(strcmp(temp.chiave,heap[figlio].chiave)>0)
         	break;
         heap[padre]=heap[figlio];
         padre=figlio;
         figlio=figlio*2;
      }
   heap[padre]=temp;
   return(item);
   }
   else { fprintf(stderr,"Heap vuoto!"); /*exit(1);*/ }
}


void printheap(void) {
int i;
   if(n>0)
		for(i=1;i<=n;i++) printf("\n%s",heap[i].chiave);
   else printf("\nALBERO VUOTO!!");

}

void load() {
FILE *fp;
elemento app;

	n=1;
	fp=fopen("nomi.bin","rb");
   if(fp==NULL) { printf("FILE NOMI NON PRESENTE. LA LISTA SARA' VUOTA.\nPremere un tasto per andare al menu principale"); getchar(); }
   else {
   	while(!feof(fp)) {
         fread(&app,sizeof(elemento),1,fp);
         if(!feof(fp)) { heap[n++]=app;}
      }
      printf("\nNOMI CARICATI.\nPremere un tasto per andare al menu principale");
      getchar();

   }
   fclose(fp);
}


void save() {
FILE *fp;
elemento app;
int i=1;

	if(n==0) printf("La rubrica e' vuota! Impossibile Salvare.");
   else {
	   fp=fopen("nomi.bin","wb");
		while(i<=n) {
   	   app=heap[i];
   		fwrite(&app,sizeof(elemento),1,fp);
     		i++;
   	}
      fclose(fp);
      printf("\nLISTA NOMI SALVATA CON SUCCESSO");
   }
}


