/*.............VETTOREDISTATO_C.............*/

#include "VettorediStato.h"

void Set_Dati(Vettore* v, int ds_sem) {

	//Semafori di COOPERAZIONE tra i Produttori e Consumatori
    semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM);
    semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    //Semafori di COMPETIZIONE tra i Produttori e Consumatori
    semctl(ds_sem, MUTEX_C, SETVAL, 1);
    semctl(ds_sem, MUTEX_P, SETVAL, 1);
	//Inizializzazione dei valori da passare tra i Produttori e Consumatori
	v->buffer[DIM]=0;	
	v->buffer2[DIM]='0';	
	v->stato[DIM]=0;	
	
}

void Remove_Dati(Vettore* v, int ds_sem, int ds_shm){
	
	v->buffer[DIM]=0;	
	v->buffer2[DIM]='0';	
	v->stato[DIM]=0;
	shmctl(ds_shm, IPC_RMID, NULL); // rimozione chiave della SHM
    semctl(ds_sem, 0, IPC_RMID); //rimozione chiave del SEM
	
}   

void Produttore(Vettore* v, int ds_sem) {
    
    Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);  
    Wait_Sem(ds_sem, MUTEX_P);
    
    int indice = 0;
    sleep(2);
    while(indice <= DIM && v->stato[indice] != BUFFER_VUOTO) {
        indice++;
    }
    v->stato[indice] = BUFFER_INUSO;
    //qui devo rilasciare il mutex per i produttori...ERRORE se non lo faccio!!!!
    Signal_Sem(ds_sem, MUTEX_P);
    printf("\n");
    srand(time(NULL));// Serve a scegliere sempre un valore diverso a ogni compilazione
				/* PER VALORE (int buffer [DIM])*/
	v->buffer[indice]= 1 + rand () % 999; // Valore casuale da 1 a 1.000
	printf("Il valore Prodotto(int buffer[DIM])= [%d]\n",v->buffer[indice]); //ELEMENTO SINGOLO int
	/*.....................*/		
	
			/* PER VALORE (char buffer2 [DIM])*/
	v->buffer2[indice]='A' + (rand () % 26); // Valore casuale da 'A' a 'Z'
	printf("Il valore Prodotto(char buffer2[DIM])= [%c]\n",v->buffer2[indice]); //ELEMENTO SINGOLO char
	/*.....................*/	
		
	v->stato[indice] = BUFFER_PIENO;

    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    
}

void Consumatore(Vettore* v, int ds_sem) {
    
    Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    Wait_Sem(ds_sem, MUTEX_C);
    
    int indice=0;
    sleep(2);
    while(indice <= DIM && v->stato[indice] != BUFFER_PIENO) {
        indice++;
    }
    v->stato[indice] = BUFFER_INUSO;
    //qui devo rilasciare il mutex per i produttori...ERRORE se non lo faccio!!!!
    Signal_Sem(ds_sem, MUTEX_C);
    printf("\n");
            
				/* PER VALORE (int buffer [DIM])*/
	printf("Il valore Consumato(int buffer[DIM])= [%d]\n",v->buffer[indice]);
	/*.....................*/	
	
			/* PER VALORE (char buffer2 [DIM])*/	
	printf("Il valore Consumato(char buffer2[DIM])= [%c]\n",v->buffer2[indice]);
 	/*.....................*/	      
 	      		
    v->stato[indice] = BUFFER_VUOTO;
	
    Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
    
}

/*.............END.............*/
