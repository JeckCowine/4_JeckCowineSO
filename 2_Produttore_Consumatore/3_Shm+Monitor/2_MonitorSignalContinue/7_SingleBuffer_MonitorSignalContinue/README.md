## Produttore-Consumatore singolo buffer con utilizzo di un Monitor Signal Continue

Nel problema produttore-consumatore, abbiamo due categorie di processi:

- **Produttori**, che scrivono un messaggio su di una risorsa condivisa
- **Consumatori**, che prelevano il messaggio dalla risorsa condivisa

Ciascuno dei due processi deve attendere, per completare la sua azione, l’arrivo del segnale dell’altro processo.

### Esercizio

I vincoli che caratterizzano il problema produttore-consumatore a singolo buffer sono i seguenti:

- Il produttore non può produrre un messaggio prima che qualche consumatore abbia letto il messaggio precedente.
- Il consumatore non può prelevare alcun messaggio fino a che un produttore non l’abbia depositato.

Per la sincronizzazione dei processi produttore e consumatore si utilizza un Monitor Hoare 
che mediande l'utilizzo di **2 var_condition** e **2_buffer** gestisce la competizione: 

2 Buffer:

- **int buffer_libero**: creato all'interno della struct e inizializzata a ``1``;
quindi è 1 se libero, 0 se pieno

- **int buffer_occupato**: creato all'interno della struct e inizializzata a ``0``;
quindi è 0 se libero, 1 se pieno

2 Var_Condition:

- **Varcond_Produttori**: varcond chiamata dal monitor se non c'è spazio per poter produrre e inizializzata in SinBufSignalContinue.h,
quindi se s->buffer_occupato=1 rimane nell'while
e sbloccato poi se ha spazio per poter produrre. Il valore iniziale della Var_Condition è inizializzato a ``0``
poi prima del rilascio del monitor si fa il signal all'altra variabile condition
```c
/*SinBufSignalContinue.h*/
#define Varcond_Produttori 0
#define Varcond_Consumatori 1
/*SinBufSignalContinue.c*/
while(s->buffer_occupato==1){
wait_condition(&(s->m),Varcond_Produttori);
}
signal_condition(&(s->m),Varcond_Consumatori);
```
- **Varcond_Consumatori**: varcond chiamata dal monitor se non c'è nessun messaggio da poter consumare e inizializzata in SinBufSignalContinue.h,
quindi se s->buffer_libero=1 rimane nell'while
e sbloccato poi se ha spazio per poter produrre. Il valore iniziale della Var_Condition è inizializzato a ``0``
poi prima del rilascio del monitor si fa il signal all'altra variabile condition
```c
/*SinBufSignalContinue.h*/
#define Varcond_Produttori 0
#define Varcond_Consumatori 1
/*SinBufSignalContinue.c*/
while(s->buffer_libero ==1){
wait_condition(&(s->m),Varcond_Consumatori);	
}
signal_condition(&(s->m),Varcond_Produttori);
```

La produzione ed il consumo avvengono rispettivamente all'interno delle procedure:

```c
/*SinBufSignalContinue.h*/
void Produttore(SingleBuff*);
void Consumatore(SingleBuff*);
```

dove, il primo argomento è un puntatore a interi della shared memory creata, 

La shared memory creata è tutta la struttura struct.

```c
/*SinBufSignalContinue.h*/
typedef struct{
int intero; 
int buffer_libero;
int buffer_occupato;
Monitor m;		
}SingleBuff;	
```
dove:

- **int intero**, un elemento di tipo ``int``contenente il messaggio da inviare;
- **int buffer_libero**, elemento per la competizione per Produttore_Consumatore
- **int buffer_occupato**, elemento per la competizione per Produttore_Consumatore
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
/*MainSignalContinue.c*/
key_t Chiave_SHM = ftok ("./SingleBuff",'S');	// chiave della shared memory
	//Inizializzazione Shared Memory Struct
int ds_shm = shmget(Chiave_SHM, sizeof(SingleBuff), IPC_CREAT | 0664);
if(ds_shm<0) { perror("SHM errore"); exit(1); }
SingleBuff* s;			
s = (SingleBuff*) shmat(ds_shm, NULL, 0);
	//FINE
shmctl(ds_shm,0,IPC_RMID);
```
Le funzioni principali di funzionamento del Monitor Hoare sono:

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
wait_condition(&(s->m), Varcond_Produttori); //nel While no nell'if
signal_codition(&(s->m),Varcond_Consuamatori) //prima del rilascio del monitor si aggiunge la signal
o
wait_condition(&(s->m),Varcond_Consumatori); //nel While no nell'if
signal_codition(&(s->m),Varcond_Produttori) //prima del rilascio del monitor si aggiunge la signal
```

- **Utilizzo nell'esercizio**:
```c
/*SinBufSignalContinue.h*/
#define Varcond_Produttori 0
#define Varcond_Consumatori 1
#define DIM_INT 3 
#define DIM_STRING 10 
typedef struct{
int intero; 
int array[DIM_INT];
char carattere;
char stringa[DIM_STRING];
int buffer_libero;
int buffer_occupato;
Monitor m;		
}SingleBuff;	

/*SinBufSignalContinue.c*/
void Set_Dati(SingleBuff* s){ 
init_monitor(&(s->m), 2); //2= Varcond_Prod, Varcond_Cons  //INIZIALIZZAZIONE MONITOR
}
void Remove_Dati(SingleBuff* s){ 
remove_monitor( & (s->m) ); //RIMOZIONE MONITOR
}
void Produttore(SingleBuff* s){ 
enter_monitor( & (s->m) ); //ACCESSO AL MONITOR	
while(s->buffer_occupato==1){
wait_condition( &(s->m), Varcond_Produttori); //ASPETTO 
}
s->buffer_occupato = 1;
s->buffer_libero = 0;
signal_condition( &(s->m), Varcond_Consumatori); //DIFFERENZA CON MONITOR HOARE
leave_monitor( & (s->m) ); //RILASCIO MONITOR
}
void Consumatore(SingleBuff* s){
enter_monitor( & (s->m) ); //ACCESSO AL MONITOR
while(s->buffer_libero ==1){
wait_condition(&(s->m),Varcond_Consumatori); //ASPETTO
}
s->buffer_libero=1;
s->buffer_occupato=0;
signal_condition( &(s->m), Varcond_Produttori); //DIFFERENZA CON MONITOR HOARE
leave_monitor( & (s->m) ); //RILASCIO MONITOR
}
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
gcc MainSignalContinue.c SinBufSignalContinue.c MonitorSignalContinue.c -o SingleBuffSignalContinue MonitorSignalContinue.h SinBufSignalContinue.h
$ ./SingleBuffSignalContinue 	
Esercizio Produttore Consumatore Single Buffer con  Monitor Signal Continue

	PRODUTTORE[1]
Valore Prodotto(int intero) = [71]
Valore Prodotto(char carattere)= [K]
Valore Prodotto(int array[DIM])= [878][970][916]
Valore Prodotto(char stringa[DIM])= [SFIZZBXGMJ0]
	CONSUMATORE[1]
Valore Consumato(int intero) = [71]
Valore Consumato(char carattere)= [K]
Valore Consumato(int array[DIM])= [878][970][916]
Valore Consumato(char stringa[DIM])= [SFIZZBXGMJ0]
$ make clean
rm -rf *.o
rm -rf SingleBuffSignalContinue
```




