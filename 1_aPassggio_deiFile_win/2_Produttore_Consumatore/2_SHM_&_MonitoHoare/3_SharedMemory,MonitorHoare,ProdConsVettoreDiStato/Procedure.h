/*.............VETTORE_H..............*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "MonitorHoare.h"

#define Num_Consumatori 2 // Numero Consumatori
#define Num_Produttori 2     // Numero Produttori 

#define Varcond_Produttori 0
#define Varcond_Consumatori 1

#define DIM 3 //Dimensione buffer
#define BUFFER_VUOTO 0
#define BUFFER_INUSO 1
#define BUFFER_PIENO 2

typedef struct {
	//VALORE DA PASSARE
    int buffer[DIM];//PER PASSARE VALORE INT
    char buffer2[DIM];//PER PASSARE VALORE CHAR
    
    int stato[DIM];
      
	int buffer_libero;
	int buffer_occupato;
	
	Monitor m;
}Vettore;

void Set_Dati(Vettore*);
void Remove_Dati(Vettore*);
void Produttore(Vettore *);
void Consumatore(Vettore *);

/*.............END.............*/
