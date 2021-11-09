/*.............SINGLEBUFFER_C.............*/

#include "SingleBuff.h"

void Set_Dati(SingleBuff* s,int ds_sem){
	
	//Semafori di COOPERAZIONE tra i Produttori e Consumatori
	semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, 1); //Si setta Spazio a 1 perchè è libero 
	semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);//Messaggio a 0 perchè non esiste
	//Inizializzazione dei valori da passare tra i Produttori e Consumatori	
	s->intero=0;
	s->carattere='0';
	for(int i=0;i<DIM_INT;i++) s->array[i]=0;
	for(int i=0;i<DIM_STRING;i++) s->stringa[i]='0';
	
}

void Remove_Dati(SingleBuff* s, int ds_sem, int ds_shm){
	
	s->intero=0;
	s->carattere='0';
	for(int i=0;i<DIM_INT;i++) s->array[i]=0;
	for(int i=0;i<DIM_STRING;i++) s->stringa[i]='0';
	shmctl(ds_shm, IPC_RMID, NULL); // rimozione chiave della shared memory
    semctl(ds_sem, 0, IPC_RMID); //rimozione chiave del semaforo)
	
}   

void Produttore(SingleBuff* s, int ds_sem) {

	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE); //Wait funzione semaforo
	sleep(1);
	srand(time(NULL)); // Serve a scegliere sempre un valore diverso a ogni compilazione
	printf("\n");
			/* PER VALORE (int intero)*/
	s->intero = 1 + rand () % 999; // Valore casuale da 1 a 1.000
	printf("Valore Prodotto(int intero) = [%d]\n", s->intero); //ELEMENTO SINGOLO int
	/*.....................*/	
	
				/* PER VALORE (char carattere)*/
	s->carattere= 'A' + (rand () % 26) ; // Valore casuale da 'A' a 'Z'
	printf("Valore Prodotto(char carattere)= [%c]\n", s->carattere); //ELEMENTO SINGOLO char
	/*.....................*/	
	
			/* PER VALORE (int array [DIM])*/
	for(int i=0;i<DIM_INT;i++){
		s->array[i] = 1 + rand() %999; // Valore casuale da 1 a 1.000 per DIM volte
	}
	printf("Valore Prodotto(int array[DIM])= ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]", s->array[i]); //ARRAY(INT) DI DIMENSIONE DIM
	printf("\n");
	/*.....................*/	
	
			/* PER VALORE (char stringa [DIM])*/
	for(int i=0;i<DIM_STRING;i++){
		s->stringa[i] = 'A' + (rand () % 26) ; // Valore casuale da 'A' a 'Z' per DIM volte
	}
	printf("Valore Prodotto(char stringa[DIM])= [%s]\n", s->stringa);//STRINGA(CHAR) DI DIMENSIONE DIM
	/*.....................*/	

	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE); //Signal funzione semaforo
}

void Consumatore(SingleBuff* s, int ds_sem) {

	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE); //Wait funzione semaforo
	sleep(1);
	printf("\n");	
			/* PER VALORE (int intero)*/	
	printf("Valore Consumato(int intero) = [%d]\n", s->intero);
	/*.....................*/	

			/* PER VALORE (char carattere)*/	
	printf("Valore Consumato(char carattere)= [%c]\n", s->carattere);
	/*.....................*/	
	
			/* PER VALORE (int array [DIM])*/	
	printf("Valore Consumato(int array[DIM])= ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]", s->array[i]); 
	printf("\n");
	/*.....................*/	

			/* PER VALORE (char Stringa [DIM])*/	
	printf("Valore Consumato(char stringa[DIM])= [%s]\n", s->stringa);
	/*.....................*/		

	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE); //Signal funzione semaforo
}

/*.............END.............*/
