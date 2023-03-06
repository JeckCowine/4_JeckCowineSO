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

void visualizzatore(int checksum_to_visual){

        Message mess;

        for (int i=0; i<NUM_MESSAGES; i++){
                printf("[VISUALIZZATORE] [%d] MSG RICEVUTO DAL CHECKSUM\n",getpid());
                	
                int ret = msgrcv(checksum_to_visual,&mess,sizeof(Message) - sizeof(long),0,0);
				if(ret<0) {
					if (errno == ENOMSG){ printf("Finiti MSG...exit!\n");break;}
					else{perror("ERRORE!!!");exit(-1);}
					} else {
							printf("[Visualizzatore] [%d]\n",getpid());
							printf("[Visualizzatore]-> msg.stringa: %s\n", mess.stringa);
							printf("[Visualizzatore]-> msg.array[0]: %d\n", mess.array[0]);
							printf("[Visualizzatore]-> msg.array[1]: %d\n", mess.array[1]);
							printf("[Visualizzatore]-> msg.var: %d\n", mess.variabile);
						}
        }
        
        exit(0);
}

