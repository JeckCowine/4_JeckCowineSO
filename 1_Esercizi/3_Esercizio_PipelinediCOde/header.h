#include "monitor_signal_continue.h"

#define MSG_TYPE 1
#define DIM_STRING 11
#define DIM_INT 2

#define NUM_FILTER 1
#define NUM_CHECKSUM 1
#define NUM_VISUAL 1

#define NUM_GENERATORS 4
#define DIM_QUEUE 4
#define VARCOND_GEN_PRODUTTORI 0
#define VARCOND_GEN_CONSUMATORI 1

#define NUM_MESSAGES 8

#define NUM_PROCESS NUM_FILTER+NUM_CHECKSUM+NUM_VISUAL

typedef int Array[DIM_INT];
typedef char Stringa[DIM_STRING];

typedef struct {
        
    long tipo;
    int variabile;
    Array array;
    Stringa stringa;

} Message;

typedef struct {
    
    Message mess[DIM_QUEUE];
    
    int testa;
    int coda;
	
	int num_elementi;
	
	Monitor m;
  
}ProdCons;

void generatore_produttore(ProdCons*);
void generatore_consumatore(ProdCons*,  int);

void filtro(int, int);
void checksum(int , int);
void visualizzatore(int);
