#include "serveur.h"
#include <stdio.h>
#include <time.h>
#include<sys/wait.h> 
#include<sys/types.h> 

#define LONGUEUR_ATTENTE 128
#define TAILLE_BUFFER 63000

char* dossier;


int S_initialise(char* adresseServeur, char* portServeur, char* dossierStatic) {
    int socketServeur;
    struct sockaddr_in addresseSocket;

    signal(SIGCHLD,SIG_IGN); // pour eviter les enfants zombies
    addresseSocket = construireAdresseTCPUDPDepuisChaine(adresseServeur, portServeur);
    socketServeur = creerSocketTCPServeur(addresseSocket);
    dossier = dossierStatic;

    return socketServeur;
}


int S_ecouter(int socketServeur) {
    unsigned int longueurAdresseClient;
    struct sockaddr_in adresseClient;
    int socketClient;
    int erreur=0;

    erreur = listen(socketServeur, LONGUEUR_ATTENTE);

    while (erreur!=-1) {

        longueurAdresseClient = sizeof adresseClient;
        socketClient = accept(socketServeur, (struct sockaddr *) &adresseClient, &longueurAdresseClient);
        erreur = S_traiterClient(socketClient);
    }
    return erreur;
}

int S_traiterClient(int socketClient) {
    pid_t PID;
    printf("connection : %li\n",socketClient);

    if (socketClient == -1)
        return -1;
        
    PID = fork();

    if (PID == -1)
        return -1;

    if (PID==0) {
        S_traiterRequete(socketClient);
        printf("deconnection : %i\n",socketClient);
        close(socketClient);
        _Exit(0);
    } 
    else {
        close(socketClient);
        return 1;
    }
    
}

int S_traiterRequete(int socketClient){
    char requete[TAILLE_BUFFER], *reponse;
    int nbCaracter;

    // do {
        nbCaracter = read(socketClient, requete, TAILLE_BUFFER-1);
        if (nbCaracter == -1) return -1;
        reponse = S_reponseHTTP(requete, nbCaracter);
        write(socketClient, reponse, strlen(reponse));

    // } while (nbCaracter != 0);

    return 0;
}

char* S_reponseHTTP(char* requete, int nbCaractere) {
    return "http/1.0 200 OK\r\n\r\nhello world\n";
}