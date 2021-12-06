## Produttore-Consumatore con pool di buffer gestito come coda circolare


Nel problema produttore-consumatore, abbiamo due categorie di processi:

- **Produttori**, che scrivono un messaggio su di una risorsa condivisa
- **Consumatori**, che prelevano il messaggio dalla risorsa condivisa

Ciascuno dei due processi deve attendere, per completare la sua azione, l’arrivo del segnale dell’altro processo.

### Esercizio

I vincoli che caratterizzano il problema produttore-consumatore con pool di buffer sono i seguenti:

- Il produttore non può produrre un messaggio prima che qualche consumatore abbia letto il messaggio precedente.
- Il consumatore non può prelevare alcun messaggio fino a che un produttore non l’abbia depositato.

In particolare, si gestisce il pool di buffer come coda circolare, 
in cui si impone la produzione di un valore in testa alla coda e la consumazione in coda.

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
void Produttore(Coda *, int);
void Consumatore(Coda *, int);
```
dove, il primo argomento è un puntatore a interi della shared memory creata, 
mentre il secondo parametro indica il descrittore del semaforo da utilizzare per le operazioni 
di wait su semaforo (i.e., ``Wait_Sem``) e 
signal su semaforo (i.e., ``Signal_Sem``) necessarie per la cooperazione,competizione tra produttore e consumatore.

La shared memory creata è tutta la struttura struct.

```c
typedef struct {
int buffer[DIM];//PER PASSARE VALORE INT
char buffer2[DIM];//PER PASSARE VALORE CHAR

int testa;
int coda;
}Coda;	
```
Viene Creata all'interno del MainCoda.c

```c
key_t Chiave_SHM = ftok("./CodaCircolare",'C'); // chiave della shared memory
int ds_shm = shmget(Chiave_SHM, sizeof(Coda), IPC_CREAT|0664);
if(ds_shm<0) { perror("SHM errore"); exit(1); }
Coda * p;
p = (Coda *) shmat(ds_shm, NULL, 0); 
shmctl(ds_shm, IPC_RMID, NULL); // rimozione chiave della shared memory		
```

I valori prodotti sono:
- Un intero generato da una funzione ``rand()`` 
```c
c->buffer[c->testa]= 1 + rand () % 999; // Valore casuale da 1 a 1.000
printf("Il valore Prodotto(int buffer[DIM])= [%d]\n",c->buffer[c->testa]); //ELEMENTO SINGOLO int
```
- Un carattere generato da una funzione ``rand()`` 
```c
c->buffer2[c->testa]='A' + (rand () % 26); // Valore casuale da 'A' a 'Z'
printf("Il valore Prodotto(char buffer2[DIM])= [%c]\n",c->buffer2[c->testa]); //ELEMENTO SINGOLO char
```

Esecuzione Programma Da Terminale:
```console
$ make
gcc MainCoda.c CodaCircolare.c semafori.c -o CodaCircolare
$ ./CodaCircolare
Esercizio Produttore Consumatore Coda Circolare con Semafori

	PRODUTTORE[1]
Il valore Prodotto(int buffer[DIM])= [456]
Il valore Prodotto(char buffer2[DIM])= [M]
	CONSUMATORE[1]
Il valore Consumato(int buffer[DIM])= [456]
Il valore Consumato(char buffer2[DIM])= [M]
	PRODUTTORE[2]
Il valore Prodotto(int buffer[DIM])= [987]
Il valore Prodotto(char buffer2[DIM])= [L]
	CONSUMATORE[2]
Il valore Consumato(int buffer[DIM])= [987]
Il valore Consumato(char buffer2[DIM])= [L]
$ make clean
rm -rf *.o
rm -rf CodaCircolare
```
