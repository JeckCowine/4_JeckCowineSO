
#include "Header.h"

void Set_Dati(Struct* c, int ds_sem) {
	
	//Semafori di COOPERAZIONE tra i Produttori e Consumatori
    semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM);
    semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    //Semafori di COMPETIZIONE tra i Produttori e Consumatori
    semctl(ds_sem, MUTEX_C, SETVAL, 1);
    semctl(ds_sem, MUTEX_P, SETVAL, 1);

	c->testa=0;
	c->coda=0;
	c->buffer[DIM]=0;	
	c->numero_elementi=0;	
	c->buffer2[DIM]='0';
	
}

void Remove_Dati(Struct* c, int ds_sem, int ds_shm){
	
	shmctl(ds_shm, IPC_RMID, NULL); // rimozione chiave della SHM
    semctl(ds_sem, 0, IPC_RMID); //rimozione chiave del SEM
    
    printf("\n\t\t<FINE>\n");
	
}   

void Produzione(Struct * c, int ds_sem) {
    
    if(c->numero_elementi==DIM){
		Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
		Wait_Sem(ds_sem, MUTEX_P);  
	}
	
       //PRODUZIONE IN TESTA DELLA CODA
	
	Array val_1={0}; Stringa val_2="0";
	
    val_1[0] = 100 + rand () % 899; 
	c->buffer[c->testa]= val_1[0]; 
		
	val_2[0] = 'A' + (rand () % 26); 
	c->buffer2[c->testa]= val_2[0]; 
		
	c->testa = (c->testa+1) % DIM;
	c->numero_elementi= c->numero_elementi+1;
	
	printf("Prodottuttore [%d] = [%d]--[%s]\n",getpid(), val_1[0],val_2);	
	
	if(c->numero_elementi>1){
    Signal_Sem(ds_sem, MUTEX_P);
    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
	}
	
}

void Consumazione(Struct * c, int ds_sem) {
    
    if(c->numero_elementi<2){
		Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    	Wait_Sem(ds_sem, MUTEX_C);
	}
	
        //CONSUMAZIONE IN CODA
	
	Array val_1={0},val_3={0};
	Stringa val_2="0",val_4="0";
		
	val_1[0]=c->buffer[c->coda];
	val_2[0]=c->buffer2[c->coda];
 	      		
	c->coda = (c->coda + 1) % DIM;

	val_3[0]=c->buffer[c->coda];
	val_4[0]=c->buffer2[c->coda];
 	      		
	c->coda = (c->coda + 1) % DIM;
	c->numero_elementi=c->numero_elementi - 2;
	
	printf("Consumatore   [%d] = [%d]--[%s]\n\t\t\t[%d]--[%s]\n",getpid(), val_1[0],val_2,val_3[0],val_4);	
	
    Signal_Sem(ds_sem, MUTEX_C);
    Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
  
}

