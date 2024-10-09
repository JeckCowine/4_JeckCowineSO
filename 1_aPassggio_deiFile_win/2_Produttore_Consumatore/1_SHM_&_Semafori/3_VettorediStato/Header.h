
#ifndef _HEADER_H
#define _HEADER_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "semafori.h"

//Funzioni per il semaforo,
#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
#define MUTEX_P 2
#define MUTEX_C 3

#define Num_Produttori 3   
#define Num_Consumatori 3 

#define Num_Produzioni 2 // Num di produzioni x ogni Produttore
#define Num_Consumazioni 2 // Num di consumazioni x ogni Consumatore

#define Num_Processi Num_Consumatori+Num_Produttori 
#define Tot_Produttori Num_Produttori*Num_Produzioni
#define Tot_Consumatori Num_Consumatori*Num_Consumazioni

#define DIM 3 

#define BUFFER_VUOTO 0
#define BUFFER_INUSO 1
#define BUFFER_PIENO 2

typedef int Array [DIM];
typedef char Stringa [DIM];

typedef struct{
	
	int array[DIM];
	Stringa stringa;
	Array stato;
				
}Struct;

void Set_Dati(Struct*,int);
void Remove_Dati(Struct*,int,int);
void Produzione(Struct*, int);
void Consumazione(Struct*, int);

#endif
