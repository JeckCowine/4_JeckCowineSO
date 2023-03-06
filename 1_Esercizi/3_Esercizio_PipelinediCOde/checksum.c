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

void checksum(int filter_to_checksum, int checksum_to_visual){

        int checksum;
        Message mess;

        for (int i=0; i<NUM_MESSAGES; i++){

                printf("[CHECKSUM] [%d] MSG RICEVUTO DAL FILTER\n",getpid());

                int ret = msgrcv(filter_to_checksum,&mess,sizeof(Message) - sizeof(long),0,0);
				if(ret<0) {
                        if (errno == ENOMSG){ printf("Finish Msg..exit!\n"); break;}
                        else{perror("ERROR!!!"); exit(-1);}
                }
                                
                for(int j=0;j<DIM_STRING;j++){
						checksum+=mess.stringa;
				}
				
				for(int j=0;j<DIM_INT;j++){
					checksum+=mess.array[i];
				}
                
                mess.variabile = checksum;
                printf("[CHECKSUM] [RISULTATO]->[%d]",mess.variabile);
                
                ret = msgsnd(checksum_to_visual,&mess,sizeof(Message)- sizeof(long),0);
                if(ret<0){perror("Error Msgsnd"); exit(1);}
                
                printf("[CHECKSUM] INVIO AL VISUALIZZATORE..\n");
                
        }
        
        exit(0);
}

