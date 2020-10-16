#include "serveur.h"

#define LONGUEUR_ATTENTE 128
#define TAILLE_BUFFER 63000
#define MAX_HEADER 300
#define STATUSHTTP(x, y) "http/1.0 x y"

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

    if (socketClient == -1)
        return -1;
        
    PID = fork();

    if (PID == -1)
        return -1;

    if (PID==0) {
        S_traiterRequete(socketClient);
        close(socketClient);
        _Exit(0);
    } 
    else {
        close(socketClient);
        return 1;
    }
    
}

int S_traiterRequete(int socketClient){
    char requete[TAILLE_BUFFER];
    int nbCaracter;

    nbCaracter = recv(socketClient, requete, TAILLE_BUFFER-1, 0);

    if (nbCaracter == -1) return -1;

    return S_reponseHTTP(socketClient, requete);
}

int S_reponseHTTP(int socketClient, char* requete) {
    char *methode, *uri, *param, cheminFichier[MAX_HEADER], response[MAX_HEADER], *buff, *typeFichier;
    FILE* fptr;
    int longueurFichier;
    
    //  printf("\n\n%s\n\n", requete);

    methode = strtok(requete, " \t\r\n");
    uri = strtok(NULL, " \t\r\n");
    // version = strtok(NULL, " \t\r\n");
    // header = strtok(NULL, "");

    param = strchr(uri, '?');
    if (param != NULL)
    {
        param[0] = '\0';
        param++;
    } else {
        param = "";
    }


    printf("\x1b[32m  [%s] %s %s \x1b[0m\n", methode, uri, param);
    
    strcat(cheminFichier, dossier);
    if (strlen(uri) == 1)
        strcat(cheminFichier, "/index.html");
    else
        strcat(cheminFichier, uri);
    

    fptr = fopen(cheminFichier, "rb");

    fseek(fptr, 0, SEEK_END);
    longueurFichier = ftell(fptr);
    rewind(fptr);

    if ((fptr == NULL) || (longueurFichier < 0)) {
        sprintf(response, "http/1.0 404 Not Found\r\n\r\nFichier non trouve\n");
        send(socketClient, response, strlen(response), 0);
        return -1;
    }

    typeFichier = S_typeFichier(cheminFichier);

    sprintf(response, "http/1.0 200 OK\r\nContent-Type: %s\r\nContent-Length: %i\r\n\r\n", typeFichier, longueurFichier);
    send(socketClient, response, strlen(response), 0);


    buff = malloc(longueurFichier);
    fread(buff, longueurFichier, 1, fptr);
    send(socketClient, buff, longueurFichier, 0);

    fclose(fptr);
    free(buff);

    return 0;
}

char* S_typeFichier(char* cheminFichier) {
    char* extension = strrchr(cheminFichier, '.');
    if (strcmp(extension, ".html")==0)
		return "text/html; charset=UTF-8;";
	else if ((strcmp(extension, ".jpg")==0) || (strcmp(extension, ".jpeg")==0))
		return "image/jpeg";
	else if (strcmp(extension, ".png")==0)
		return "image/png";
    else if (strcmp(extension, ".svg")==0)
		return "image/svg";
    else if (strcmp(extension, ".mp3")==0)
		return "audio/mp3";
    else if (strcmp(extension, ".ttf")==0)
		return "font/ttf";
    else if (strcmp(extension, ".js")==0)
		return "application/javascript";
    else if (strcmp(extension, ".css")==0)
		return "text/css; charset=UTF-8";
	else
		return "text/plain; charset=UTF-8";
}