#include <unistd.h>
#include <netdb.h>
#include <sys/stat.h>

#include "tcpcreersocket.c"
#include "header/Communication.h"



void comm(int argc, char *argv[],int *verproc){

    
    int socket_service;  
    char message[TAILLEBUF]; // buffer qui contiendra le message reçu
    char *reponse; // chaîne renvoyée au client
    char nb_octets; // nombre d'octets reçus ou envoyés 
    static struct sockaddr_in addr_client; // adresse socket coté client
    int lg_addr; // longueur adresse
    
    creerSocketTCP(atoi(argv[1]));

    // connexion etablie, on envoie le message
    if (listen(socket_ecoute, 5) == -1) {
        perror("erreur listen");
        exit(1);
    }
    // on attend la connexion du client
    int papa = getpid();
    lg_addr = sizeof(struct sockaddr_in);
    
    int fdw; //bout du tuyau en ecriture
    int fdr; //bout du tuyau en lecture
    char buffer[TAILLEBUF]; //tableau contenant les messages passés dans les pipes
    
    
    while(getpid() == papa){ //crée un nouveau processus a chaque nouvelle connection d'un client
        
        socket_service = accept(socket_ecoute, (struct sockaddr *)&addr_client, &lg_addr);
        if (socket_service == -1) {
            perror("erreur listen");
            exit(1);
        }
        if(fork() == -1){
            perror("echec fork");
            exit(1);
        }

    }    

    char nom_pipe[20]; //chaine accueillant le nom du pipe pour avoir un pipe dédié par client afin d'eviter des confusions de données entre le barman et la comm
    sprintf(nom_pipe,"/tmp/%d", getpid());
    if (mkfifo(nom_pipe, 0666) == -1){
        perror("erreur creation pipe");
        exit(1);
    } 

    if(strcmp(message,"quitter") == 0){
            
            unlink(nom_pipe);
            exit(0);
        }
        
    while(*verproc != -1){
    
        while(*verproc != 2){};

        if(read(socket_service, message, TAILLEBUF) == -1){
            perror("erreur lecture socket");
            exit(1);
        }
    
        
        if (strcmp(message, "Demande") == 0) {
            
              
            fdw = open ("/tmp/transition", O_WRONLY|O_SYNC); //envoie le nom du pipe au barman pour comm
            if(fdw == -1){
                perror("erreur d'ouverture du tube en ecriture");
                exit(1);
            }

            write(fdw, nom_pipe, strlen(nom_pipe)+1);
            close(fdw);
            
            fdr = open (nom_pipe, O_RDONLY|O_SYNC); //synchronisation
            if(fdr == -1){
                perror("erreur d'ouverture du tube en lecture");
                exit(1);
            }
            read(fdr, buffer, sizeof(buffer));
            close(fdr);
           
            fdw = open (nom_pipe, O_WRONLY|O_SYNC); //envoie l'info qu'on veut des infos lol
            if(fdw == -1){
                perror("erreur d'ouverture du tube en ecriture");
                exit(1);
            }
            write(fdw, "info", 5);
            close(fdw);

            

            
            fdr = open (nom_pipe, O_RDONLY|O_SYNC); //recupere le nombre de futs 
            if(fdr == -1){
                perror("erreur d'ouverture du tube en lecture");
                exit(1);
            }
            read(fdr, buffer, sizeof(buffer));
            close(fdr);
            
            
            reponse = malloc(sizeof(int));
            int nb = atoi(buffer);
            if (sprintf(reponse,"%d",nb) == -1){
                perror("erreur sprintf");
                exit(0);
            }
            
           

            if(write(socket_service, reponse, strlen(reponse)+1) == -1){
                perror("echec ecriture socket");
                exit(1);
            }
            
            if (read(socket_service, message, TAILLEBUF) == -1){
                perror("echec lecture socket");
                exit(1);
            }
            
            for(int i = 0; i < nb; i++){ 
               
            fdw = open (nom_pipe, O_WRONLY|O_SYNC); //synchronisation
            if(fdw == -1){
                perror("erreur d'ouverture du tube en ecriture");
                exit(1);
            }
            write(fdw, "sync", 5);
            close(fdw);

               

                fdr = open (nom_pipe, O_RDONLY|O_SYNC); //recupere les infos sur les bieres
                
                if (fdr == -1){
                    perror("erreur lecture socket");
                    exit(1);
                }
                
                read(fdr, buffer, sizeof(buffer));
                close(fdr);

                if (sprintf(reponse,"%s",buffer) == -1){
                    perror("erreur sprintf");
                    exit(1);
                }
                
                if(write(socket_service, reponse, strlen(reponse)+1) == -1){
                    perror("echec ecriture socket");
                    exit(1);
                }
                if(read(socket_service, message, TAILLEBUF) == -1){
                    perror("echec lecture socket");
                    exit(1);
                }


            }
           

        }
        else{
            if (strcmp(message, "Commande") == 0){
                
                
                if(read(socket_service, message, TAILLEBUF) == -1){
                    perror("echec lecture socket");
                    exit(1);
                }

                char id[10];
                strcpy(id,message);
                    
                if(write(socket_service, message, strlen(message)+1) == -1){
                    perror("echec ecriture socket");
                    exit(1);
                }

                if(read(socket_service, message, TAILLEBUF) == -1){
                    perror("echec lecture socket");
                    exit(1);
                }
                
                if(write(socket_service, message, strlen(message)+1) == -1){
                    perror("echec ecriture socket");
                    exit(1);
                }



               

                
              
                fdw = open ("/tmp/transition", O_WRONLY|O_SYNC); //envoie le nom du pipe pr communiquer
                if (fdw == -1){
                    perror("echec ouverture transition");
                    exit(1);
                }
                write(fdw, nom_pipe, strlen(nom_pipe)+1);
                close(fdw);

                fdr = open (nom_pipe, O_RDONLY|O_SYNC); // synchronisation
                
                if (fdr == -1){
                    perror("erreur lecture socket");
                    exit(1);
                }
                
                read(fdr, buffer, sizeof(buffer));
                close(fdr);
                

                fdw = open (nom_pipe, O_WRONLY|O_SYNC);// envoie l'info qu'on commande
                if (fdw == -1){
                    perror("echec ouverture pipe en lecture");
                    exit(1);
                }
                write(fdw, "commande", 9);
                close(fdw);

                fdr = open (nom_pipe, O_RDONLY|O_SYNC); //synchroinsation
                
                if (fdr == -1){
                    perror("erreur lecture socket");
                    exit(1);
                }
                
                read(fdr, buffer, sizeof(buffer));
                close(fdr);

                
                

                


                
                ///////////////// [Envoie l'id de la biere qu'on commande]
                
                
                fdw = open (nom_pipe, O_WRONLY|O_SYNC);
                if (fdw == -1){
                    perror("echec ouverture pipe en lecture");
                    exit(1);
                }
                write(fdw, id , strlen(id)+1);
                close(fdw);
              
               

                fdr = open (nom_pipe, O_RDONLY|O_SYNC); //synchroinsation
                
                if (fdr == -1){
                    perror("erreur lecture socket");
                    exit(1);
                }
                
                read(fdr, buffer, sizeof(buffer));
                close(fdr);
                
                ///////////////// [Envoie la taille de la biere qu'on commande]
                fdw = open (nom_pipe, O_WRONLY|O_SYNC);
                if (fdw == -1){
                    perror("echec ouverture pipe en lecture");
                    exit(1);
                }
                write(fdw, message , strlen(message)+1);
                close(fdw);
               
                //////////////// [Recupere les infos sur cette biere]
                fdr = open (nom_pipe, O_RDONLY|O_SYNC);
                if (fdr == -1){
                    perror("echec ouverture pipe en ecriture");
                    exit(1);
                }
                read(fdr, buffer, sizeof(buffer));
                close(fdr);

                
                //ZONE PIPE//
                 
               
                
                
                 if(write(socket_service, buffer, strlen(buffer)+1) == -1){
                        perror("echec ecriture socket");
                        exit(1);
                    }
                              
            }
        }

    }
    // on ferme les sockets
    
    
    close(socket_service);
    close(socket_ecoute);
    exit(0);

   
}