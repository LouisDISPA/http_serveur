#ifndef __SERVEUR_h__
#define __SERVEUR_h__

#include "Reseau.h"

//TODO: documentation

/**
 * @brief 
 * 
 * @param adresseServeur 
 * @param portServeur 
 * @return int 
 */
int S_initialise(char* adresseServeur, char* portServeur, char* dossierStatic);

/**
 * @brief 
 * 
 * @param socketServeur 
 * @param longueurFileDAttente 
 * @return int 
 */
int S_ecouter(int socketServeur);

int S_traiterClient(int socketClient);

int S_traiterRequete(int socketClient);

char* S_reponseHTTP(char* requete, int nbCaractere);

#endif