/*.............MAIN_C.............*/

#include "Procedure.h"

int main() {
	
	printf("Esercizio Produttore Consumatore Vettore di Stato con Monitor_Signal_Continue\n\n");
	
	pid_t pid; 
	key_t Chiave_SHM = ftok ("./Vettore",'V');	// chiave della shared memory
		
	//Inizializzazione Shared Memory Struct
	
	int ds_shm = shmget(Chiave_SHM, sizeof(Vettore), IPC_CREAT | 0664);
	if(ds_shm<0) { perror("SHM errore"); exit(1); }
	Vettore* v;			
	v = (Vettore*) shmat(ds_shm, NULL, 0);
	
	//FINE
	
	Set_Dati(v);
	
	for(int i=0;i<Num_Produttori;i++){
		
		pid=fork();
		if(pid==0){
				//figlio Produttore
			printf("\tPRODUTTORE[%d]",i+1);
			Produttore(v);
			exit(0);
		}
		
	}
		
	for(int i=0;i<Num_Consumatori;i++){
		pid=fork();	
		if(pid==0){
				//figlio Consumatore
			printf("\tCONSUMATORE[%d]",i+1);
			Consumatore(v);
			exit(0);
		}
	}
	
	
	for(int i=0;i<Num_Consumatori+Num_Produttori;i++){
		wait(NULL);	
	}
	
	Remove_Dati(v);
	
	shmctl(ds_shm,0,IPC_RMID);
	
	return 0;
}

/*.............END.............*/
