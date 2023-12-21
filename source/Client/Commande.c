#include <ctype.h>
#include "header/Commande.h"



void Commande(int sock){

    char *message;
    char reponse[TAILLEBUF];
    int nb_octets;

    message = "Commande"; //envoie au serveur l'info qu'on veut commander
    nb_octets = write(sock, message, strlen(message)+1);
    
    
    


    printf("Quelle biere voulez vous commander ? : "); 
    char choix[10];
    //
    int c;
    scanf("%9s",choix);
    fflush(stdin);
    while ((c = getchar()) != '\n') { }

    for(int i = 0; i < strlen(message); i++){
        choix[i] = toupper(choix[i]);
    }

    while(strcmp(choix,"BLONDE") != 0 && strcmp(choix,"AMBREE") != 0){
        printf("HEIN ? (choix possibles : \"BLONDE\" ou \"AMBREE\")\n");
        scanf("%9s",choix);
        fflush(stdin);
        while ((c = getchar()) != '\n') { }
        for(int i = 0; i < strlen(choix); i++){
        choix[i] = toupper(choix[i]);
    }
    }
    
   
    //renvoi au serveur le choix
    message = malloc(sizeof(int));
    strcpy(message,choix);

    
   
    message = malloc(sizeof(int));
    strcpy(message,choix);
    nb_octets = write(sock, message, strlen(message)+1);
    
    nb_octets = read(sock, reponse, TAILLEBUF); //recupere les infos sur le choix
    
    printf("Quelle taille ? : "); 
    scanf("%9s",choix);
    fflush(stdin);
    while ((c = getchar()) != '\n') { }
    
    for(int i = 0; i < strlen(choix); i++){
        choix[i] = toupper(choix[i]);
    }
    //
    while(strcmp(choix,"PINTE") != 0 && strcmp(choix,"DEMI") != 0){
        printf("HEIN ? (choix possibles : \"PINTE\" ou \"DEMI\")\n");
        scanf("%9s",choix);
        fflush(stdin);
        while ((c = getchar()) != '\n') { }
        for(int i = 0; i < strlen(choix); i++){
        choix[i] = toupper(choix[i]);
    }
    }
    //renvoi au serveur le choix
    message = malloc(sizeof(int));
    strcpy(message,choix);
    
    nb_octets = write(sock, message, strlen(message)+1);
    nb_octets = read(sock, reponse, TAILLEBUF);
    nb_octets = read(sock, reponse, TAILLEBUF); //recupere les infos sur le choix

    int recup = atoi(reponse); 
    
      system("clear");
      
    if(recup == 1){ ///la boisson a été servie sans probleme


            printf("  ---------------------------------------------------------\n");
            printf("|                  Miaouci votre biere nya~ ! ^^           |\n");
            printf("  ------------------------------------------------------  -\n");
            printf("                                                         \\ |\n");
            printf("                                                          \\|\n");
            printf("                                                        miaou    \n");
            printf("                                                       |\\---/|\n");
            printf("                                        .~~~~.         | ,_, |\n");
            printf("                                        i====i_         \\_`_/-..----.\n");
            printf("                                        |cccc|_)      ___/ `   ' ,""+ \\\n");
            printf("                                        |cccc|       (__...'   __\\    |`.___.';\n");
            printf("                                        `-==-'         (_,...'(_,.`__)/'.....+\n");







  

    }
    else{ ///il y'a un probleme avec la boisson commandée
    if(recup == 2){

    

        printf("  ---------------------------------------------------------\n");
        printf("| Miaon ne peut pas vous servir... plus de biere... nya~ :'(\n");
        printf("  ------------------------------------------------------  -\n");
        printf("                                                         \\ |\n");
        printf("                                                          \\|\n");
        printf("                                                        miaou    \n");
        printf("                                                       |\\---/|\n");
        printf("                                                       | ,_, |\n");
        printf("                                        i    i_         \\_`_/-..----.\n");
        printf("                                        |    |_)      ___/ `   ' ,""+ \\\n");
        printf("                                        |    |       (__...'   __\\    |`.___.';\n");
        printf("                                        `-==-'         (_,...'(_,.`__)/'.....+\n");
    }
    else {

        printf("  ---------------------------------------^-^---------------\n");
        printf("|         Miaosolée mais le bar ferme ! (owo)              |\n");
        printf("  ------------------------------------------------------  -\n");
        printf("                                                         \\ |\n");
        printf("                                                          \\|\n");
        printf("                                                        miaou    \n");
        printf("                                                       |\\---/|\n");
        printf("                                                       | ,_, |\n");
        printf("                                        i    i_         \\_`_/-..----.\n");
        printf("                                        |    |_)      ___/ `   ' ,""+ \\\n");
        printf("                                        |    |       (__...'   __\\    |`.___.';\n");
        printf("                                        `-==-'         (_,...'(_,.`__)/'.....+\n");

    }
    }

 

}