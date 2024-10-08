/*.............SINGLEBUFFER_H..............*/

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
#define SPAZIO_DISPONIBILE 0 //Funzioni per il semaforo, Se 0 è pieno, Se 1 è libero
#define MESSAGGIO_DISPONIBILE 1 //Funzioni per il semaforo, Se 0 non c'è Messaggio, Se 1 si

#define Num_Consumatori 2 // Numero Consumatori
#define Num_Produttori 2     // Numero Produttori 

#define DIM_INT 3 // Dimensione Array
#define DIM_STRING 10 // Dimensione Stringa

typedef struct{
	//VALORE DA PASSARE	
		int intero; //PER PASSARE VALORE INT
		    /*---oppure---*/
		int array[DIM_INT];//PER PASSARE VALORE INT
		    /*---oppure---*/
		char carattere;//PER PASSARE VALORE CHAR
		    /*---oppure---*/
		char stringa[DIM_STRING];//PER PASSARE VALORE CHAR
		
}SingleBuff;

void Set_Dati(SingleBuff*,int);
void Remove_Dati(SingleBuff*,int,int);
void Produttore(SingleBuff*, int);
void Consumatore(SingleBuff*, int);

/*.............END.............*/
