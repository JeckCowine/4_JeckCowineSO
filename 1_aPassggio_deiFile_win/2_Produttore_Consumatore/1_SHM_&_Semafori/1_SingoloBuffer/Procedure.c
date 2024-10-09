
#include "Header.h"

void Set_Dati(Struct* s,int ds_sem){
	
	semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, 1); // Si setta Spazio a 1 perchè è libero 
	semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);// Messaggio a 0 perchè non esiste

	s->intero=0;
	s->carattere='0';
	s->array[DIM]=0;
	s->stringa[DIM]='0';
	
}

void Remove_Dati(Struct* s, int ds_sem, int ds_shm){
	
	shmctl(ds_shm, IPC_RMID, NULL); 
    semctl(ds_sem, 0, IPC_RMID); 
    
    printf("\n\t\t<FINE>\n");
	
}   

void Produzione(Struct* s, int ds_sem) {

	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE); 

	int val_1=0; char val_2='0'; Array val_3={0}; Stringa val_4="0";
	
	val_1 = 10 + rand () % 88; 
	s->intero = val_1;
	
	val_2 = 'A' + (rand () % 26) ; 
	s->carattere= val_2;
	
	val_3[0]= 10 + rand() % 88; 
	s->array[0] = val_3[0];
	val_3[1]= 10 + rand() % 88; 
	s->array[1] = val_3[1];
	
	for(int i=0;i<DIM;i++){ 
		val_4[i] = 'A' + (rand () % 26) ; 
		s->stringa[i] = val_4[i]; }
	
	printf("Prodottuttore [%d]= [%d]--[%d,%d]--[%c]--[%s]\n",getpid(), val_1,val_3[0],val_3[1],val_2,val_4);

	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void Consumazione(Struct* s, int ds_sem) {

	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE); 
	
	int val_1=0; char val_2='0'; Array val_3={0}; Stringa val_4="0";
	
	val_1 = s->intero;
	val_2 = s->carattere;
	val_3[0] = s->array[0];
	val_3[1] = s->array[1];
	for(int i=0;i<DIM;i++) val_4[i] = s->stringa[i];
			
	printf("Consumatore   [%d]= [%d]--[%d,%d]--[%c]--[%s]\n",getpid(), val_1,val_3[0],val_3[1],val_2,val_4);
	
	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE); 
}

