/*.............SINBUFMONHOAR_H..............*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "MonitorHoare.h"

#define Num_Consumatori 1 // Numero Consumatori
#define Num_Produttori 1     // Numero Produttori 

#define Varcond_Produttori 0
#define Varcond_Consumatori 1

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
	
	int buffer_libero;
	int buffer_occupato;
	
	Monitor m;
		
}SingleBuff;

void Set_Dati(SingleBuff*);
void Remove_Dati(SingleBuff*);
void Produttore(SingleBuff*);
void Consumatore(SingleBuff*);

/*.............END.............*/
