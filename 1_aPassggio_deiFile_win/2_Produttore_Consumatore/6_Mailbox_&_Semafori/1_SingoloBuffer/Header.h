
#ifndef _HEADER_H
#define _HEADER_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "semafori.h"

//Funzioni per il semaforo,
#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1 

#define Num_Produttori 1   
#define Num_Consumatori 1 
 
#define Num_Produzioni 3   // Num di produzioni x ogni Produttore
#define Num_Consumazioni 3 // Num di consumazioni x ogni Consumatore

#define Num_Processi Num_Consumatori+Num_Produttori 
#define Tot_Produttori Num_Produttori*Num_Produzioni
#define Tot_Consumatori Num_Consumatori*Num_Consumazioni

#define MESSAGGIO 1

#define DIM 5 

typedef int Array [DIM];
typedef char Stringa [DIM];

typedef struct{
	
	long tipo;
	int intero;
	char carattere;
	Stringa stringa;
	Array array;
		
}message;

typedef struct{
	
	message msg;
		
} Struct;

void Set_Dati(Struct*,int);
void Remove_Dati(int,int,int);
void Produzione(Struct*,int,int);
void Consumazione(Struct*,int,int);
void Prova(int);
#endif
