## Produttore-Consumatore singolo buffer

Nel problema produttore-consumatore, abbiamo due categorie di processi:

- **Produttori**, che scrivono un messaggio su di una risorsa condivisa
- **Consumatori**, che prelevano il messaggio dalla risorsa condivisa

Ciascuno dei due processi deve attendere, per completare la sua azione, l’arrivo del segnale dell’altro processo.

### Esercizio

I vincoli che caratterizzano il problema produttore-consumatore a singolo buffer sono i seguenti:

- Il produttore non può produrre un messaggio prima che qualche consumatore abbia letto il messaggio precedente.
- Il consumatore non può prelevare alcun messaggio fino a che un produttore non l’abbia depositato.

Per la sincronizzazione dei processi produttore e consumatore si utilizzano **2 semafori**: 

- **SPAZIO_DISPONIBILE**: semaforo bloccato da un produttore prima di una produzione, 
e sbloccato da un consumatore in seguito ad un consumo. Il valore iniziale del semaforo deve essere pari ad ``1``;

- **MESSAGGIO_DISPONIBILE**: semaforo sbloccato da un produttore in seguito ad una produzione, 
e bloccato da un consumatore prima del consumo. Il valore iniziale del semaforo deve essere pari ad ``0``.

La produzione ed il consumo avvengono rispettivamente all'interno delle procedure:

```c
void Produttore(SingleBuff*, int);
void Consumatore(SingleBuff*, int);
```

dove, il primo argomento è un puntatore a interi della shared memory creata, 
mentre il secondo parametro indica il descrittore del semaforo da utilizzare per le operazioni 
di wait su semaforo (i.e., `Wait_Sem`) e 
signal su semaforo (i.e., `Signal_Sem`) necessarie per la cooperazione tra produttore e consumatore.

La shared memory creata è tutta la struttura struct.

```c
typedef struct{	
int intero; //PER PASSARE VALORE INT
int array[DIM_INT];//PER PASSARE VALORE INT
char carattere;//PER PASSARE VALORE CHAR
char stringa[DIM_STRING];//PER PASSARE VALORE CHAR
}SingleBuff;		
```

Viene Creata all'interno del MainSingleBuff.c

```c
key_t Chiave_SHM = ftok ("./SingleBuff",'S');	// chiave della shared memory
int ds_shm = shmget(Chiave_SHM, sizeof(SingleBuff), IPC_CREAT | 0664);
if(ds_shm<0) { perror("SHM errore"); exit(1); }
SingleBuff* s;			
s = (SingleBuff*) shmat(ds_shm, NULL, 0);
shmctl(ds_shm, IPC_RMID, NULL); // rimozione chiave della shared memory		
```

I valori prodotti sono:
- Un intero generato tramite la funzione ``rand()`` 
```c
s->intero = 1 + rand () % 999; // Valore casuale da 1 a 1.000
printf("Valore Prodotto(int intero) = [%d]\n", s->intero);
```
- Un carattere generato da una funzione ``rand()`` 
```c
s->carattere = 'A' + (rand () % 26) ; // Valore casuale da 'A' a 'Z'
printf("Valore Prodotto(char carattere)= [%c]\n", s->carattere);
```
- Un array di interi generato da una funzione ``rand()`` 
```c
for(int i=0;i<DIM_INT;i++){
   s->array[i] = 1 + rand() %999; // Valore casuale da 1 a 1.000 
}
printf("Valore Prodotto(int array[DIM])= ");
for(int i=0;i<DIM_INT;i++) printf("[%d]", s->array[i]); 
printf("\n");
```
- Una stringa di caratteri generata da una funzione ``rand()`` 
```c
for(int i=0;i<DIM_STRING;i++){
   s->stringa[i] = 'A' + (rand () % 26) ; // Valore casuale da 'A' a 'Z'
}
printf("Valore Prodotto(char stringa[DIM])= [%s]\n", s->stringa);
```

Esecuzione Programma Da Terminale:
```console
$ make
gcc -c MainSingleBuff.c
gcc -c SingleBuff.c
gcc -c semafori.c
gcc -o SingleBuff MainSingleBuff.o SingleBuff.o semafori.o
$ ./SingleBuff
	PRODUTTORE[1]
Valore Prodotto(int intero) = [756]
Valore Prodotto(char carattere)= [D]
Valore Prodotto(int array[DIM])= [732][495][790]
Valore Prodotto(char stringa[DIM])= [JELMYVNFJC]
	CONSUMATORE[1]
Valore Consumato(int intero) = [756]
Valore Consumato(char carattere)= [D]
Valore Consumato(int array[DIM])= [732][495][790]
Valore Consumato(char stringa[DIM])= [JELMYVNFJC]
	PRODUTTORE[2]
Valore Prodotto(int intero) = [301]
Valore Prodotto(char carattere)= [Y]
Valore Prodotto(int array[DIM])= [771][383][84]
Valore Prodotto(char stringa[DIM])= [CVJYDXTYPP]
	CONSUMATORE[2]
Valore Consumato(int intero) = [301]
Valore Consumato(char carattere)= [Y]
Valore Consumato(int array[DIM])= [771][383][84]
Valore Consumato(char stringa[DIM])= [CVJYDXTYPP]
$ make clean
rm -rf *.o
rm -rf SingleBuff
```




