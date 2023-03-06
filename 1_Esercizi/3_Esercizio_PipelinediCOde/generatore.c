#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"


void generatore_produttore(ProdCons*pc){
        
    enter_monitor(&(pc->m));
    
    while(pc->num_elementi==DIM_QUEUE){
			wait_condition(&(pc->m), VARCOND_GEN_PRODUTTORI);
	}
	
	srand(getpid()*time(NULL));
	
	pc->msg[testa].tipo=MSG_TYPE;
	
	//Variabile singola, uguale a 0
	pc->msg[testa].variabile=0;
	
	//Valore da 0 a 9, due numeri
	for(int i=0;i<DIM_INT;i++){
		pc->msg[testa].array[i]=rand()%9;
	}
	
	//Stringa di 10 caratteri
	for(int i=0;i<DIM_STRING;i++){
		pc->msg[testa].stringa[i]='A'+ (rand () % 26);
	}
	
	pc->msg[testa].stringa[DIM_STRING-1]='\0';
	
    printf("[Produttore] [%d]\n",getpid());
    printf("[Produttore]-> msg.stringa: %s\n", pc->msg[testa].stringa);
    printf("[Produttore]-> msg.array[0]: %d\n", pc->msg[testa].array[0]);
    printf("[Produttore]-> msg.array[1]: %d\n", pc->msg[testa].array[1]);
    printf("[Produttore]-> msg.var: %d\n", pc->msg[testa].variabile);
 
	pc->testa = (pc->testa+1) %DIM_QUEUE;
	pc->num_elementi++;
	
	signal_condition(&(pc->m),VARCOND_GEN_CONSUMATORI);
	
	leave_monitor(&(pc->m));
	
}

void generatore_consumatore(ProdCons*pc, int gen_to_filter){

    enter_monitor(&(pc->m));
    
    while(pc->num_elementi==0){
			wait_condition(&(pc->m), VARCOND_GEN_CONSUMATORI);
	}   
	
    printf("[Consumatore] [%d]\n",getpid());
    printf("[Consumatore]-> msg.stringa: %s\n", pc->msg[coda].stringa);
    printf("[Consumatore]-> msg.array[0]: %d\n", pc->msg[coda].array[0]);
    printf("[Consumatore]-> msg.array[1]: %d\n", pc->msg[coda].array[1]);
    printf("[Consumatore]-> msg.var: %d\n", pc->msg[coda].variabile);
  
    int ret = msgsnd(gen_to_filter,&(pc->msg[pc->coda]),sizeof(Message) - sizeof(long),0);
    if (ret<0){ perror("Error msgsnd"); exit(-1);
    }
    
    printf("[Consumatore] [%d] MSG INVIATO AL FILTER\n",getpid());

	pc->coda = (pc->coda+1) %DIM_QUEUE;    
    pc->num_elementi--;
    	
    signal_condition(&(pc->m),VARCOND_GEN_PRODUTTORI);
    
    leave_monitor(&(pc->m));
    
}

