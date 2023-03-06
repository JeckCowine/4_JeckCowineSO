
#include "Header.h"

void Produttore(Struct*,int,int);
void Consumatore(Struct*,int,int);
void StampaInfo();

int main() {

	StampaInfo();
	
	pid_t pid; 
	
	key_t Chiave_SHM = ftok ("./",'S');	// chiave della shared memory
	key_t Chiave_MSG = ftok("./",'M');  //chiave del messaggio
	key_t Chiave_SEM = ftok ("./",'S');  // chiave del semaforo
	
	//Inizializzazione Shared Memory Struct
	
	int ds_shm = shmget(Chiave_SHM, sizeof(Struct), IPC_CREAT | 0664);
	if(ds_shm<0) { perror("SHM errore"); exit(1); }
	Struct* s;			
	s = (Struct*) shmat(ds_shm, NULL, 0);
	
	//FINE

	//Inizializzazione Messaggio
	
	int mess=msgget(Chiave_MSG,IPC_CREAT|0664);
	if(mess<0) { perror("MSG errore"); exit(1); }
	
	//Inizializzazione Semaforo, 2 semafori
	
	int ds_sem = semget(Chiave_SEM, 2, IPC_CREAT|0664);
	if(ds_sem<0) { perror("SEM errore"); exit(1); }
    
	//FINE
	
	Set_Dati(s,ds_sem);

	for(int i=0;i<Num_Produttori;i++){
		pid=fork();
		if(pid<0) { perror("Fork errore"); exit(1); }
		else if(pid==0){
			Produttore(s,mess,ds_sem);
			exit(0);
		}
		
	}
		
	for(int i=0;i<Num_Consumatori;i++){
		pid=fork();	
		if(pid<0) { perror("Fork errore"); exit(1); }
		else if(pid==0){
			Consumatore(s,mess,ds_sem);
			exit(0);
		}
	}
	
	for(int i=0;i<Num_Processi;i++){
		wait(NULL);	
	}
    
    Remove_Dati(mess,ds_sem,ds_shm);
        
    return 0;
}

void Produttore(Struct* s,int mess,int ds_sem){
	
	srand(getpid()*time(NULL));
	for(int i=0;i< Num_Produzioni;i++){
		sleep(1);
		Produzione(s,mess,ds_sem);
		Prova(mess);
	}
	
}

void Consumatore(Struct* s,int mess,int ds_sem){
	
	for(int i=0;i< Num_Consumazioni;i++){
		sleep(1);
		Consumazione(s,mess,ds_sem);
	}
	
}

void StampaInfo(){
		
	printf("\n\t\tINFO\n");
	printf("<%d>Produttori  con <%d>Produzioni  <TOT=%d>\n",Num_Produttori,Num_Produzioni,Tot_Produttori);
	printf("<%d>Consumatori con <%d>Consumazioni<TOT=%d>\n",Num_Consumatori,Num_Consumazioni,Tot_Consumatori);
	printf("<%d>Processi Totali\n",Tot_Produttori+Tot_Consumatori);
	printf("\n\t<AVVIO COMPILAZIONE>\n\n");
	printf("\t\t\tInt   Array   Char Stringa\n");
	
}
