## Esercizio. Chat Multiprocesso

Scrivere un programma basato su code di messaggi UNIX per consentire la conversazione tra utenti del sistema. 
- Il programma deve essere un eseguibile che due utenti (su due terminali distinti) eseguono per poter conversare.
- Il programma deve accettare in ingresso dalla linea di comando una coppia di caratteri da utilizzare
  come identificativi delle code da usare per le conversazioni
  es: **./chat a b (Primo Terminale)  ./chat b a (Secondo Terminale)**
- Il programma dovrà instanziare due processi figli, MIttente e Ricevente, dove:

  **(MITTENTE)**: esegue in loop in cui ad ogni iterazione si mette in attesa di una stringa dallo standart input
				     ed invia un messaggio con la stringa sulla prima coda. Quando l'utente inserisce 'exit'
				     il programma deve inviare un messaggio con una stringa 'exit' sulla seconda coda e terminare
				     
  **(RICEVENTE)**: esegue in loop in cui ad ogni iterazione si mette in attesa di un messaggio dalla seconda coda
								   e appena ricevuta stamperà sullo standart output la stringa ricevuta. In caso di ricezione della 
								   stringa 'exit' dovrà terminare
								   
![image](https://user-images.githubusercontent.com/93724872/143234187-26364783-5594-4445-8d3f-ae21bb58ab60.png)

[1]: Se un mittente ed un ricevente usano gli stessi caratteri di ingresso, 
        essi devono poter comunicare tra loro usando le stesse code di messaggi condivise. 
        Se invece un mittente e un ricevente usano caratteri di ingresso diversi,
        essi useranno code diverse e non potranno comunicare tra loro. 
[2]: Si utilizzi la funzione scanf() per leggere una stringa dallo standard input.

**(N° del Processo, Valore_Float(Singolo), Valore_Char(Singolo), Valore_Array, Valore_Stringa )**
Il processo P3 riceve dalla coda i messaggi, 5 da P1 e 5 da P2 e calcola la media dei valori float ricevuto stampandola a terminale
L'esecuzione del programma deve essere esterna mediante exec

La struttura struct contenente i tipi di messaggio da inviare:

```c
/*CodaMessaggi.h*/
typedef struct {
	long tipo;
	float intero;
	char carattere;
	int array[DIM_INT];
	char stringa[DIM_STRING];	
}Coda;
```

dove:

- (1) **N° del Processo** identificato con **long tipo** è la stringa `P1` o `P2` (a seconda del processo), 
dichiarata in CodaMessaggi.h e richiamata nei processi

```c
/*CodaMessaggi.h*/
#define p1 1
#define p2 2
typedef struct {
	long tipo;
	
/*Processo1.c*/
Coda c; //STRUCT DELLA CODA
c.tipo=p1;

/*Processo2.c*/
Coda c; //STRUCT DELLA CODA
c.tipo=p2;
```

- (2) **float intero**, un elemento di tipo ``float``contenente il messaggio da inviare e definito in CodaMessaggi.c
e richiamato in Processo1.c e Processo2.c

```c
/*CodaMessaggi.c*/
float GeneraValore(int MIN, int MAX){
//GENERA VALORE DA UN MIN E UN MAX
float x = (int) (int) (rand () + MIN) / (RAND_MAX / MAX);
return x;
}

/*Processo1.c*/
//Genera Valori Da 1 a 10
c.intero=GeneraValore(1,10); 

/*Processo2.c*/
//Genera Valori Da 1 a 20
c.intero=GeneraValore(1,20);
```

- (3) **char carattere**, un elemento di tipo ``char``contenente il messaggio da inviare e definito in CodaMessaggi.c
e richiamato in Processo1.c e Processo2.c

```c
/*CodaMessaggi.c*/
char GeneraCarattere(char CARATTERE,int MAX){	
//GENERA UN CARATTERE CASUALE
char string = (char) (int) CARATTERE + (rand () % MAX);
return string;
}

/*Processo1.c*/
//Genera Caratteri da 'G' a 'I'
c.carattere=GeneraCarattere('G',3);

/*Processo2.c*/
//Genera Caratteri da 'A' a 'D'
c.carattere=GeneraCarattere('A',4);
```

- (4) **int array[DIM]**, un array di elementi di tipo ``int``contenente il messaggio da inviare e definito nei Processi 1 e 2;

```c
/*CodaMessaggi.h*/
#define DIM_INT 2

/*Processo1.c*/ 
//Genera Valori Da 1 a 25 
for(int i=0;i<DIM_INT;i++) { c.array[i]= 1 + rand () % 25;}

/*Processo2.c*/ 
//Genera Valori Da 10 a 20 
for(int i=0;i<DIM_INT;i++) { c.array[i]= 10 + rand () % 11;}
```

- (5) **char stringa[DIM]**, un array di elementi di tipo ``char``contenente il messaggio da inviare e definito nei Processi 1 e 2;

```c
/*CodaMessaggi.h*/
#define DIM_STRING 3

/*Processo1.c*/ 
//Genera Caratteri da 'R' a 'U'
for(int i=0;i<DIM_STRING;i++) {c.stringa[i] = 'R' + (rand () % 4);}
c.stringa[DIM_STRING-1]='\0'; //CARATTERE TERMINALE

/*Processo2.c*/ 
//Genera Caratteri da 'A' a 'G'
for(int i=0;i<DIM_STRING;i++) {c.stringa[i] = 'A' + (rand () % 7);}
c.stringa[DIM_STRING-1]='\0'; //CARATTERE TERMINALE
```

La Coda di messaggi viene Creata all'interno dei Processi(p1.c,p2.c,p3.c) e deve avere lo stesso nome in tutti i processi

```c
/*Processo1.c,Processo2.c,Processo3.c*/ 
key_t Chiave_Coda = ftok (".",'p');	// chiave della coda messaggio
int ds_coda = msgget (Chiave_Coda,IPC_CREAT | 0664);
if(ds_coda<0) { perror("Coda_1 Error"); exit(1); } // cambia solo il nome dell'errore in base al processo
Coda c; //Struct 
msgctl(ds_coda,IPC_RMID,0); // rimozione chiave viene messa solo in Processo3.c
```

Le funzioni principali di funzionamento della Coda di messaggi sono:

```c
/*CodaMessaggi.h*/
#define p1 1
#define p2 2
#define DIM_MSG_p1 5
#define DIM_MSG_p2 5

/*Processo1.c*/
int check;
c.tipo=p1;
// invio 5 messaggi su coda
for(int i=0;i<DIM_MSG_p1;i++){ 
check = msgsnd (ds_coda,(void*) &c,sizeof(Coda) - sizeof(long),IPC_NOWAIT); //INVIO MESSAGGIO SU CODA
if(check<0) {perror("msgsnd error");_exit(1);}
}

/*Processo2.c*/
int check;
c.tipo=p2;
// invio 5 messaggi su coda
for(int i=0;i<DIM_MSG_p2;i++){ 
check = msgsnd (ds_coda,(void*) &c,sizeof(Coda) - sizeof(long),IPC_NOWAIT); //INVIO MESSAGGIO SU CODA
if(check<0) {perror("msgsnd error");_exit(1);}
}

/*Processo3.c*/
int check;
// riceve 10 messaggi dalla coda
for(int i=0;i<DIM_MSG_p1+DIM_MSG_p2;i++){ 
check = msgrcv(ds_coda,(void*)&c,sizeof(Coda)-sizeof(long),0,0); //RICEVO MESSAGGIO SU CODA
if(check<0) {perror("msgrcv error");_exit(1);}
```

Le stampe dell'invio del Messaggio sono fatte rispettivamenti in Processo1.c e Processo2.c e sono uguali tra loro

```c
/*Processo1.c, Processo2.c*/
printf("Mesaggio Inviato<n°%d>, PROCESSO < %lu > \n",i+1,c.tipo);
printf("\tVALORE_FLOAT < %3.1f > \n",c.intero);
printf("\tVALORE_CHAR < %c >\n",c.carattere);
printf("\tVALORE_ARRAY < "); 
for(int i=0;i<DIM_INT;i++) printf("[%d] ",c.array[i]);
printf(">\n");
printf("\tVALORE_STRINGA < %s >\n",c.stringa);
```

La stampa della recezione del Messaggio è fatta in Processo3.c

```c
/*Processo3.c*/
printf("Mesaggio Ricevuto<n°%d>, PROCESSO < %lu > \n",i+1,c.tipo);
printf("\tVALORE_FLOAT < %3.1f > \n",c.intero);
printf("\tVALORE_CHAR < %c >\n",c.carattere);		
printf("\tVALORE_ARRAY < "); 
for(int i=0;i<DIM_INT;i++) printf("[%d] ",c.array[i]);
printf(">\n");
printf("\tVALORE_STRINGA < %s >\n",c.stringa);	
```

Ricevuto dalla coda il valore float il Processo3.c ne calcola la media stampandola a terminale

```c
/*Processo3.c*/
float media[2]={0}; //Ha i risultati della media
float vettore1_int[DIM_MSG_p1+DIM_MSG_p2]={0}; //Ha i valori float di P1
float vettore2_int[DIM_MSG_p1+DIM_MSG_p2]={0}; //Ha i valori float di P2
int check;
	
//Dopo la recezione dei msg dalla coda
check = msgrcv(ds_coda,(void*)&c,sizeof(Coda)-sizeof(long),0,0); 
if(check<0) {perror("msgrcv error");_exit(1);}

if(c.tipo == p1){ //Controllo per prendere solo i msg di P1
	vettore1_int[i]=c.intero;
	media[p1-1]+=c.intero / DIM_MSG_p1;
}	else if(c.tipo == p2) { //Controllo per prendere solo i msg di P2
		vettore2_int[i]=c.intero;
		media[p2-1]+=c.intero / DIM_MSG_p2;
	}
	
//Stampe dei vettori contenenti i valori di P1 e P2 e le loro Medie
printf("\nCalcolo n°1 Media, Valori tra 0 a 10\nTra: ");	
for (int i=0;i<DIM_MSG_p1+DIM_MSG_p2;i++) {
	if(vettore1_int[i]!=0){
		printf("< %3.1f > ",vettore1_int[i]);
	}
}
	
printf("= [%3.2f]\n",media[0]); //Media dei valori di P1
	
printf("\nCalcolo n°2 Media, Valori tra 1 a 20\nTra: ");
for (int i=1;i<DIM_MSG_p1+DIM_MSG_p2;i++) {
    if(vettore2_int[i]!=0){
		printf("< %3.1f > ",vettore2_int[i]);
	}
}
		
printf("= [%3.2f]\n",media[1]); //Media dei valori di P2
```

Per compilare il programma si usufrisce di un corpo MainExec.c esterno che mediante i processi creati fa l'exec

```c
/*MainExec.c*/
#include "CodaMessaggi.h"
int main(){
pid_t pid;
	
pid = fork();
if(pid==0){
	execl("./p1","./p1",NULL);
	perror("Exec Fallita");
	exit(1);	
} else if(pid<0) { perror ("Errore Fork"); exit(1); }
	
pid = fork();
if(pid==0){
	execl("./p2","./p2",NULL);
	perror("Exec Fallita");
	exit(1);	
} else if(pid<0) { perror ("Errore Fork"); exit(1); }
	
pid = fork();
if(pid==0){
	execl("./p3","./p3",NULL);
	perror("Exec Fallita");
	exit(1);	
} else if(pid<0) { perror ("Errore Fork"); exit(1); }
	
for(int i=0;i<NUM_PROCESSI;i++){
	wait(NULL);
}
		
return 0;
}
```

Il Makefile è composto in questo modo: (crea 3 eseguibili + l'eseguibile del main) 

```Makefile
all: 1_start p1 p2 p3

1_start: CodaMessaggi.h
	gcc MainExec.c CodaMessaggi.c -o 1_start

p1: CodaMessaggi.h
	gcc Processo1.c CodaMessaggi.c -o p1
	
p2: CodaMessaggi.h
	gcc Processo2.c CodaMessaggi.c -o p2
	
p3: CodaMessaggi.h
	gcc Processo3.c CodaMessaggi.c -o p3 

clean:
	rm -rf *.o
	rm -rf 1_start p1 p2 p3
```

Esecuzione Programma Da Terminale:
```console
$ make
gcc MainExec.c CodaMessaggi.c -o 1_start
gcc Processo1.c CodaMessaggi.c -o p1
gcc Processo2.c CodaMessaggi.c -o p2
gcc Processo3.c CodaMessaggi.c -o p3 
$ ./1_start 
Mesaggio Inviato<n°1>, PROCESSO < 1 > 
	VALORE_FLOAT < 1.0 > 
	VALORE_CHAR < G >
	VALORE_ARRAY < [22] [14] >
	VALORE_STRINGA < RS >
Mesaggio Ricevuto<n°1>, PROCESSO < 1 > 
	VALORE_FLOAT < 1.0 > 
	VALORE_CHAR < G >
	VALORE_ARRAY < [22] [14] >
	VALORE_STRINGA < RS >
Mesaggio Inviato<n°1>, PROCESSO < 2 > 
	VALORE_FLOAT < 14.0 > 
	VALORE_CHAR < A >
	VALORE_ARRAY < [17] [16] >
	VALORE_STRINGA < AC >
Mesaggio Ricevuto<n°2>, PROCESSO < 2 > 
	VALORE_FLOAT < 14.0 > 
	VALORE_CHAR < A >
	VALORE_ARRAY < [17] [16] >
	VALORE_STRINGA < AC >
Mesaggio Inviato<n°2>, PROCESSO < 1 > 
	VALORE_FLOAT < 4.0 > 
	VALORE_CHAR < G >
	VALORE_ARRAY < [8] [21] >
	VALORE_STRINGA < UU >
Mesaggio Ricevuto<n°3>, PROCESSO < 1 > 
	VALORE_FLOAT < 4.0 > 
	VALORE_CHAR < G >
	VALORE_ARRAY < [8] [21] >
	VALORE_STRINGA < UU >
Mesaggio Inviato<n°3>, PROCESSO < 1 > 
	VALORE_FLOAT < 3.0 > 
	VALORE_CHAR < H >
	VALORE_ARRAY < [14] [16] >
	VALORE_STRINGA < ST >
Mesaggio Ricevuto<n°4>, PROCESSO < 1 > 
	VALORE_FLOAT < 3.0 > 
	VALORE_CHAR < H >
	VALORE_ARRAY < [14] [16] >
	VALORE_STRINGA < ST >
Mesaggio Inviato<n°2>, PROCESSO < 2 > 
	VALORE_FLOAT < 3.0 > 
	VALORE_CHAR < C >
	VALORE_ARRAY < [15] [16] >
	VALORE_STRINGA < BG >
Mesaggio Ricevuto<n°5>, PROCESSO < 2 > 
	VALORE_FLOAT < 3.0 > 
	VALORE_CHAR < C >
	VALORE_ARRAY < [15] [16] >
	VALORE_STRINGA < BG >
Mesaggio Inviato<n°4>, PROCESSO < 1 > 
	VALORE_FLOAT < 7.0 > 
	VALORE_CHAR < I >
	VALORE_ARRAY < [14] [19] >
	VALORE_STRINGA < SU >
Mesaggio Ricevuto<n°6>, PROCESSO < 1 > 
	VALORE_FLOAT < 7.0 > 
	VALORE_CHAR < I >
	VALORE_ARRAY < [14] [19] >
	VALORE_STRINGA < SU >
Mesaggio Inviato<n°3>, PROCESSO < 2 > 
	VALORE_FLOAT < 3.0 > 
	VALORE_CHAR < A >
	VALORE_ARRAY < [20] [16] >
	VALORE_STRINGA < AD >
Mesaggio Ricevuto<n°7>, PROCESSO < 2 > 
	VALORE_FLOAT < 3.0 > 
	VALORE_CHAR < A >
	VALORE_ARRAY < [20] [16] >
	VALORE_STRINGA < AD >
Mesaggio Inviato<n°5>, PROCESSO < 1 > 
	VALORE_FLOAT < 5.0 > 
	VALORE_CHAR < H >
	VALORE_ARRAY < [12] [15] >
	VALORE_STRINGA < SS >
Mesaggio Ricevuto<n°8>, PROCESSO < 1 > 
	VALORE_FLOAT < 5.0 > 
	VALORE_CHAR < H >
	VALORE_ARRAY < [12] [15] >
	VALORE_STRINGA < SS >
Mesaggio Inviato<n°4>, PROCESSO < 2 > 
	VALORE_FLOAT < 13.0 > 
	VALORE_CHAR < C >
	VALORE_ARRAY < [16] [11] >
	VALORE_STRINGA < BA >
Mesaggio Ricevuto<n°9>, PROCESSO < 2 > 
	VALORE_FLOAT < 13.0 > 
	VALORE_CHAR < C >
	VALORE_ARRAY < [16] [11] >
	VALORE_STRINGA < BA >
Mesaggio Inviato<n°5>, PROCESSO < 2 > 
	VALORE_FLOAT < 12.0 > 
	VALORE_CHAR < A >
	VALORE_ARRAY < [17] [15] >
	VALORE_STRINGA < AC >
Mesaggio Ricevuto<n°10>, PROCESSO < 2 > 
	VALORE_FLOAT < 12.0 > 
	VALORE_CHAR < A >
	VALORE_ARRAY < [17] [15] >
	VALORE_STRINGA < AC >

Calcolo n°1 Media, Valori tra 1 a 10
Tra: < 1.0 > < 4.0 > < 3.0 > < 7.0 > < 5.0 > = [2.60]

Calcolo n°2 Media, Valori tra 1 a 20
Tra: < 14.0 > < 3.0 > < 3.0 > < 13.0 > < 12.0 > = [9.00]
$ make clean
rm -rf *.o
rm -rf 1_start p1 p2 p3
```
