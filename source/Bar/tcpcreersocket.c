
#include "./header/tcpcreersocket.h"


int creerSocketTCP(int port){
       
    socket_ecoute = socket(AF_INET, SOCK_STREAM,0);
    if (socket_ecoute == -1) {
        perror("creation socket");
        exit(1);
    }
    // liaison de la socket d'écoute sur le port passé en parametre
    bzero((char *) &addr_serveur,sizeof(addr_serveur));
    addr_serveur.sin_family = AF_INET;
  
    addr_serveur.sin_port = htons(port);
    
    if( bind(socket_ecoute, (struct sockaddr*)&addr_serveur, sizeof(addr_serveur))== -1 ) {
        perror("erreur bind socket écoute");
        exit(1);
    }
    
}