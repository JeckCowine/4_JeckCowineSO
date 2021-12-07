/*.............VETTORESIGNALCONTINUE_H..............*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "Monitor.h"

#define Num_Consumatori 2 // Numero Consumatori
#define Num_Produttori 2     // Numero Produttori 

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

void Set_Dati(Vettore*);
void Remove_Dati(Vettore*);
void Produttore(Vettore*);
void Consumatore(Vettore*);

/*.............END.............*/
