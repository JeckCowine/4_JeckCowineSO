
#include "Header.h"

void Set_Dati(Struct* m,int ds_sem){
		
	semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, 1); // Si setta Spazio a 1 perchè è libero 
	semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);// Messaggio a 0 perchè non esiste

	m->msg.intero=0;
	m->msg.carattere='0';
	m->msg.array[DIM]=0;
	m->msg.stringa[DIM]='0';
	
}

void Remove_Dati(int mess, int ds_sem,int ds_shm){
	
	msgctl(mess,IPC_RMID,0);
	shmctl(ds_shm, IPC_RMID,NULL); 
    semctl(ds_sem, 0, IPC_RMID); 
    
    printf("\n\t\t<FINE>\n");
	
}   

void Produzione(Struct* s,int mess, int ds_sem) {
	
	Wait_Sem(ds_sem, SPAZIO_DISPONIBILE); 
	
	s->msg.tipo=MESSAGGIO;
	s->msg.intero= 10 + rand () % 88; 
	s->msg.carattere = 'A' + (rand () % 26) ; 
	s->msg.array[0]= 10 + rand() % 88; 
	s->msg.array[1]= 10 + rand() % 88; 

	for(int i=0;i<DIM;i++){ 
		s->msg.stringa[i]= 'A' + (rand () % 26) ; 
	}
	
	printf("Producer [%d]= [%d]--[%d,%d]--[%c]--[%s]\n",getpid(),s->msg.intero,s->msg.array[0],s->msg.array[1],s->msg.carattere,s->msg.stringa);

	int ret = msgsnd(mess,&(s->msg),sizeof(message) - sizeof(long),0);
    if (ret<0){ perror("Error msgsnd"); exit(-1);}
    
	Signal_Sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void Consumazione(Struct* s,int mess, int ds_sem) {
	
	Wait_Sem(ds_sem, MESSAGGIO_DISPONIBILE); 
	    
	printf("Consumer [%d]= [%d]--[%d,%d]--[%c]--[%s]\n",getpid(),s->msg.intero,s->msg.array[0],s->msg.array[1],s->msg.carattere,s->msg.stringa);
	
	Signal_Sem(ds_sem, SPAZIO_DISPONIBILE); 
}

