#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "header.h"

int main(){

        pid_t pid;

        int key_genTOfilter = ftok ("./",'msg');
        int key_filterTOchecksum = ftok ("./",'msg');	
        int key_checksumTOvisual = ftok ("./",'msg');

        int gen_to_filter = msgget(gen_to_filter, IPC_CREAT | 0664);
        if(gen_to_filter<0) { perror("MailBox Gen ERROR"); exit(1); }
        int filter_to_checksum = msgget(gen_to_filter, IPC_CREAT | 0664);
        if(filter_to_checksum<0) { perror("MailBox Filter ERROR"); exit(1); }
        int ds_checksum_to_visual = msgget(gen_to_filter, IPC_CREAT | 0664);
        if(ds_checksum_to_visual<0) { perror("MailBox Checksum ERROR"); exit(1); }
        
        /* creazione shm per prod-cons generatori */
    
        key_t shm_key = /* TODO: definire chiave shared memory per prod/cons generatori*/

        int ds_shm = /* TODO: generare il descrittore della shared memory per prod/cons generatori*/

        if(ds_shm<0) { perror("SHM errore"); exit(1); }

        /* TODO: ottenere il riferimento per il segmento di shm */

        /* TODO: inizializzare variabili utilizzate per la sincronizzazione generatori */
        
    
        int i;

        for (i=0; i<NUM_GENERATORS; i++){
        
                pid = fork();

                if (pid == 0){
                
                    if (i % 2 == 0){
                        
                        printf("GENERATORE PROD PID: %d\n", getpid());
                        int j;
                        for (j=0; j<4; j++){
                            srand(time(NULL)*getpid()+j);
                            generatore_produttore(pc);
                        }
                        exit(0);
                    }
                    else {
                        printf("GENERATORE CONS PID: %d\n", getpid());
                        int j;
                        for (j=0; j<4; j++){
                            generatore_consumatore(pc, gen_to_filter);
                        }
                        exit(0);
                    }
                }        
        }        


        for (i=0; i<NUM_FILTER+NUM_CHECKSUM+NUM_VISUAL; i++){
                pid = fork();
                if (pid==0){
                        if (i==0){
                            printf("FILTRO PID: %d\n", getpid());
                            filtro(gen_to_filter, filter_to_checksum);
                        }
                        else if (i==1){
                            printf("CHECKSUM PID: %d\n", getpid());
                            checksum(filter_to_checksum, ds_checksum_to_visual);
                        }
                        else if (i==2){
                            printf("VISUALIZZATORE PID: %d\n", getpid());
                            visualizzatore(ds_checksum_to_visual);
                        }
                }
        }

       
        for (i=0; i<total_process; i++){
                wait(NULL);
        }

        /* TODO: deallocare risorse (code, shm, monitor) */
        
        printf("[master] Rimozione code OK!\n");
        printf("[master] Rimozione monitor OK!\n");
    
        return 0;
}
