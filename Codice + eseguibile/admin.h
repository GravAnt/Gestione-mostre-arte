#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "modifica_file.h"


/**
*Apre il menu per le funzioni admin
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]utene:struct utente
*@paramin[in]char:username dell'admin
*/
void admin_menu(mostra [], opera [], utente [], char []);
/**
*Funzione per creare o aggiornare i file di backup
*@paramin[in]FILE:file delle mostre
*@paramin[in]FILE:file delle opere
*@paramin[in]FILE:file degli utenti
*/
void file_backup(FILE *, FILE *, FILE *);
/**
*Menù per la gestione dell'admin delle mostre
*@paramin[in]mostra:struct mostra
*@paramin[in]char:username dell'admin
*@paramin[in]int:numero delle mostre dopo aver contato le righe
*/
void admin_mostra(mostra [], char [], int);
/**
*Menù per la gestione dell'admin delle opere
*@paramin[in]opera:struct opera
*@paramin[in]char:username dell'admin
*@paramin[in]int:numero delle opere dopo aver contato le righe
*/
void admin_opera(opera [], char [], int);
/**
*Menù per la gestione dell'admin degli utenti
*@paramin[in]utente:struct utente
*@paramin[in]char:username dell'admin
*@paramin[in]int:numero degli utenti dopo aver contato le righe
*/
void admin_utente(utente [], char [], int);
/**
*Aggiungere una riga ad uno dei file cui le struct fanno riferimento
*/
void aggiungi_riga();


void admin_menu(mostra mst[], opera opr[], utente utn[], char username[])
{
    FILE *pt_mostra = fopen("file_mostre.csv","r");
    FILE *pt_opera = fopen("file_opere.csv","r");
    FILE *pt_utente = fopen("file_utenti.csv","r");
    int num_mostre = conta_righe(pt_mostra);
    int num_opere = conta_righe(pt_opera);
    int num_utenti = conta_righe(pt_utente);
    int selez;
    bool elimina = false;
    //richiesta di backup
    printf("\n\a  Autenticazione amministratore avvenuta con successo\n  ATTENZIONE: alcune modifiche potrebbero compromettere il funzionamento del programma se i dati sono contraddittori");
    printf("\n  Qualsiasi modifica sui file e' irreversibile, si consiglia di eseguire il backup\n");
    printf("\n  Inserisci 1 se vuoi eseguire il backup dei file:\n>>> ");
    scanf("%d", &selez);
    if(selez == 1)
    {
        file_backup(pt_mostra, pt_opera, pt_utente);
        printf("\n  Backup effettuato\n");
    }
    fclose(pt_mostra);
    fclose(pt_opera);
    fclose(pt_utente);

    printf("\n  Cosa vuoi fare?\n  1 - Modifica i dati delle mostre\n  2 - Modifica i dati delle opere\n  3 - Modifica i dati degli utenti\n  4 - Visualizza dati\n  5 - Aggiungi dati\n");
    do
    {
        printf(">>> ");
        scanf("%d", &selez);
    }
    while(selez < 1 || selez > 5);

    switch(selez)
    {
    case 1: //modifica dati delle mostre
        admin_mostra(mst, username, num_mostre);
        break;

    case 2: //modifica dati delle opere
        admin_opera(opr, username, num_opere);
        break;

    case 3: //modifica dati degli utenti
        admin_utente(utn, username, num_utenti);
        break;

    case 4: //visualizza dati
        visualizza_file(mst, opr, utn, num_mostre, num_opere, num_utenti);
        break;

    case 5: //aggiungi dati
        aggiungi_riga();
        printf("\n  Per evitare malfunzionamenti il programma sara' chiuso\n");
        strcpy(username, "none");
        break;
    }
}


void admin_mostra(mostra mst[], char username[], int num_mostre)
{
    int selez, ripeti, ind_mst;
    bool elimina = false;

    printf("\n  Seleziona mostra che vuoi modificare\n");
    for(int i = 0; i < num_mostre; i++)
    {
        printf("  %d - %s\n", (i+1), mst[i].nome);
    }

    do
    {
        printf(">>> ");
        scanf("%d", &ind_mst);
    }
    while (ind_mst < 1 || ind_mst > num_mostre);

    ind_mst--; //decremento perché l'utente solitamente inserisce i valori a partire da 1, ma nell'array si parte dalla posizione 0
    do
    {
        ripeti = 0; //bugfix perché quando si cancellava la mostra non si chiudeva il programma, non avevo messo ripeti = 0 dentro il ciclo iterativo
        printf("\n  Cosa vuoi modificare?\n  1 - Nome\n  2 - Luogo\n  3 - Data esposizione\n  4 - Numero massimo di visitatori in un giorno\n  5 - Responsabile della mostra\n  6 - Cancella mostra\n");
        do
        {
            printf(">>> ");
            scanf("%d", &selez);
        }
        while(selez < 1 || selez > 6);

        fflush(stdin);
        modifica_mst(mst, ind_mst, num_mostre, selez, &elimina);
        printf("\n  Modifiche eseguite con successo\n");
        if(!elimina)
        {
            printf("\n  Inserisci 1 se vuoi continuare a modificare i dati della mostra selezionata:\n>>> ");
            scanf("%d", &ripeti);
        }
        else strcpy(username, "none"); //in questo modo non chiedo all'utente se vuole fare altro, ma chiudo direttamente il programma
    }
    while(ripeti == 1);
}


void admin_opera(opera opr[], char username[], int num_opere)
{
    int selez, ripeti, ind_opr;
    bool elimina = false;

    printf("\n  Seleziona opera che vuoi modificare\n");
    for(int i = 0; i < num_opere; i++)
    {
        printf("  %d - %s\n", (i+1), opr[i].nome);
    }

    do
    {
        printf(">>> ");
        scanf("%d", &ind_opr);
    }
    while (ind_opr < 1 || ind_opr > num_opere);

    ind_opr--;
    do
    {
        ripeti = 0; //bugfix
        printf("\n  Cosa vuoi modificare?\n  1 - Nome\n  2 - Autore\n  3 - Tipo\n  4 - Genere\n  5 - Periodo\n  6 - Anno\n  7 - Codice\n  8 - Cancella opera\n");
        do
        {
            printf(">>> ");
            scanf("%d", &selez);
        }
        while(selez < 1 || selez > 8);

        fflush(stdin);
        modifica_opr(opr, ind_opr, num_opere, selez, &elimina);
        printf("\n  Modifiche eseguite con successo\n");
        if(!elimina)
        {
            printf("\n  Inserisci 1 se vuoi continuare a modificare i dati dell'opera selezionata:\n>>> ");
            scanf("%d", &ripeti);
        }
        else
        {
            strcpy(username, "none");
        }
    }
    while(ripeti == 1);
}


void admin_utente(utente utn[], char username[], int num_utenti)
{
    int selez, ripeti, ind_utn;
    bool elimina = false;

    printf("\n  Seleziona utente che vuoi modificare\n");
    for(int i = 1; i < num_utenti; i++) //non posso modificare il primo utente, che è l'admin
    {
        printf("  %d - %s\n", i, utn[i].username);
    }

    do
    {
        printf(">>> ");
        scanf("%d", &ind_utn);
    }
    while (ind_utn < 1 || ind_utn > num_utenti);

    do
    {
        ripeti = 0; //bugfix
        printf("\n  Cosa vuoi modificare?\n  1 - Nome\n  2 - Cognome\n  3 - Username\n  4 - Password\n  5 - Prenotazione\n  6 - Giorno\n  7 - Mese\n  8 - Cancella utente\n");
        do
        {
            printf(">>> ");
            scanf("%d", &selez);
        }
        while(selez < 1 || selez > 8);

        fflush(stdin);
        modifica_utn(utn, ind_utn, num_utenti, selez, &elimina);
        printf("\n  Modifiche eseguite con successo\n");
        if(!elimina)
        {
            printf("\n  Inserisci 1 se vuoi continuare a modificare i dati dell'utente selezionato:\n>>> ");
            scanf("%d", &ripeti);
        }
        else
        {
            strcpy(username, "none");
        }
    }
    while(ripeti == 1);
}


void aggiungi_riga()
{
    int selez;

    printf("\n  Cosa vuoi aggiungere?\n  1 - Nuova mostra\n  2 - Nuova opera\n  3 - Nuovo utente\n");
    do
    {
        printf(">>> ");
        scanf("%d", &selez);
    }
    while(selez < 1 || selez > 3);

    fflush(stdin);
    switch(selez)
    {
    case 1: //aggiungo nuova mostra
        aggiungi_mostra();
        break;

    case 2: //aggiungo nuova opera
        aggiungi_opera();
        break;

    case 3: //aggiungo nuovo utente
        aggiungi_utente();
        break;
    }
}


void file_backup(FILE *pt_mostra, FILE *pt_opera, FILE *pt_utente)
{
    char ch;
    FILE *ptr = fopen("backup_mostre.csv", "w");
    while((ch = fgetc(pt_mostra)) != EOF) //copio carattere per carattere fin quando non arrivo alla fine del file
    {
        fputc(ch, ptr);
    }
    fclose(ptr);

    ptr = fopen("backup_opere.csv", "w");
    while((ch = fgetc(pt_opera)) != EOF)
    {
        fputc(ch, ptr);
    }
    fclose(ptr);

    ptr = fopen("backup_utenti.csv", "w");
    while((ch = fgetc(pt_utente)) != EOF)
    {
        fputc(ch, ptr);
    }
    fclose(ptr);
}

#endif // ADMIN_H_INCLUDED
