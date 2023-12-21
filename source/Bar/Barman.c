
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <stdbool.h>

struct tireuse{ //definition de la structure necessaire pour le fonctionnement de la tireuse
    char nom_biere[20];
    float quantite;
    int degre;
};

//definition constante globales
#define TAILLEBUF 40
#define BLONDE 0
#define AMBREE 1

#include "sem.c"
#include "Communication.c"
#include "controle.c"
#include "barinfo.c"
#include "barcommande.c"


int main(int argc, char* argv[]){
    system("clear");
    unlink("/tmp/transition");
    
    if (argc != 2){
        perror("mauvais nombre d'arguments reessayez avec 2 arguments comme suit :\nbarman.out [numero de port]");
        exit(-1);
    }
    if(mkfifo("/tmp/transition", 0666) == -1){ //creation du pipe permettant de recuperer les id de processus
        perror("echec creation pipe");
        exit(1);
    }

///////////////////////////////////////////
///////////ZONE D'INITIALISATION/////////
///////////////////////////////////////////

    int fdw; ////bout tuyau d'ecriture
    int fdr; //bout tuyau de lecture
    
    char buffer[TAILLEBUF]; //tableau pour passer les messages
    char nom_pipe[TAILLEBUF]; //nom du tuyau associé au processus
    char id[TAILLEBUF]; //contient le nom de la biere choisie


    ///////initialisation d'une memoire partagée pour pouvoir donner la main aux 3 processus principaux
    int shm_ver;
    int *verproc = malloc(sizeof(int));
    shm_ver = shmget(IPC_PRIVATE, sizeof(int), 0666);
    if(shm_ver == -1){
        perror("echec creation main");
        exit(1);
    }
    verproc = shmat(shm_ver, NULL, 0);
    if(verproc == (void*)-1){
        perror("echec shmat main");
        exit(1);
    }
    *verproc = 5;

    //initialisation d'une memoire partagée pour eviter de lancer le processus de controle a l'infini
    int shm_controle;
    int *encontrole = malloc(sizeof(int));
    shm_controle = shmget(IPC_PRIVATE, sizeof(int), 0666);
    if(shm_controle == -1){
        perror("echec creation main");
        exit(1);
    }
    encontrole = shmat(shm_controle, NULL, 0);
    if(encontrole == (void*)-1){
        perror("echec shmat main");
        exit(1);
    }
    *encontrole = 0;
 
    ////initialisation de memoire partagée pour les futs de bieres
    int shm_tireuse;
    struct tireuse* tireuse;
    

    shm_tireuse = shmget(IPC_PRIVATE, (sizeof(struct tireuse) * 2), IPC_CREAT | IPC_EXCL | 0666);
    if(shm_tireuse == -1){
        perror("echec creation espace partagé tireuses");
        exit(1);
    }

    tireuse = shmat(shm_tireuse, NULL, 0);
    if(tireuse == (void*)-1){
        perror("echec lien tireuse a l'espace partag");
        exit(1);
    }


    tireuse[BLONDE].quantite = 5;
    tireuse[AMBREE].quantite = 5;
    tireuse[BLONDE].degre = 86;
    tireuse[AMBREE].degre = 98;
 

    strcpy(tireuse[AMBREE].nom_biere, "Miaou malté");
        
    strcpy(tireuse[BLONDE].nom_biere, "Wendili-Nya");
    
    ///initialisation des semaphores pour l'acces aux tireuses
    int semid;

    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | 0666);
    if(semid == -1){
        perror("echec creation semaphores");
        exit(1);
    }

    if(semctl(semid, 0, SETVAL, 1) == -1){
        perror("echec init semaphore Blonde");
        exit(1);
    }
    if(semctl(semid, 1, SETVAL, 1) == -1){
        perror("echec init semaphore AMBREE");
        exit(1);
    }
    ////initialisation d'une memoire partagée pour ordonnancer les processus
    int shm_prio;
    int* prio = malloc(sizeof(int));
    
    shm_prio = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    if(shm_prio == -1){
        perror("echec creation espace partagé verif ordo");
        exit(1);
    }

    prio = shmat(shm_prio, NULL, 0);
    if(prio == (void*)-1){
        perror("echec shmat");
        exit(1);
    }
    *prio = 9999999;    
   
   switch(fork()){ //crée un processus pour s'occuper de la communication
        case 0 : comm(argc,argv,verproc); exit(0);
        break;
        case -1 : perror("echec fork comm"); exit(1);
        break;
    }

    switch(fork()){ //crée un processus qui s'occupe de donner la main entre les 3 processus principaux
        case 0 : 
        while(true){
            *verproc = 1;
            sleep(1); 
            *verproc = 2;
            sleep(1);
            controle(tireuse, encontrole, atoi(argv[1]));
            sleep(1);}
        break;
        case -1 : perror("echec fork donneurmain"); exit(1);
        break;
    }
    
    int papa = getpid(); //sauvegarde de l'id du processus pere
    
    while(getpid() == papa){ //le processus pere boucle mais ses fils sortent
        
        fdr = open ("/tmp/transition", O_RDONLY|O_SYNC); 
        if(fdr == -1){
            perror("echec ouverture transition en lecture");
            exit(1);
        } 
        read(fdr, buffer, sizeof(buffer));  ///crée un processus fils pour chaque entrée reçue dans le pipe "transition" 
        close(fdr);
        if(fork() == -1){
            perror("echec fork");
            exit(1);
        }
    }

   
    
 



    
    
    
    strcpy(nom_pipe,buffer);///sauvegarde le pid du processus venu chercher des infos sur la biere pour communiquer au pipe correspondant
    
     fdw = open (nom_pipe, O_WRONLY|O_SYNC); //synchronisation
        if(fdw == -1){
            perror("echec ouverture pipe en ecriture");
            exit(1);
        }
        write(fdw, "sync", 1);
        close(fdw);
    
    
    fdr = open (nom_pipe, O_RDONLY|O_SYNC);
    if(fdr == -1){
        perror("echec ouverture pipe en lecture");
        exit(1);
    }
    read(fdr, buffer, sizeof(buffer));
    close(fdr);
   //REPERE RESTAURATIN
    
   
    if(strcmp(buffer,"info") == 0){ //Zone pour envoyer les infos des futs
        
        barinfo(nom_pipe, tireuse, buffer);

    }
    else{ //Zone pour gerer une commande de biere
        if(strcmp(buffer,"commande") == 0){
        
            
            
        while(*verproc != 1){} ///boucle bloquante tant que la main n'a pas été donnée au processus de barman
    
        barcommande(id, nom_pipe, buffer, semid, prio, encontrole, tireuse);
        
    }
    }
    unlink(nom_pipe);
}