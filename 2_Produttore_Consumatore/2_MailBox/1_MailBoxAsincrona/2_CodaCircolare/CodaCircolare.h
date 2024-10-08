/*.............CODACIRCOLARE_H..............*/

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>

#define MESSAGGIO 1

#define Num_Consumatori 2 // Numero Consumatori
#define Num_Produttori 2     // Numero Produttori 

#define DIM 3 // Dimensione 

typedef struct {
	//VALORE DA PASSARE
    int buffer[DIM];//PER PASSARE VALORE INT
    /*---oppure---*/
    char buffer2[DIM];//PER PASSARE VALORE CHAR
    
    int testa;
    int coda;
}Coda;

void Set_Dati(Coda);
void Remove_Dati(Coda,int);
void Produttore(Coda,int,int);
void Consumatore(Coda,int,int);

/*.............END.............*/
