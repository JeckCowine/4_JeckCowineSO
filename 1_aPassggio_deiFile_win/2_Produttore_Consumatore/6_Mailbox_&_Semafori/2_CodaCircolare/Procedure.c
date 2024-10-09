
#include "Header.h"

void Set_Dati(Struct* c, int ds_sem) {
	
	//Semafori di COOPERAZIONE tra i Produttori e Consumatori
    semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM);
    semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    //Semafori di COMPETIZIONE tra i Produttori e Consumatori
    semctl(ds_sem, MUTEX_C, SETVAL, 1);
    semctl(ds_sem, MUTEX_P, SETVAL, 1);

	c->mess[0].array[0]=0;
	c->mess[0].stringa[0]='0';
	
	c->testa=0;
	c->coda=0;
	
}

void Remove_Dati(Struct* c, int ds_msg, int ds_sem, int ds_shm){
	
	msgctl(ds_msg,IPC_RMID,0);
	shmctl(ds_shm, IPC_RMID, NULL); // rimozione chiave della SHM
    semctl(ds_sem, 0, IPC_RMID); //rimozione chiave del SEM
    
    printf("\n\t\t<FINE>\n");
	
}   

void Produzione(Struct * c, int ds_msg,int ds_sem) {
    
   
	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE);
	Wait_Sem(ds_sem, MUTEX_P);  
	
       //PRODUZIONE IN TESTA DELLA CODA
	
	Array val_1={0}; Stringa val_2="0";
	
	ds_msg = 0; 
	
	c->mess[c->testa].tipo= MESSAGGIO;
	
	c->mess[c->testa].array[0]= 100 + rand () % 899;  
	c->mess[c->testa].stringa[0]= 'A' + (rand () % 26); 
	
	//val_1[0]= c->mess[c->testa].array[0];
	//val_2[0]= c->mess[c->testa].stringa[0];
	
	c->testa = (c->testa+1) % DIM;
	
	printf("Prodottuttore [%d] = [%d]--[%s]\n",getpid(), val_1[0],val_2);	
	
	//int ret=msgsnd(ds_msg,&(c->mess[c->testa]),sizeof(Message)- sizeof(long),0);
	//if(ret<0){perror("Errore MSGSND"); exit(1);}
	
    Signal_Sem(ds_sem, MUTEX_P);
    Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
	
}

void Consumazione(Struct * c, int ds_msg,int ds_sem) {
    
	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
    Wait_Sem(ds_sem, MUTEX_C);

        //CONSUMAZIONE IN CODA
	
	Array val_1={0};
	Stringa val_2="0";
		
	//int ret = msgrcv(ds_msg,&(c->mess[c->coda]),sizeof(Message)-sizeof(long),0,0);
	//if(ret<0){perror("Error MSGRCV"); exit(1);}
	
	val_1[0]=c->mess[c->coda].array[0];
	val_2[0]=c->mess[c->coda].stringa[0];
 	      		
	c->coda = (c->coda + 1) % DIM;
	
	printf("Consumatore   [%d] = [%d]--[%s]\n",getpid(), val_1[0],val_2);	
	
    Signal_Sem(ds_sem, MUTEX_C);
    Signal_Sem(ds_sem, SPAZIO_DISPONIBILE);
  
}

