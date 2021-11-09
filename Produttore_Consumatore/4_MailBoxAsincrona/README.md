## Produttore-Consumatore con coda di messaggi asincrona

Nel problema produttore-consumatore, abbiamo due categorie di processi:

- **Produttori**, che scrivono un messaggio su una coda di messaggi asincrona
- **Consumatori**, che prelevano il messaggio da una coda di messaggi asincrona

Ciascuno dei due processi deve attendere, per completare la sua azione, l’arrivo del segnale dell’altro processo.

### Esercizio

I vincoli che caratterizzano il problema produttore-consumatore con coda di messaggi asincrona sono i seguenti:

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
	int array[DIM_INT];
	char carattere;
	char stringa[DIM_STRING];
} MailBox;
```
dove:

- **long tipo** identifica il tipo di messaggio, e deve essere sempre un intero positivo ``long``.
- **int intero**, un elemento di tipo ``int``contenente il messaggio da inviare;
- **char carattere**, un elemento di tipo ``char``contenente il messaggio da inviare;
- **int array[DIM]**, un array di elementi di tipo ``int``contenente il messaggio da inviare;
- **char stringa[DIM]**, un array di elementi di tipo ``char``contenente il messaggio da inviare;

La MailBox viene Creata all'interno del MainMailBoxAsinc.c

```c
key_t Chiave_CODA = ftok ("./MailBoxAsinc",'M');	// chiave della coda messaggio
int ds_coda =msgget(Chiave_CODA,IPC_CREAT|0664);
if(ds_coda<0) { perror("MailBox errore"); exit(1); }
MailBox m; //Struct 
msgctl(ds_coda,IPC_RMID,0);// rimozione chiave della MailBox
```

Le funzioni principali di funzionamento della Mailbox sono:

```c
/*MailBoxAsincrona.h*/
#define MESSAGGIO 1

/*MailBoxAsincrona.c*/
void Produttore(MailBox m, int ds_coda){
m.tipo=MESSAGGIO;
	// invio messaggio
msgsnd(ds_coda,(void*)&m,sizeof(MailBox)-sizeof(long),IPC_NOWAIT);
}
void Consumatore(MailBox m, int ds_coda) {
	// ricezione messaggio
msgrcv(ds_coda,(void *) &m,sizeof(MailBox)-sizeof(long),MESSAGGIO,0);
}
```

I messaggi inviati sono:
- Un intero generato tramite la funzione ``rand()`` 
```c
m.intero = 1 + rand () % 99; // Valore casuale da 1 a 1.000
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
gcc -c MainMailBoxAsinc.c
gcc -c MailBoxAsincrona.c
gcc -o MailBoxAsinc MainMailBoxAsinc.o MailBoxAsincrona.o
$ ./MailBoxAsinc
	PRODUTTORE[1]
Messaggio Inviato(int intero) = [508]
Messaggio Inviato(char carattere) = [B]
Messaggio Inviato(int array[DIM]) = [189][189][769]
Messaggio Inviato(char stringa) = [TXIVDP]
	CONSUMATORE[1]
Messaggio Ricevuto(int intero) = [508]
Messaggio Ricevuto(char carattere) = [B]
Messaggio Ricevuto(int array[DIM]) = [189][189][769]
Messaggio Ricevuto(char stringa) = [TXIVDP]
	PRODUTTORE[2]
Messaggio Inviato(int intero) = [944]
Messaggio Inviato(char carattere) = [G]
Messaggio Inviato(int array[DIM]) = [556][961][304]
Messaggio Inviato(char stringa) = [KCQWCC]
	CONSUMATORE[2]
Messaggio Ricevuto(int intero) = [944]
Messaggio Ricevuto(char carattere) = [G]
Messaggio Ricevuto(int array[DIM]) = [556][961][304]
Messaggio Ricevuto(char stringa) = [KCQWCC]
$ make clean
rm -f *.o
rm -f ./MailBoxAsinc
```
