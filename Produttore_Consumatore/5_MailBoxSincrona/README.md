## Produttore-Consumatore con coda di messaggi sincrona

Nel problema produttore-consumatore, abbiamo due categorie di processi:

- **Produttori**, che scrivono un messaggio su una coda di messaggi asincrona
- **Consumatori**, che prelevano il messaggio da una coda di messaggi asincrona

Ciascuno dei due processi deve attendere, per completare la sua azione, l’arrivo del segnale dell’altro processo.

### Esercizio

I vincoli che caratterizzano il problema produttore-consumatore con coda di messaggi sincrona sono i seguenti:

- Il produttore non può produrre un messaggio prima che qualche consumatore abbia letto il messaggio precedente.
- Il consumatore non può prelevare alcun messaggio fino a che un produttore non l’abbia depositato.

La produzione ed il consumo avvengono rispettivamente all'interno delle procedure:

```c
void Produttore(MailBox,int);
void Consumatore(MailBox,int);
```
dove, il primo argomento è un puntatore a interi della Struct, 
mentre il secondo parametro indica il descrittore della coda di messaggi (MailBox) 
da utilizzare per lo scambio di messaggi tra produttore e consumatore.

La struttura struct contenente i tipi di messaggio da inviare:

```c
typedef struct {
	long tipo;	
	int intero;
	char carattere;
	int array[DIM_INT];
	char stringa[DIM_STRING];	
} MailBox;
```
dove:

- **long tipo** identifica il tipo di messaggio, e deve essere sempre un intero positivo ``long``.
- **int intero**, un elemento di tipo ``int``contenente il messaggio da inviare;
- **char carattere**, un elemento di tipo ``char``contenente il messaggio da inviare;
- **int array[DIM]**, un array di elementi di tipo ``int``contenente il messaggio da inviare;
- **char stringa[DIM]**, un array di elementi di tipo ``char``contenente il messaggio da inviare;

La MailBox viene Creata all'interno del MainMailBoxSinc.c e inizializzata in MailBoxSincrona.c

```c
key_t Chiave_CODA = ftok ("./MailBoxSincrona",'M'); // chiave della coda messaggio
key_t Chiave_CODA1 = ftok ("./MailBoxSincrona",'M');	// chiave della coda messaggio
key_t Chiave_CODA2 = ftok ("./MailBoxSincrona",'M');	// chiave della coda messaggio
int ds_coda = msgget(Chiave_CODA,IPC_CREAT|0664);
ds_coda1=msgget(Chiave_CODA1,IPC_CREAT|0664);
ds_coda2=msgget(Chiave_CODA2,IPC_CREAT|0664);
if(ds_coda<0) { perror("MailBox errore"); exit(1); }
if(ds_coda1<0) { perror("MailBox1 errore"); exit(1); }
if(ds_coda2<0) { perror("MailBox2 errore"); exit(1); }
MailBox m; //Struct 
msgctl(ds_coda,IPC_RMID,0);// rimozione chiave della MailBox
msgctl(ds_coda1,IPC_RMID,0);// rimozione chiave della MailBox
msgctl(ds_coda2,IPC_RMID,0);// rimozione chiave della MailBox
```

Le funzioni principali di funzionamento della Mailbox sono:

```c
/*MailBoxSincrona.h*/
#define REQUEST_TO_SEND 1
#define OK_TO_SEND 2
#define MESSAGGIO 3
static int ds_coda1;
static int ds_coda2;

/*MailBoxSincrona.c*/
void Produttore(MailBox m, int ds_coda){
MailBox m1,m2;
m.tipo=MESSAGGIO;
// Send Sincrona :
m1.tipo=REQUEST_TO_SEND;
// invio messaggio RTS
msgsnd(ds_coda1,&m1,sizeof(MailBox)-sizeof(long),0);	
// ricezione OTS
msgrcv(ds_coda2,&m2,sizeof(MailBox)-sizeof(long),OK_TO_SEND,0);
// invio messaggio
msgsnd(ds_coda,&m,sizeof(MailBox)-sizeof(long),0);
}
void Consumatore(MailBox m, int ds_coda) {
MailBox m1,m2
// Receive Bloccante
msgrcv(ds_coda1,&m1,sizeof(MailBox)-sizeof(long),REQUEST_TO_SEND,0);	// costruzione messaggio OTS
m2.tipo=OK_TO_SEND;
msgsnd(ds_coda2,&m2,sizeof(MailBox)-sizeof(long),0);
// ricezione messaggio
int tipomess= MESSAGGIO;
msgrcv(ds_coda,&m,sizeof(MailBox)-sizeof(long),tipomess,0);
}
```

I messaggi inviati sono:
- Un intero generato tramite la funzione ``rand()`` 
```c
m.intero = 1 + rand () % 999; // Valore casuale da 1 a 1.000
printf("Messaggio Inviato(int intero) = [%d]\n",m.intero);
```
- Un carattere generato da una funzione ``rand()``
```c
m.carattere= 'A' + (rand () % 26) ; // Valore casuale da 'A' a 'Z'
printf("Messaggio Inviato(char carattere) = [%c]\n",m.carattere);
```
- Un array di interi generato da una funzione ``rand()`` 
```c
for(int i=0;i<DIM_INT;i++) {
	m.array[i] = 1 + rand() % 999; // Valore casuale da 1 a 1.000 per DIM volte
}
printf("Messaggio Inviato(int array[DIM]) = ");
for(int i=0;i<DIM_INT;i++) printf("[%d]",m.array[i]);
printf("\n");
```
- Una stringa di caratteri generata da una funzione ``rand()``
```c
for(int i=0;i<DIM_STRING;i++) { 
	m.stringa[i]= 'A' + rand () % 26; // Valore casuale da 'A' a 'Z' per DIM volte
}
printf("Messaggio Inviato(char stringa) = [%s]\n",m.stringa);
```

Esecuzione Programma Da Terminale:
```console
$ make
gcc -c MainMailBoxSinc.c
gcc -c MailBoxSincrona.c
gcc -o MailBoxSinc MainMailBoxSinc.o MailBoxSincrona.o
$ ./MailBoxSinc
	PRODUTTORE[1]
Messaggio Inviato(int intero) = [395]
Messaggio Inviato(char carattere) = [V]
Messaggio Inviato(int array[DIM]) = [400][15][365]
Messaggio Inviato(char stringa) = [RMYIFS]
	CONSUMATORE[1]
Messaggio Ricevuto(int intero) = [395]
Messaggio Ricevuto(char carattere) = [V]
Messaggio Ricevuto(int array[DIM]) = [400][15][365]
Messaggio Ricevuto(char stringa) = [RMYIFS]
	PRODUTTORE[2]
Messaggio Inviato(int intero) = [32]
Messaggio Inviato(char carattere) = [N]
Messaggio Inviato(int array[DIM]) = [535][795][409]
Messaggio Inviato(char stringa) = [SIRYBD]
	CONSUMATORE[2]
Messaggio Ricevuto(int intero) = [32]
Messaggio Ricevuto(char carattere) = [N]
Messaggio Ricevuto(int array[DIM]) = [535][795][409]
Messaggio Ricevuto(char stringa) = [SIRYBD]
$ make clean
rm -f *.o
rm -f ./MailBoxSinc
```
