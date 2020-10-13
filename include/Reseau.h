#ifndef __RESEAU_h__
#define __RESEAU_h__

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//TODO: documentation

/**
 * @brief 
 * 
 * @param adresseIP 
 * @param port 
 * @return struct sockaddr_in 
 */
struct sockaddr_in construireAdresseTCPUDPDepuisChaine(char* adresseIP, char* port);

/**
 * @brief 
 * 
 * @param adresse 
 * @return int 
 */
int creerSocketTCPClient(struct sockaddr_in adresse);

/**
 * @brief 
 * 
 * @return int 
 */
int creerSocketUDPClient();


/**
 * @brief 
 * 
 * @param adresse 
 * @return int 
 */
int creerSocketTCPServeur(struct sockaddr_in adresse);

/**
 * @brief 
 * 
 * @param adresse 
 * @return int 
 */
int creerSocketUDPServeur(struct sockaddr_in adresse);


#endif