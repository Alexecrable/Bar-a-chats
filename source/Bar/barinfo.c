
#include "header/barinfo.h" 


void barinfo(char* nom_pipe, struct tireuse *tireuse,char* buffer){
    int fdw,fdr;
    fdw = open (nom_pipe, O_WRONLY|O_SYNC); //envoie le nombre de tireuses
        if(fdw == -1){
            perror("echec ouverture pipe en ecriture");
            exit(1);
        }
        write(fdw, "2", 1);
        close(fdw);

        char infobiere[TAILLEBUF];
        
        for(int i = 0; i < 2; i++){
            
            fdr = open (nom_pipe, O_RDONLY|O_SYNC); // synchronisation
            if(fdr == -1){
                perror("echec ouverture pipe en lecture");
                exit(1);
            }
            read(fdr, buffer, sizeof(buffer));
            close(fdr);
            
            
            fdw = open (nom_pipe, O_WRONLY|O_SYNC); //envoie les infos sur les bieres
            if(fdw == -1){
                perror("echec ouverture pipe en ecriture");
                exit(1);
            }       
            sprintf(infobiere,"%s [%d°]",tireuse[i].nom_biere, tireuse[i].degre);
            write(fdw, infobiere, strlen(infobiere)+1);
            close(fdw);
        }
        exit(0);
}