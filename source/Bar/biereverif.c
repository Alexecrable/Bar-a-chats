
#include "header/biereverif.h"



void anim_biere(int taille,int *encontrole){
    //anim remplir pinte
    int i;
    int j;
    system("clear");

    for (i = 0; i <= taille; i++)
    {   
        if(*encontrole == 1){ //evite de cacher les infos de la commande du fournisseur avec des anims
            usleep(400000);
        }
        else{ //super anim trop cool
            for(j = 20; j > taille; j--){
            if(i < taille){
                printf("           █         \n");
            }
            else{
                printf("                     \n");
            }
            
        }
        
        for (j = taille; j > i; j--)
        {
            printf("   |       █        |\n");
        }
        
        for (j = i; j > 0; j--)
        {
            printf("   |████████████████|\n");
            
        }
            printf("   |----------------|\n");
        
        
        if(i < taille){
            usleep(400000);
            system("clear");
        }

        }
        
        
        
        
    }
    
}

int biereverif(char* id, char* taille, struct tireuse* tireuse, int semid,int *encontrole){
    int i = 2;
    
    if(strcmp(id,"BLONDE") == 0){//commande d'une blonde
        i = BLONDE;
        } 
    else{
        if(strcmp(id,"AMBREE") == 0){//commande d'une AMBREE
            i = AMBREE;
            } 

        
    }

    if(strcmp(taille,"PINTE") == 0){
        
            custom_wait(semid,i);
           
            if((tireuse[i].quantite - 0.5) >= 0){ //verification et service de la pinte
                
                tireuse[i].quantite = tireuse[i].quantite - 0.5;
                anim_biere(10,encontrole);
                custom_post(semid,i);
                return 1;

            }
            else{ //pas assez pour une pinte
           
                custom_post(semid,i);
                return 2;

            }
        }
        else{
            if(strcmp(taille,"DEMI") == 0){
                
                custom_wait(semid,i);
                if((tireuse[i].quantite - 0.25) >= 0){ //verification et service du demi
                    
                    tireuse[i].quantite = tireuse[i].quantite -0.25;
                    anim_biere(5,encontrole);
                    custom_post(semid,i);
                    return 1;
    
                }
                else{ //pas assez pour un demi
                    custom_post(semid,i);
                    return 2;
    
                }

            }
            else{
                custom_post(semid,i);
                printf("client %d parti :'(\n",getpid());
                exit(1);
            }
                

        }
   
}