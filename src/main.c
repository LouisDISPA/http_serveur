#include "serveur.h"

int main(int argc,char **argv) {
    char* adresseServeur = "127.0.0.1";
    char* portServeur = "8080";
    char* dossierPublic = "www";
    int socketid;
    FILE* configFile = fopen("etc/serveurHTTP.conf", "r");

    if (configFile != NULL) {
        adresseServeur = malloc(20);
        portServeur = malloc(10);
        dossierPublic = malloc(100);
        fscanf(configFile, "%s %s %s", adresseServeur, portServeur, dossierPublic);
        fclose(configFile);
    }
    else {
        if ( argc >= 2 )
            adresseServeur = argv[1];
        if ( argc >= 3 )
            dossierPublic = argv[2];
        if ( argc >= 4 )
            portServeur = argv[3];
    }

    printf("Initialise Serveur: %s:%s\n", adresseServeur, portServeur);
    socketid = S_initialise(adresseServeur, portServeur, dossierPublic);

    if (socketid != -1) {
        printf("Serveur en ecoute\n");
        return S_ecouter(socketid);
    }

    free(adresseServeur);
    free(portServeur);
    free(dossierPublic);

    return 1;
}