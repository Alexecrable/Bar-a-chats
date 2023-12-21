    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <netdb.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <errno.h>

    #include "remplirfut.c"
    #include "header/controle.h"



    ///verifie que les bieres sont en quantitées suffisantes (faudra rajouter les sockets udp pour envoyer la demande de commande au fournisseur)

    void controle(struct tireuse *tireuse, int *encontrole, int port){  
        
        
        if((tireuse[BLONDE].quantite < 0.5 || tireuse[AMBREE].quantite < 0.5) && *encontrole == 0){
            *encontrole = 1; //permet d'empecher le controle de se lancer a repetition tout en permettant de continuer de faire tourner la communication du bar afin de ne pas faire attendre un client inutilement
            sleep(1);
            switch(fork()){
                case 0 : return;
                break;
                
            }
            
            if(tireuse[BLONDE].quantite < 0.5){
                
                remplirfut(tireuse, port, BLONDE);

            }
            if(tireuse[AMBREE].quantite < 0.5){

                remplirfut(tireuse, port, AMBREE);

            }
            
            
            
            *encontrole = 0;
            
            
        }
        
        return;
    }
