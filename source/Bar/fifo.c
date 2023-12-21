
#include "header/fifo.h"




//ordonnance les processus dans l'ordre d'arrivée
void fifo(int id, int semid, int* prio){

    custom_wait(semid,0);

    if(getpid() < *prio){
        *prio = getpid();
    }

    custom_post(semid,0);
    sleep(1);
    
    if(getpid() == *prio){
              
        *prio = 9999999;  
    }
    else{
        while(*prio != 9999999){} 
        fifo(id, semid, prio);
    }
}