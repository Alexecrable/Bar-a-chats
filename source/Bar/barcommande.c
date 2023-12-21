#include "header/barcommande.h"
#include "biereverif.c"
#include "fifo.c"

void barcommande(char* id, char* nom_pipe, char* buffer, int semid, int *prio, int* encontrole, struct tireuse *tireuse){
    int biere_test = 0; //variable verifiant la condition des bieres
    int fdw, fdr;
    fdw = open (nom_pipe, O_WRONLY|O_SYNC); //synchronisation
        if(fdw == -1){
            perror("echec ouverture pipe en ecriture");
            exit(1);
        }
        write(fdw, "sync", 1);
        close(fdw);

        //ZONE PIPE// [recupe l'id de la biere choisie]
        fdr = open (nom_pipe, O_RDONLY|O_SYNC);
        if(fdr == -1){
            perror("echec ouverture pipe en lecture");
            exit(1);
        }
        read(fdr, buffer, sizeof(buffer));
        close(fdr);
        //ZONE PIPE//
        

        strcpy(id,buffer);

        fdw = open (nom_pipe, O_WRONLY|O_SYNC); //synchronisation
        if(fdw == -1){
            perror("echec ouverture pipe en ecriture");
            exit(1);
        }
        write(fdw, "sync", 1);
        close(fdw);
        
        
        //ZONE PIPE// [recupe la taille de la biere choisie]
        fdr = open (nom_pipe, O_RDONLY|O_SYNC);
        if(fdr == -1){
            perror("echec ouverture pipe en lecture");
            exit(1);
        }
        read(fdr, buffer, sizeof(buffer));
        close(fdr);
        //ZONE PIPE//

       
        
        fifo(getpid(),semid,prio); ///ordonnance les processus arrivant pour les servir dans l'ordre d'arrivée
        biere_test = biereverif(id,buffer,tireuse,semid,encontrole);  ///verifie que la biere commandée existe, et en quantité suffisante

      
        
        if(sprintf(buffer,"%d",biere_test) == -1){
            perror("echec sprintf bieretest");
            exit(1);
        }
        
    
        //ZONE PIPE// [envoie les infos sur la biere commandée]
        fdw = open (nom_pipe, O_WRONLY|O_SYNC);
        if(fdw == -1){
            perror("echec ouverture pipe en ecriture");
            exit(1);
        }
        write(fdw, buffer, strlen(buffer)+1);
        close(fdw);
        //ZONE PIPE//
    
        exit(0);
}