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

void filtro(int gen_to_filter, int filter_to_checksum){

        Message mess;

        for (int i=0; i<NUM_MESSAGES; i++){
				
                int ret = msgrcv(gen_to_filter,&mess,sizeof(Message) - sizeof(long),0,0); 
				if(ret<0) {perror("Error msgrcv"); exit(-1);}

                printf("[FILTER] [%d]  MSG RICEVUTO DAL GENERATORE #%d  RIMANGONO %d MSG\n", getpid(),i+1,NUM_MESSAGES);

                if(strchr(mess.stringa,'X')!=NULL){ printf("NON TROVATA 'X', String->%s\n",mess.stringa)}
                else {
					printf("'X' TROVATA, String->%s\nINVIO AL CHECKSUM\n",mess.stringa);
					ret = msgsnd(filter_to_checksum,&mess,sizeof(Message) - sizeof(long),0); 
					if(ret<0) {perror("Error msgsnd"); exit(-1);}
				}
        }
    
        exit(0);
}

