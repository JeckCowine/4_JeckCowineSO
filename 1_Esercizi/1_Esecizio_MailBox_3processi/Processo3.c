/************* PROCESSO3_C ****************/

#include "CodaMessaggi.h"

int main(){
	
	key_t Chiave_Coda = ftok (".",'p');
	
	int ds_coda = msgget (Chiave_Coda,IPC_CREAT | 0664);
	if(ds_coda<0) { perror("Coda_3 Error"); exit(1); }
	float media[2]={0};
	float vettore1_int[DIM_MSG_p1+DIM_MSG_p2]={0};
	float vettore2_int[DIM_MSG_p1+DIM_MSG_p2]={0};
	
	Coda c;
		
	for(int i=0;i<DIM_MSG_p1+DIM_MSG_p2;i++){ //RICEVE DIM_MSG_p1(5) + DIM_MSG_p2(5) --> 10MSG
		
		msgrcv(ds_coda,(void*)&c,sizeof(Coda)-sizeof(long),0,0); //RICEVO MESSAGGIO SU CODA
	
		//STAMPE DEI MESSAGGI RICEVUTI
		printf("Mesaggio Ricevuto<n°%d>, PROCESSO < %lu > \n",i+1,c.tipo);
		printf("\tVALORE_FLOAT < %3.1f > \n",c.intero);
		printf("\tVALORE_CHAR < %c >\n",c.carattere);		
		printf("\tVALORE_ARRAY < "); 
		for(int i=0;i<DIM_INT;i++) printf("[%d] ",c.array[i]);
		printf(">\n");
		printf("\tVALORE_STRINGA < %s >\n",c.stringa);	
		if(c.tipo == p1){
			//SERVE PER CALCOLARE LA MEDIA DEI NUMERI
			vettore1_int[i]=c.intero;
			media[p1-1]+=c.intero / DIM_MSG_p1;
		}
		else if(c.tipo == p2) {
			//SERVE PER CALCOLARE LA MEDIA DEI NUMERI
			vettore2_int[i]=c.intero;
			media[p2-1]+=c.intero / DIM_MSG_p2;
		}
		
	}
	
	printf("\nCalcolo n°1 Media, Valori tra 0 a 10\nTra: ");
	
	for (int i=0;i<DIM_MSG_p1+DIM_MSG_p2;i++) {
		if(vettore1_int[i]!=0){
			printf("< %3.1f > ",vettore1_int[i]);
			}
	}
	
	printf("= [%3.2f]\n",media[0]);
	
	printf("\nCalcolo n°2 Media, Valori tra 1 a 20\nTra: ");
	
	for (int i=1;i<DIM_MSG_p1+DIM_MSG_p2;i++) {
		 if(vettore2_int[i]!=0){
			printf("< %3.1f > ",vettore2_int[i]);
			}
	}
		
	printf("= [%3.2f]\n",media[1]);

	msgctl(ds_coda,IPC_RMID,0);
	
	return 0;
	
}


/****END****/
