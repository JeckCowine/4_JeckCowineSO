/*.............MAIN_C.............*/

#include "Procedure.h"

int main() {
	
	printf("Esercizio Produttore Consumatore Coda CIrcolare con Monitor_Signal_Continue\n\n");
	
	pid_t pid; 
	key_t Chiave_SHM = ftok ("./Coda",'C');	// chiave della shared memory
		
	//Inizializzazione Shared Memory Struct
	
	int ds_shm = shmget(Chiave_SHM, sizeof(Coda), IPC_CREAT | 0664);
	if(ds_shm<0) { perror("SHM errore"); exit(1); }
	Coda* c;			
	c = (Coda*) shmat(ds_shm, NULL, 0);
	
	//FINE
	
	Set_Dati(c);
	
	for(int i=0;i<Num_Produttori;i++){
		
		pid=fork();
		if(pid==0){
				//figlio Produttore
			printf("\tPRODUTTORE[%d]",i+1);
			Produttore(c);
			exit(0);
		}
		
	}
		
	for(int i=0;i<Num_Consumatori;i++){
		pid=fork();	
		if(pid==0){
				//figlio Consumatore
			printf("\tCONSUMATORE[%d]",i+1);
			Consumatore(c);
			exit(0);
		}
	}
	
	
	for(int i=0;i<Num_Consumatori+Num_Produttori;i++){
		wait(NULL);	
	}
	
	Remove_Dati(c);
	
	shmctl(ds_shm,0,IPC_RMID);
	
	return 0;
}

/*.............END.............*/
