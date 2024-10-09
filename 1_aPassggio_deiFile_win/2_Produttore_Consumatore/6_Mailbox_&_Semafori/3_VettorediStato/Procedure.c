/*.............VETTOREDISTATO_C.............*/

#include "Header.h"

void Set_Dati(Struct* v, int ds_sem) {

    semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM);
    semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    semctl(ds_sem, MUTEX_C, SETVAL, 1);
    semctl(ds_sem, MUTEX_P, SETVAL, 1);

	v->array[DIM]=0;
	v->stringa[DIM]='0';
	v->stato[DIM]=0;	
	
}

void Remove_Dati(Struct* v, int ds_sem, int ds_shm){
	
	shmctl(ds_shm, IPC_RMID, NULL); 
    semctl(ds_sem, 0, IPC_RMID); 
	    
    printf("\n\t\t<FINE>\n");
    
}   

void Produzione(Struct* v, int ds_sem) {
    
    Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);  
    Wait_Sem(ds_sem, MUTEX_P);

	int indice=0; Array val_1={0}; Stringa val_2="0";
		         
    while(indice <= DIM && v->stato[indice] != BUFFER_VUOTO) {
        indice++;
    }
    
    v->stato[indice] = BUFFER_INUSO;
    	
    Signal_Sem(ds_sem, MUTEX_P);
        
	val_1[0]= 10 + rand() % 88; 
	v->array[indice] = val_1[0];
														//VALORI INVIATI
	val_2[0] = 'A' + (rand () % 26) ; 
	v->stringa[indice] = val_2[0];
	
	printf("Prodottuttore [%d] = [%d]--[%s]\n",getpid(), val_1[0],val_2);
	
	v->stato[indice] = BUFFER_PIENO;
    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
	
}

void Consumazione(Struct* v, int ds_sem) {
        
    Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    Wait_Sem(ds_sem, MUTEX_C); 
    
    int indice =0; Array val_1={0}; Stringa val_2="0";
              
    while(indice <= DIM && v->stato[indice] != BUFFER_PIENO) {
        indice++;
    }
    
    v->stato[indice] = BUFFER_INUSO;
    
    Signal_Sem(ds_sem, MUTEX_C);
	
	val_1[0] = v->array[indice];
													//VALORI RICEVUTI
	val_2[0] = v->stringa[indice]; 
			
	printf("Consumatore   [%d] = [%d]--[%s]\n", getpid(), val_1[0],val_2);
		
	v->stato[indice] = BUFFER_VUOTO;
	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
 
}

/*.............END.............*/
