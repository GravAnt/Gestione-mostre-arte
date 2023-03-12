#ifndef CRITT_H_INCLUDED
#define CRITT_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
*Funzione di crypting della password
*@paramin[in]char:password scelta dall'utente
*/
void critt(char []);
/**
*Funzione di decrypting della password
*@paramin[in]char:password scelta dall'utente
*/
void decritt(char []);


//cifrario di Cesare
void critt(char password[])
{
    for(int i = 0; i < strlen(password); i++)
    {
        password[i]++;
    }
}


void decritt(char password[])
{
    for(int i = 0; i < strlen(password); i++)
    {
        password[i]--;
    }
}

#endif // CRITT_H_INCLUDED
