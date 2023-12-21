#ifndef CREERSOCKETTCP
#define CREERSOCKETTCP
 

int socket_ecoute;
static struct sockaddr_in addr_serveur;
   

int creerSocketTCP(int port);

 
#endif 