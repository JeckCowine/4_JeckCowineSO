## Produttore-Consumatore con Vettore di Stato con utilizzo di un Monitor Signal Continue

Nel problema produttore-consumatore, abbiamo due categorie di processi:

- **Produttori**, che scrivono un messaggio su di una risorsa condivisa
- **Consumatori**, che prelevano il messaggio dalla risorsa condivisa

Ciascuno dei due processi deve attendere, per completare la sua azione, l’arrivo del segnale dell’altro processo.

### Esercizio

I vincoli che caratterizzano il problema produttore-consumatore a singolo buffer sono i seguenti:

- Il produttore non può produrre un messaggio prima che qualche consumatore abbia letto il messaggio precedente.
- Il consumatore non può prelevare alcun messaggio fino a che un produttore non l’abbia depositato.

Per la sincronizzazione dei processi produttore e consumatore si utilizza un Monitor Signal e Continue 
che mediande l'utilizzo di **2 var_condition** e **2_buffer** gestisce la competizione: 

2 Buffer:

- **int Spazio_Disponibile**: creato all'interno della struct e inizializzata a ``DIM`` che è una define creata in Procedure.h;
quindi è 0 è pieno (Non c'è spazio), 1 se è libero (C'è spazio)

- **int Messaggio_Disponibile**: creato all'interno della struct e inizializzata a ``0``;
quindi se è 0 non c'è un Messaggio nella risorsa, Se 1 il messaggio si può consumare

2 Var_Condition:

- **MUTEX_P**: varcond chiamata dal monitor se non c'è spazio per poter produrre e inizializzata in Procedure.h,
quindi se v->Spazio_Disponibile=0 (ovvere non c'è spazio per poter produrre) rimane nell'while
e sbloccato poi se ha spazio per poter produrre. Il valore iniziale della Var_Condition è inizializzato a ``DIM``(Quindi 3 poi mano a mano si scala con Messaggio_Disponibile--)
fatto questo si rilascia il monitor per un'altro produttore per poi chiamarsi di nuovo l'enter_monitor
e prima del rilascio del monitor si fa il signal sulla variabile condition dei consumatori
```c
/*Procedure.h*/
#define MUTEX_P 1
#define MUTEX_C 1
/*Procedure.c*/
while(v->Spazio_Disponibile==0){
wait_condition( &(v->m), MUTEX_P);
}	
v->Spazio_Disponibile--;
signal_condition( &(v->m), MUTEX_C);
```
- **MUTEX_C**: varcond chiamata dal monitor se non c'è nessun messaggio da consumare e inizializzata in Procedure.h,
quindi se v->Messaggio_Disponibile=0 (ovvere non c'è nessun messaggio) rimane nell'while
e sbloccato poi se c'è un messaggio in arrivo. Il valore iniziale della Var_Condition è inizializzato a ``0``(Poichè all'inizio sono presenti 0 msg)
fatto questo si rilascia il monitor per un'altro consumatore per poi chiamarsi di nuovo l'enter_monitor
e prima del rilascio del monitor si fa il signal sulla variabile condition dei produttori
```c
/*Procedure.h*/
#define MUTEX_P 1
#define MUTEX_C 1
/*Procedure.c*/
while(v->Messaggio_Disponibile ==0){
wait_condition(&(v->m),MUTEX_C);	
}
v->Spazio_Disponibile++;
signal_condition( &(v->m),MUTEX_P);
```

La produzione ed il consumo avvengono rispettivamente all'interno delle procedure:

```c
/*Procedure.h*/
void Produttore(Vettore*);
void Consumatore(Vettore*);
```

dove, il primo argomento è un puntatore a interi della shared memory creata, 

La shared memory creata è tutta la struttura struct.

```c
/*Procedure.h*/
typedef struct{
int buffer[DIM];
char buffer2[DIM];
int stato[DIM];
int Spazio_Disponibile; //Se 0 è pieno, Se 1 è libero
int Messaggio_Disponibile; //Se 0 non c'è Messaggio, Se 1 si
Monitor m;
}Vettore;	
```
dove:
- **int buffer[DIM]**, un array di elementi di tipo ``int``contenente i valori prodotti;
- **char buffer2[DIM]**, un array di elementi di tipo ``char``contenente i valori prodotti;
- **stato[DIM]**, un array di elementi di tipo intero. Il valore i-esimo, **stato[i]**, può assumere i seguenti tre valori:
	- **BUFFER_VUOTO**, la cella ``buffer[i], buffer2[i]`` non contiene alcun valore prodotto; 
	- **BUFFER_PIENO** , la cella ``buffer[i], buffer2[i]`` contiene un valore prodotto e non ancora consumato;
	- **BUFFER_INUSO**,  il valore della cella ``buffer[i] , buffer2[i]`` contiene un valore in uso da un processo attivo, consumatore o produttore.
	- **INIZIALIZZAZIONE** ogni elemento del vettore ``stato[DIM]`` deve essere inizializzato a ``BUFFER_VUOTO``.
- **int Spazio_Disponibile**, elemento per la competizione per Produttore_Consumatore
- **int Messaggio_Disponibile**, elemento per la competizione per Produttore_Consumatore
- **Monitor m**, richiamo della struct monitor presente nella libreria e assegnato con nome "m" ;
```c
/*MonitorSignalContinue.h*/
typedef struct {
//id del semaforo per realizzare il mutex del monitor
  int mutex;
//numero di variabili condition
  int num_var_cond;
//id del gruppo sem associati alle var.cond
  int id_conds;
//id della memoria condivisa per i contatori delle variabili condition
  int id_shared;
//array delle variabili condition_count
  int *cond_counts;
} Monitor;
```

La Shared Memory viene Creata all'interno del Main

```c
/*Main.c*/
key_t Chiave_SHM = ftok ("./VettoreDiStato",'V');	// chiave della shared memory
	//Inizializzazione Shared Memory Struct
int ds_shm = shmget(Chiave_SHM, sizeof(Vettore), IPC_CREAT | 0664);
if(ds_shm<0) { perror("SHM errore"); exit(1); }
Vettore* v;			
v = (Vettore*) shmat(ds_shm, NULL, 0);
	//FINE
shmctl(ds_shm,0,IPC_RMID);
```
Le funzioni principali di funzionamento del Monitor Signal e Continue sono:

- **Inizializzazione**:
```c
init_monitor(&(s->m), 2); 
dove 2 = Varcond_Prod, Varcond_Cons 
```

- **Rimozione**:
```c
remove_monitor( & (s->m) ); 
```

- **Accesso**:
```c
enter_monitor( & (s->m) );
```

- **Rilascio**:
```c
leave_monitor( & (s->m) );
```

- **Aspettare i valori**:
```c
	//DIFFERENZA CON MONITOR HOARE
PRODUTTORE
enter_monitor;
wait_condition(&(v->m), MUTEX_P); //nel While no nell'if
v->Spazio_Disponibile--;
leave_monitor;
enter_monitor;
v->Messaggio_Disponibile++;
signal_codition(&(v->m),MUTEX_C) //prima del rilascio del monitor si aggiunge la signal
o
CONSUMATORE
enter_monitor;
wait_condition(&(v->m),MUTEX_C); //nel While no nell'if
v->Messaggio_Disponibile--;
leave_monitor;
enter_monitor;
v->Spazio_Disponibile++;
signal_codition(&(v->m),MUTEX_P) //prima del rilascio del monitor si aggiunge la signal
```

- **Utilizzo nell'esercizio**:
```c
/*Procedure.h*/
#define MUTEX_P 1
#define MUTEX_C 1
#define DIM 3 //Dimensione buffer
#define BUFFER_VUOTO 0
#define BUFFER_INUSO 1
#define BUFFER_PIENO 2
typedef struct{
int buffer[DIM];
char buffer2[DIM];
int stato[DIM];
int Spazio_Disponibile; //Se 0 è pieno, Se 1 è libero
int Messaggio_Disponibile; //Se 0 non c'è Messaggio, Se 1 si
Monitor m;
}Vettore;	

/*Procedure.c*/
	//INIZIALIZZAZIONE DATI
void Set_Dati(Vettore* v){ 
init_monitor(&(v->m), 2); //2= Varcond_Prod, Varcond_Cons  //INIZIALIZZAZIONE MONITOR
}
	//RIMOZIONE DATI
void Remove_Dati(Vettore* v){ 
remove_monitor( & (v->m) ); //RIMOZIONE MONITOR
}
	//PRODUTTORE
void Produttore(Vettore* v){ 
enter_monitor( & (v->m) );
while(v->Spazio_Disponibile==0){ wait_condition( &(v->m), MUTEX_P); }
int indice = 0;
while(indice <= DIM && v->stato[indice] != BUFFER_VUOTO){ indice++; }
v->stato[indice] = BUFFER_INUSO;
v->Spazio_Disponibile--;
leave_monitor( & (v->m) );
enter_monitor( & (v->m) );
v->stato[indice] = BUFFER_PIENO;
v->Messaggio_Disponibile++;
signal_condition( &(v->m), MUTEX_C);
leave_monitor( & (v->m) );	
}
	//CONSUMATORE
void Consumatore(Vettore* v){
enter_monitor( & (v->m) );	
while(v->Messaggio_Disponibile ==0){ wait_condition(&(v->m),MUTEX_C); }
int indice = 0;
while(indice <= DIM && v->stato[indice] != BUFFER_PIENO){ indice++; }
v->stato[indice] = BUFFER_INUSO;
v->Messaggio_Disponibile--;
leave_monitor( & (v->m) );
enter_monitor( & (v->m) );
v->stato[indice] = BUFFER_VUOTO;
v->Spazio_Disponibile++;
signal_condition( &(v->m),MUTEX_P);
leave_monitor( & (v->m) );	
}
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
gcc Main.c Procedure.c Monitor.c -o Vettore Monitor.h Procedure.h
$ ./Vettore  	
Esercizio Produttore Consumatore Vettore di stato con  Monitor Signal Continue

	PRODUTTORE[1]
Il valore Prodotto(int buffer[DIM])= [643]
Il valore Prodotto(char buffer2[DIM])= [N]
	CONSUMATORE[1]
Il valore Consumato(int buffer[DIM])= [643]
Il valore Consumato(char buffer2[DIM])= [N]
	PRODUTTORE[2]
Il valore Prodotto(int buffer[DIM])= [883]
Il valore Prodotto(char buffer2[DIM])= [R]
	CONSUMATORE[2]
Il valore Consumato(int buffer[DIM])= [883]
Il valore Consumato(char buffer2[DIM])= [R]
$ make clean
rm -rf *.o
rm -rf Vettore
```
