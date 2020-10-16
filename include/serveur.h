#ifndef __SERVEUR_h__
#define __SERVEUR_h__

#include "Reseau.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h> 
#include <sys/stat.h>

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

int S_reponseHTTP(int socketClient, char* requete);

char* S_typeFichier(char* cheminFichier);

#endif