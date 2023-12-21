
#include "header/sem.h"

// P(S)
void custom_wait(int semid, int sem_num) { 

    struct sembuf buf;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    buf.sem_num=sem_num;
    semop(semid, &buf, 1);
    
}

// V(S)
void custom_post(int semid, int sem_num){

    struct sembuf buf;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    buf.sem_num=sem_num;
    semop(semid, &buf, 1);
    
}