#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define TAILLEBUF 40
#include "Demande.c"
#include "Commande.c"
#include "Quitter.c"



int main(int argc, char *argv[]){

    if (argc != 3){ //verifie que le processus a bien été appelé avec le bon nombre de parametres
        perror("mauvais nombre d'arguments");
        exit(1);
    }

    /////////////////////////////////////////////////
    ///////INITIALISATION ET CREATION SOCKET////////////////
    ///////////////////////////////////////////////////:

    int choix;
    int sock;
    int nb_octets;
    static struct sockaddr_in addr_serveur; 
    struct hostent *serveur_host;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
    perror("creation socket");
    exit(1);
    }
  
    serveur_host = gethostbyname(argv[1]);
    
    if (serveur_host==NULL) {
        perror("erreur récupération adresse serveur\n");
        exit(1);
    }

    bzero((char *) &addr_serveur,sizeof(addr_serveur));
    addr_serveur.sin_family = AF_INET;
    if (argc==1){
        addr_serveur.sin_port = htons(0);
    }
    else{
        
        addr_serveur.sin_port = htons(atoi(argv[2]));
    }
    
    memcpy(&addr_serveur.sin_addr.s_addr, serveur_host-> h_addr, serveur_host->h_length);

    // connexion de la socket client locale à la socket coté serveur
    if (connect(sock, (struct sockaddr *)&addr_serveur, sizeof(struct sockaddr_in)) == -1) {
        perror("erreur connexion serveur");
        exit(1);
    }
    
    system("clear");
            printf("  ---------------------------------------------------------\n");
            printf("| Miaoujour, bienvenue, que miaou-désirez-vous ?           |\n");
            printf("  ------------------------------------------------------  -\n");
            printf("        ____     ____     ___         _\\__               \\ |\n");
            printf("       |    )   |    |   |   |       |    |               \\|\n");
            printf("       |-- <    |----|   |---        |----|            miaou    \n");
            printf("       |____)   |    |   |  \\        |    |            |\\---/|\n");
            printf("   _____             ____   _______                    | ,_, |\n");
            printf("  |        |    |   |    |     |        i    i_         \\_`_/-..----.\n");
            printf("  |        |----|   |----|     |        |    |_)      ___/ `   ' ,""+ \\\n");
            printf("  |_____   |    |   |    |     |        |    |       (__...'   __\\    |`.___.';\n");
            printf("                                        `-==-'         (_,...'(_,.`__)/'.....+\n");

    while(true){


        choix = 0;
        int c;

        
        //
        do{ 
            
            
             ///demande le choix d'action en client tant qu'il ne donne pas une action valide
            printf("choix action (rentrez le numero correspondant):\n\n");
            printf("1 - \"Qu'avez vous comme biere ????\"\n");
            printf("2 - \"Je vais prendre... une... heueueuuuu..... \"\n");
            printf("3 - *Quitter le bar*\n");
            

               

 






            scanf("%d",&choix);
            while ((c = getchar()) != '\n') { }
        }while(choix < 1 || choix > 3);

        switch(choix){
            case 1 : Demande(sock); ///recupere le menu
            break;
            case 2 : Commande(sock); ///commande une biere
            break;
            case 3 : Quitter(sock); ///sortir du bar
            break;
        }
    } 
}



