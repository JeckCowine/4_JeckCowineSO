/************* PROCESSO1_C ****************/

#include "CodaMessaggi.h"

int main(){
		
	key_t Chiave_Coda = ftok (".",'p');
		
	int ds_coda = msgget (Chiave_Coda,IPC_CREAT | 0664);
	if(ds_coda<0) { perror("Coda_1 Error"); exit(1); }
	
	Coda c;
	
	c.tipo=p1;
	int check;
	
	for(int i=0;i<DIM_MSG_p1;i++){ //INVIA 5 MESSAGGI
		
		srand(getpid()*time(NULL));
		c.intero=GeneraValore(0,10); //Genera Valori Da 0 a 10 (SI CONTA ANCHE LO 0)
		c.carattere=GeneraCarattere('G',3); //Genera un Carattere Da G a I (SI CONTA ANCHE G)
		for(int i=0;i<DIM_INT;i++) { c.array[i]= 1 + rand () % 25;}
		//Genera Valori Da 1 a 25 (SI CONTA ANCHE IL 1)
		for(int i=0;i<DIM_STRING;i++) {c.stringa[i] = 'R' + (rand () % 4);}
		//Genera un Carattere Da R a U (SI CONTA ANCHE R)
		c.stringa[DIM_STRING-1]='\0'; //CARATTERE TERMINALE
		
		check = msgsnd (ds_coda,(void*) &c,sizeof(Coda) - sizeof(long),IPC_NOWAIT); //INVIO MESSAGGIO SU CODA
		if(check<0) {perror("msgsnd error");_exit(1);}
		
		//STAMPE VALORI INVIATI
		printf("Mesaggio Inviato<n°%d>, PROCESSO < %lu > \n",i+1,c.tipo);
		printf("\tVALORE_FLOAT < %3.1f > \n",c.intero);
		printf("\tVALORE_CHAR < %c >\n",c.carattere);
		printf("\tVALORE_ARRAY < "); 
		for(int i=0;i<DIM_INT;i++) printf("[%d] ",c.array[i]);
		printf(">\n");
		printf("\tVALORE_STRINGA < %s >\n",c.stringa);
		sleep(1);

	}
	
	
}


/****END****/
