#include "header/Quitter.h"


void Quitter(int sock){

    char *message;
    char reponse[TAILLEBUF];
    int nb_octets;
    message = "quitter"; 
    nb_octets = write(sock, message, strlen(message)+1); //envoie au serveur l'info que l'on part :'(
    system("clear");
            printf("  ---------------------------------------------------------\n");
            printf("|                   Miaourevoir...... :'(                  |\n");
            printf("  ------------------------------------------------------  -\n");
            printf("                                                         \\ |\n");
            printf("                                                          \\|\n");
            printf("                                                        miaou    \n");
            printf("                                                       |\\---/|\n");
            printf("                                                       | ,_, |\n");
            printf("                                        i    i_         \\█ █/-..----.\n");
            printf("                                        |    |_)      ___█ █   ' ,""+ \\\n");
            printf("                                        |    |       (__.█.█   __\\    |`.___.';\n");
            printf("                                        `-==-'         (_█.█.'(_,.`__)/'.....+\n");

         
      
    exit(0);
        
}