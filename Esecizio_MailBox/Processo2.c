/************* PROCESSO2_C ****************/

#include "CodaMessaggi.h"

int main(){
		
	key_t Chiave_Coda = ftok (".",'p');
	
	int ds_coda = msgget (Chiave_Coda,IPC_CREAT | 0664);
	if(ds_coda<0) { perror("Coda_2 Error"); exit(1); }
	
	Coda c;
	
	c.tipo=p2;
	
	for(int i=0;i<DIM_MSG_p2;i++){ //INVIA 5 MESSAGGI
		
		srand(getpid()*time(NULL));
		c.intero=GeneraValore(1,20); //Genera Valori Da 10 a 20 (SI CONTA ANCHE IL 10)
		c.carattere=GeneraCarattere('A',4); //Genera un Carattere Da A a D (SI CONTA ANCHE A)
		for(int i=0;i<DIM_INT;i++) { c.array[i]= 10 + rand () % 11;}
		//Genera Valori Da 10 a 20 (SI CONTA ANCHE IL 10)
        for(int i=0;i<DIM_STRING;i++) {c.stringa[i] = 'A' + (rand () % 7);}
        //Genera un Carattere Da A a G (SI CONTA ANCHE A)
		c.stringa[DIM_STRING-1]='\0'; //CARATTERE TERMINALE
		
		msgsnd (ds_coda,(void*) &c,sizeof(Coda) - sizeof(long),IPC_NOWAIT); //INVIO MESSAGGIO SU CODA
		
		//STAMPE VALORI INVIATI
		printf("Mesaggio Inviato<n°%d>, PROCESSO < %lu > \n",i+1,c.tipo);
		printf("\tVALORE_FLOAT < %3.1f > \n",c.intero);
		printf("\tVALORE_CHAR < %c >\n",c.carattere);
		printf("\tVALORE_ARRAY < "); 
		for(int i=0;i<DIM_INT;i++) printf("[%d] ",c.array[i]);
		printf(">\n");
		printf("\tVALORE_STRINGA < %s >\n",c.stringa);
		sleep(2);
		
	}
	
	
}


/****END****/
