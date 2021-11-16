/*............VETTOREDISTATO_H..............*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "semafori.h"

/* SEMAFORI */
#define SPAZIO_DISPONIBILE 0//Funzioni per il semaforo, Se 0 è pieno, Se 1 è libero
#define MESSAGGIO_DISPONIBILE 1//Funzioni per il semaforo, Se 0 non c'è Messaggio, Se 1 si
#define MUTEX_P 2//Per gestire la competizione per le operazioni di produzione
#define MUTEX_C 3//Per gestire la competizione per le operazioni di consumo

#define Num_Consumatori 2 // Numero Consumatori
#define Num_Produttori 2     // Numero Produttori 

#define DIM 3 //Dimensione buffer

#define BUFFER_VUOTO 0
#define BUFFER_INUSO 1
#define BUFFER_PIENO 2

typedef struct{
    int buffer[DIM];
    char buffer2[DIM];
    int stato[DIM];
}Vettore;

void Set_Dati(Vettore*,int);
void Remove_Dati(Vettore*,int,int);
void Produttore(Vettore *, int);
void Consumatore(Vettore *, int);

/*.............END.............*/
