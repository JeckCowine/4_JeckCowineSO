/*.............CODACIRCOLARE_C.............*/

#include "CodaCircolare.h"

void Set_Dati(Coda* c, int ds_sem) {

	//Semafori di COOPERAZIONE tra i Produttori e Consumatori
    semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM);
    semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    //Semafori di COMPETIZIONE tra i Produttori e Consumatori
    semctl(ds_sem, MUTEX_C, SETVAL, 1);
    semctl(ds_sem, MUTEX_P, SETVAL, 1);
   //Inizializzazione testa e coda  
	c->testa=0;
	c->coda=0;
	 //Inizializzazione dei valori da passare tra i Produttori e Consumatori
	c->buffer[DIM]=0;	
	c->buffer2[DIM]='0';
	
}

void Remove_Dati(Coda* c, int ds_sem, int ds_shm){
	
	c->testa=0;
	c->coda=0;
	c->buffer[DIM]=0;	
	c->buffer2[DIM]='0';
	shmctl(ds_shm, IPC_RMID, NULL); // rimozione chiave della SHM
    semctl(ds_sem, 0, IPC_RMID); //rimozione chiave del SEM
	
}   

void Produttore(Coda * c, int ds_sem) {
    
    Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);  
    Wait_Sem(ds_sem, MUTEX_P);

    sleep(2);
    printf("\n");
    srand(time(NULL));// Serve a scegliere sempre un valore diverso a ogni compilazione
        //PRODUZIONE IN TESTA DELLA CODA
	
				/* PER VALORE (int buffer [DIM])*/
	c->buffer[c->testa]= 1 + rand () % 999; // Valore casuale da 1 a 1.000
	printf("Il valore Prodotto(int buffer[DIM])= [%d]\n",c->buffer[c->testa]); //ELEMENTO SINGOLO int
	/*.....................*/		
	
			/* PER VALORE (char buffer2 [DIM])*/
	c->buffer2[c->testa]='A' + (rand () % 26); // Valore casuale da 'A' a 'Z'
	printf("Il valore Prodotto(char buffer2[DIM])= [%c]\n",c->buffer2[c->testa]); //ELEMENTO SINGOLO char
	/*.....................*/	
		
	c->testa = (c->testa+1) % DIM;
	  
    Signal_Sem(ds_sem, MUTEX_P);
    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    
}

void Consumatore(Coda * c, int ds_sem) {
    
    Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    Wait_Sem(ds_sem, MUTEX_C);
    
    sleep(2);
    printf("\n");
            //CONSUMAZIONE IN CODA
            
				/* PER VALORE (int buffer [DIM])*/
	printf("Il valore Consumato(int buffer[DIM])= [%d]\n",c->buffer[c->coda]);
	/*.....................*/	
	
			/* PER VALORE (char buffer2 [DIM])*/	
	printf("Il valore Consumato(char buffer2[DIM])= [%c]\n",c->buffer2[c->coda]);
 	/*.....................*/	      		
 	      		
	c->coda = (c->coda + 1) % DIM;
	
    Signal_Sem(ds_sem, MUTEX_C);
    Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
    
}

/*.............END.............*/
