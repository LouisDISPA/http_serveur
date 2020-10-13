#include "serveur.h"
#include <stdio.h>

int main(int argc,char **argv) {
    char* adresseServeur = "127.0.0.1";
    char* portServeur = "8080";
    int socketid;

    if ( argc >= 2 )
        adresseServeur = argv[1];

    if ( argc >= 3 )
        portServeur = argv[2];

    printf("Initialise Serveur sur => %s:%s\n", adresseServeur, portServeur);
    socketid = S_initialise(adresseServeur, portServeur, "dossier");

    if (socketid != -1) {
        printf("Serveur en ecoute\n");
        return S_ecouter(socketid);
    }

    return 1;
}