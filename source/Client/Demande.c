

#include "header/Demande.h"

#define TAILLEBUF 40

void Demande(int sock){

    char *message;
    char reponse[TAILLEBUF];
    int nb_octets;
   
    //envoie l'info au serveur qu'on demande la liste
    message = "Demande"; 
    nb_octets = write(sock, message, strlen(message)+1);

    //recupere le nombre d'items pour la liste
    nb_octets = read(sock, reponse, TAILLEBUF);
    nb_octets = write(sock, message, strlen(message)+1);
    
    int nb_biere = atoi(reponse);

    //affichage de la liste des boissons
    system("clear");

    printf("  ---------------------------------------------------------\n");
    printf("|            Voici nos miaou-bieres disponibles nya~       |\n");
    printf("  ------------------------------------------------------  -\n");
    printf("                                                         \\ |\n");
    printf("                                                          \\|\n");
     for(int i = 0; i < nb_biere; i++){  //boucle recuperant le nom de chaque boisson pour l'afficher 
        
        nb_octets = read(sock, reponse, TAILLEBUF);
        nb_octets = write(sock, message, strlen(message)+1);
        if(i == 0){
            printf("   BLONDE - %s | ", reponse);
        }else{
            printf("AMBREE - %s         miaou\n", reponse);
        }
        
    }
    
            printf("                                                       |\\---/|\n");
            printf("                                                       | ,_, |\n");
            printf("                                        i    i_         \\_`_/-..----.\n");
            printf("                                        |    |_)      ___/ `   ' ,""+ \\\n");
            printf("                                        |    |       (__...'   __\\    |`.___.';\n");
            printf("                                        `-==-'         (_,...'(_,.`__)/'.....+\n");
       
    
}