/*.............CODACIRCOLARE_H..............*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "MonitorSignalContinue.h"

#define Num_Consumatori 2 // Numero Consumatori
#define Num_Produttori 2     // Numero Produttori 

#define Varcond_Produttori 0
#define Varcond_Consumatori 1

#define DIM 3 //Dimensione buffer

typedef struct {
	//VALORE DA PASSARE
    int buffer[DIM];//PER PASSARE VALORE INT
    /*---oppure---*/
    char buffer2[DIM];//PER PASSARE VALORE CHAR
    
    int testa;
    int coda;
    
	int buffer_libero;
	int buffer_occupato;
	
	Monitor m;
}Coda;

void Set_Dati(Coda*);
void Remove_Dati(Coda*);
void Produttore(Coda *);
void Consumatore(Coda *);

/*.............END.............*/
