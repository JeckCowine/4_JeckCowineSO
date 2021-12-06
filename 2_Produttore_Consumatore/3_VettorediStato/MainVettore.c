/*.............MAIN_C.............*/

#include "VettorediStato.h"

int main() {
	
	printf("Esercizio Produttore Consumatore con Vettore di Stato con Semafori\n\n");

	pid_t pid;
	key_t Chiave_SHM = ftok("./VettoreDiStato",'V'); // chiave della shared memory
	key_t Chiave_SEM = ftok("./VettoreDiStato",'V'); // chiave del semaforo
	
	//Inizializzazione Shared Memory Struct
	
	int ds_shm = shmget(Chiave_SHM, sizeof(Vettore), IPC_CREAT|0664);
	if(ds_shm<0) { perror("SHM errore"); exit(1); }
	Vettore * v;
	v = (Vettore *) shmat(ds_shm, NULL, 0); 
	
	//FINE

	//Inizializzazione Semaforo, 4 semafori
	
	int ds_sem = semget(Chiave_SEM, 4, IPC_CREAT|0664);
	if(ds_sem<0) { perror("SEM errore"); exit(1); }

	//FINE
	
	Set_Dati(v,ds_sem);
	
	for(int i=0;i<Num_Consumatori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Consumatore
			printf("\tCONSUMATORE[%d]",i+1);
			Consumatore(v, ds_sem);
			exit(1);
			}
		}

	for(int i=0;i<Num_Produttori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Produttore
			printf("\tPRODUTTORE[%d]",i+1);
			Produttore(v, ds_sem);
			exit(1);
			}
		}

	for(int i=0; i<Num_Consumatori+Num_Produttori; i++) {
		//fine produttori consumatori
		wait(NULL);
	}
	
	Remove_Dati(v,ds_sem,ds_shm);
	
    return 0;
}

/*.............END.............*/
