## Produttore-Consumatore con pool di buffer gestito con vettore di stato

Nel problema produttore-consumatore, abbiamo due categorie di processi:

- **Produttori**, che scrivono un messaggio su di una risorsa condivisa
- **Consumatori**, che prelevano il messaggio dalla risorsa condivisa

Ciascuno dei due processi deve attendere, per completare la sua azione, l’arrivo del segnale dell’altro processo.

### Esercizio

I vincoli che caratterizzano il problema produttore-consumatore con pool di buffer con vettore di stato sono i seguenti:

- Il produttore non può produrre un messaggio prima che qualche consumatore abbia letto il messaggio precedente.
- Il consumatore non può prelevare alcun messaggio fino a che un produttore non l’abbia depositato.

La soluzione con pool di buffer gestito come coda circolare può penalizzare produttori o consumatori veloci
in presenza di produttori o consumatori lenti. 
Questo può accadere, ad esempio, quando i messaggi prodotti hanno dimensione variabile.
Per questo in questo caso, ci si avvale di un **vettore di stato** ausiliare per acquisire il lasciapassare a produrre o consumare 
una specifica locazione del pool di buffer in maniera concorrente.                    
L'accesso a tale vettore di stato è in mutua esclusione, e dopo aver acquisito un buffer del pool, produttori e consumatori procedono in concorrenza. 

Per la sincronizzazione dei processi produttore e consumatore si utilizzano **4 semafori**: 

- **SPAZIO_DISPONIBILE**: semaforo bloccato da un produttore prima di una produzione, 
e sbloccato da un consumatore in seguito ad un consumo. Il valore iniziale del semaforo deve essere pari ad ``1``;

- **MESSAGGIO_DISPONIBILE**: semaforo sbloccato da un produttore in seguito ad una produzione, 
e bloccato da un consumatore prima del consumo. Il valore iniziale del semaforo deve essere pari ad ``0``.

- **MUTEX_C**: semaforo per gestire la competizione per le operazioni di consumo;
Il valore iniziale del semaforo deve essere pari ad ``1``.

- **MUTEX_P**: semaforo per gestire la competizione per le operazioni di produzione.
Il valore iniziale del semaforo deve essere pari ad ``1``.

La produzione ed il consumo avvengono rispettivamente all'interno delle procedure:

```c
void Produttore(Vettore *, int);
void Consumatore(Vettore *, int);
```
dove, il primo argomento è un puntatore a interi della shared memory creata, 
mentre il secondo parametro indica il descrittore del semaforo da utilizzare per le operazioni 
di wait su semaforo (i.e., ``Wait_Sem``) e 
signal su semaforo (i.e., ``Signal_Sem``) necessarie per la cooperazione,competizione tra produttore e consumatore.

La shared memory creata è tutta la struttura struct.

```c
typedef struct{
    int buffer[DIM];
    char buffer2[DIM];
    int stato[DIM];
}Vettore;
```

dove:

- **int buffer[DIM]**, un array di elementi di tipo ``int``contenente i valori prodotti;

- **char buffer2[DIM]**, un array di elementi di tipo ``char``contenente i valori prodotti;

- **stato[DIM]**, un array di elementi di tipo intero. Il valore i-esimo, **stato[i]**, può assumere i seguenti tre valori:
	- **BUFFER_VUOTO**, la cella ``buffer[i], buffer2[i]`` non contiene alcun valore prodotto; 
	- **BUFFER_PIENO** , la cella ``buffer[i], buffer2[i]`` contiene un valore prodotto e non ancora consumato;
	- **BUFFER_INUSO**,  il valore della cella ``buffer[i] , buffer2[i]`` contiene un valore in uso da un processo attivo, consumatore o produttore.

Inizialmente ogni elemento del vettore ``stato[DIM]`` deve essere inizializzato a ``BUFFER_VUOTO``.

La Shared Memory viene Creata all'interno del MainVettore.c

```c
key_t Chiave_SHM = ftok("./VettoreDiStato",'V'); // chiave della shared memory
int ds_shm = shmget(Chiave_SHM, sizeof(Vettore), IPC_CREAT|0664);
if(ds_shm<0) { perror("SHM errore"); exit(1); }
Vettore * v;
v = (Vettore *) shmat(ds_shm, NULL, 0); 
shmctl(ds_shm, IPC_RMID, NULL); // rimozione chiave della shared memory		
```

I valori prodotti sono:
- Un intero generato da una funzione ``rand()`` 
```c
v->buffer[indice]= 1 + rand () % 999; // Valore casuale da 1 a 1.000
printf("Il valore Prodotto(int buffer[DIM])= [%d]\n",v->buffer[indice]); //ELEMENTO SINGOLO int
```
- Un carattere generato da una funzione ``rand()`` 
```c
v->buffer2[indice]='A' + (rand () % 26); // Valore casuale da 'A' a 'Z'
printf("Il valore Prodotto(char buffer2[DIM])= [%c]\n",v->buffer2[indice]); //ELEMENTO SINGOLO char
```

Esecuzione Programma Da Terminale:

```console
$ make
gcc -c VettorediStato.c
gcc -c semafori.c
gcc -c MainVettore.c
gcc -o VettoreDiStato VettorediStato.o semafori.o MainVettore.o
$ ./VettoreDiStato
	PRODUTTORE[1]
Il valore Prodotto(int buffer[DIM])= [391]
Il valore Prodotto(char buffer2[DIM])= [I]
	CONSUMATORE[1]
Il valore Consumato(int buffer[DIM])= [391]
Il valore Consumato(char buffer2[DIM])= [I]
	PRODUTTORE[2]
Il valore Prodotto(int buffer[DIM])= [118]
Il valore Prodotto(char buffer2[DIM])= [B]
	CONSUMATORE[2]
Il valore Consumato(int buffer[DIM])= [118]
Il valore Consumato(char buffer2[DIM])= [B]
$ make clean
rm -rf *.o
rm -rf VettoreDiStato
```




