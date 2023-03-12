#ifndef AVVIO_H_INCLUDED
#define AVVIO_H_INCLUDED
#define max_errori 5 //per il login
#define lung_passw 8
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "admin.h"
#include "critt.h"
#include "prenotazione.h"
#include "ricerca.h"


/**
*Apre il menù all'avvio del programma che consente login o registrazione
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]utene:struct utente
*@paramin[in]int:numero degli utenti dopo aver contato le righe
*/
void avvio(mostra [], opera [], utente [], int);
/**
*Apre il menù che consente all'utente di prenotare, fare una ricerca o di visualizzare/modificare il proprio profilo
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]utene:struct utente
*@paramin[in]char:username dell'utente
*/
void menu(mostra [], opera [], utente [], char []);
/**
*Funzione di login da parte dell'utente
*@paramin[in]utene:struct utente
*@paramin[in]char:username dell'utente
*@paramin[in]int:numero degli utenti dopo aver contato le righe
*/
void accesso(utente [], char [], int);
/**
*Funzione di registrazione da parte dell'utente
*@paramin[in]utene:struct utente
*@paramin[in]char:username dell'utente
*@paramin[in]int:numero degli utenti dopo aver contato le righe
*/
void regist(utente [], char [], int);


void avvio(mostra mst[], opera opr[], utente utn[], int num_utenti)
{
    int selez, ripeti;
    char username[dim];

    printf("  ---- Avvio del programma ----\n\n");
    printf("  Benvenuto, cosa vuoi fare?\n  1 - Login\n  2 - Registrazione\n  Per uscire premere un qualsiasi altro tasto\n>>> ");
    scanf("%d", &selez);
    switch(selez)
    {
    case 1: //caso in cui voglio fare il login
        accesso(utn, username, num_utenti);
        do
        {
            ripeti = 0;
            if(strcmp("none", username) != 0) //se il login è fallito esci dal programma
            {
                menu(mst, opr, utn, username);
                if(strcmp("none", username) != 0)
                {
                    printf("\n  ---- Premi 1 se vuoi usare ancora il programma ----\n>>> ");
                    scanf("%d", &ripeti);
                }
            }
        }
        while(ripeti == 1 && strcmp("none", username) != 0); //se c'è stato un errore di autenticazione o se il profilo è stato cancellato devo uscire dal programma
        break;

    case 2: //caso in cui voglio registrarmi
        fflush(stdin);
        regist(utn, username, num_utenti);
        FILE *ptr = fopen("file_utenti.csv", "r");
        num_utenti++;
        utente nuovo_utn[num_utenti];
        popola_utenti(ptr, nuovo_utn); //così invio a menu l'array di struct con tutti gli utenti vecchi più quello nuovo
        do
        {
            ripeti = 0;
            menu(mst, opr, nuovo_utn, username);
            if(strcmp("none", username) != 0) //se ho cancellato l'account che ho appena creato non mando il messaggio per continuare a usare il programma
            {
                printf("\n  ---- Premi 1 se vuoi usare ancora il programma ----\n>>> ");
                scanf("%d", &ripeti);
            }
        }
        while(ripeti == 1 && strcmp("none", username) != 0);
        break;
    }

    printf("\n  ---- Grazie per aver usato il programma ----");
}


void menu(mostra mst[], opera opr[], utente utn[], char username[])
{
    if(strcmp(username, "admin") == 0)
    {
        admin_menu(mst, opr, utn, username);
    }
    else
    {
        FILE *pt_mostra = fopen("file_mostre.csv","r");
        FILE *pt_opera = fopen("file_opere.csv","r");
        FILE *pt_utente = fopen("file_utenti.csv","r");
        int num_mostre = conta_righe(pt_mostra);
        int num_opere = conta_righe(pt_opera);
        int num_utenti = conta_righe(pt_utente);
        int selez;

        fflush(stdin);
        printf("\n  Cosa vuoi fare?\n  1 - Prenotazione\n  2 - Visualizza/modifica profilo\n  3 - Informazioni sulle mostre/opere d'arte\n");
        do
        {
            printf(">>> ");
            scanf("%d", &selez);
        }
        while(selez < 1 || selez > 3);

        switch(selez)
        {
        case 1: //caso in cui voglio prenotarmi
            prenotazione(mst, utn, username, num_mostre);
            break;

        case 2: //caso in cui voglio visualizzare/modificare i dati
            profilo(mst, utn, username, num_utenti);
            break;

        case 3: //caso in cui voglio cercare
            ricerca(mst, opr, num_mostre, num_opere);
            break;
        }

        fclose(pt_mostra);
        fclose(pt_opera);
        fclose(pt_utente);
    }
}


void accesso(utente utn[], char username[], int num_utenti)
{
    int ind_utn, conta_err = 0;
    char password[dim];
    bool accesso_err;

    fflush(stdin);
    do
    {
        printf("\n  Inserisci username:\n>>> ");
        gets(username);
        for(ind_utn = 0; ind_utn < num_utenti; ind_utn++)
        {
            accesso_err = (strcmp(utn[ind_utn].username, username));
            if(!accesso_err)
            {
                break; //se l'ho trovato esco subito dal ciclo
            }
            if(ind_utn == (num_utenti - 1)) //vuol dire che ho controllato tutti gli username del file, non trovando l'username
            {
                printf("\n\a  Errore: username non valido.");
                conta_err++;
            }
        }
    }
    while (accesso_err && conta_err < max_errori);

    if(conta_err != max_errori)
    {
        do
        {
            printf("\n  Inserisci password:\n>>> ");
            gets(password);
            critt(password);
            accesso_err = strcmp(utn[ind_utn].password, password);
            if(!accesso_err)
            {
                break;
            }
            else
            {
                printf("\n\a  Errore: password non valida.");
                conta_err++;
            }
        }
        while (accesso_err && conta_err < max_errori); //se sbaglio continuo a chiedere la password, ma se supero i 5 errori esco dal ciclo
    }
    if(conta_err == max_errori) //vuol dire che se in totale ho fallito l'accesso 5 volte tra username e password allora si manda un messaggio di errore
    {
        printf("\n\n  Troppi tentativi sbagliati, chiusura del programma\n");
        strcpy(username, "none");
    }
}


void regist(utente utn[], char username[], int num_utenti)
{
    FILE *pt_utente = fopen("file_utenti.csv", "r+");
    bool regist_err;
    char nome[dim], cognome[dim], password[dim];

    fseek(pt_utente, 0, SEEK_END);
    printf("\n  Inserisci il tuo nome:\n>>> ");
    gets(nome);
    printf("\n Inserisci il tuo cognome:\n>>> ");
    gets(cognome);
    do
    {
        regist_err = false;
        printf("\n  Inserisci username per la registrazione:\n>>> ");
        gets(username);
        for(int i = 0; i < num_utenti; i++)
        {
            if((strcmp(username, utn[i].username)) == 0 || (username, "none") == 0) //se l'username è già usato oppure non è valido si manda un messaggio d'errore
            {
                regist_err = true;
                printf("\n\a  Username gia' in uso o non valido.");
                break;
            }
        }
    }
    while (regist_err);

    do
    {
        printf("\n  Inserisci password (almeno %d caratteri):\n>>> ", lung_passw);
        gets(password);
    }
    while (strlen(password) < lung_passw); //la password deve avere almeno (lung_passw) carattero

    critt(password);
    fprintf(pt_utente, "\n%s,%s,%s,%s,0,0,0", nome, cognome, username, password);
    fclose(pt_utente);
    printf("\n  Account creato con successo\n");
}

#endif
