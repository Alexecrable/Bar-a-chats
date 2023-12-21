    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <netdb.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <errno.h>

      #include "header/remplirfut.h"

 
   

    void remplirfut(struct tireuse *tireuse, int port, int couleur){  
         
            char *msg = "bonjour";

            printf("MANQUE CRUCIAL DE %s (%f)\n",tireuse[couleur].nom_biere, tireuse[couleur].quantite);

            printf("voici les bieres disponibles :\n");

            switch(fork()){
                case 0 : 
                if (couleur == BLONDE){
                    system("java -cp source/Bar Commande BLONDE"); 
                }
                else{
                    system("java -cp source/Bar Commande AMBREE"); 
                }
                exit(0);
                break;
            }

            sleep(1);

            char hostname[20];
            
            gethostname(hostname,20);

            struct hostent *serveur_host;
            // adresse de la socket coté serveur
            static struct sockaddr_in addr_serveur;
            // taille de l'addresse socket
            socklen_t lg;
            // descripteur de la socket locale
            int sock;
            // chaine à envoyer
            
            
            // buffer de réception
            char buffer[TAILLEBUF];
            // chaine reçue en réponse
            char *reponse;
            // nombre d'octets lus ou envoyés
            int nb_octets;

            // création d'une socket UDP
            sock = socket(AF_INET, SOCK_DGRAM, 0);
            int enable = 1;
            if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
                perror("setsockopt(SO_REUSEADDR) failed");
            }
            
            // récupération identifiant du serveur
            serveur_host = gethostbyname(hostname);
            
            // création adresse socket destinatrice
            bzero(&addr_serveur, sizeof(struct sockaddr_in));
            addr_serveur.sin_family = AF_INET;
            addr_serveur.sin_port = htons(7777);
            memcpy(&addr_serveur.sin_addr.s_addr, serveur_host -> h_addr, serveur_host -> h_length);

           
           int achat;
           int c;
           do{  ///demande le choix de biere a acheter
            printf("Quelle biere voulez vous commander ? (choisir 1 numero)\n: ");
            scanf("%d",&achat);
            while ((c = getchar()) != '\n') { }
        }while(achat < 1 || achat > 3);

            msg = malloc(sizeof(int));
            sprintf(msg,"%d",achat);
            
            

            lg = sizeof(struct sockaddr_in);
            nb_octets = sendto(sock, msg, strlen(msg), 0,(struct sockaddr*)&addr_serveur, lg); //envoie le choix d'achat
            

           
            nb_octets = recvfrom(sock, buffer, TAILLEBUF, 0,(struct sockaddr*)&addr_serveur, &lg); //recuperation du nom de la biere
            reponse = (char *)malloc(nb_octets * sizeof(char));
            memcpy(reponse, buffer, nb_octets);
            
           
           

            strcpy(tireuse[couleur].nom_biere,reponse);
            
           

            lg = sizeof(struct sockaddr_in); 
            nb_octets = sendto(sock, msg, strlen(msg), 0,(struct sockaddr*)&addr_serveur, lg); //synchronisation
               
            nb_octets = recvfrom(sock, buffer, TAILLEBUF, 0,(struct sockaddr*)&addr_serveur, &lg); //recuperation du degré
        
        
            reponse = (char *)malloc(nb_octets + 1); // ajouter un octet pour le caractère nul
            memset(reponse, '\0', nb_octets + 1);
            memcpy(reponse, buffer, nb_octets);
           

            int degre = atoi(reponse);
         
            tireuse[couleur].quantite = 5;
            tireuse[couleur].degre = degre;

            // on ferme la socket
            sleep(1);
            close(sock);
            
        
        
    
    }

