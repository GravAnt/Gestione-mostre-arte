#ifndef UTENTI_H_INCLUDED
#define UTENTI_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
*Funzione che inserisce gli utenti letti da file in un array di struct
*@paramin[in]FILE:file utenti
*@paramin[in]utente:struct utente
*/
void popola_utenti(FILE *, utente []);
/**
*Funzione che apre il menù di gestione del profilo per l'utente
*@paramin[in]mostra:struct mostra
*@paramin[in]utente:struct utente
*@paramin[in]char:username dell'utente
*@paramin[in]int:indice utenti
*/
void profilo(mostra [], utente [], char [], int);
/**
*Funzione che visualizza le informazione sull'utente
*@paramin[in]mostra:struct mostra
*@paramin[in]utente:struct utente
*@paramin[in]int:indice utenti
*/
void visualizza_utn(mostra [], utente [], int);
/**
*Funzione che apre il menù per la modifica del profilo per l'utente
*@paramin[in]utente:struct utente
*@paramin[in]int:indice utenti
*@paramin[in]int:numero degli utenti dopo il conteggio
*/
void modifica_profilo(utente [], int, int); //modifica_profilo è per l'utente, modifica_utn è per l'admin
/**
*Funzione che cancella il profilo dell'utente
*@paramin[in]utente:struct utente
*@paramin[in]int:indice utenti
*@paramin[in]int:numero degli utenti dopo il conteggio
*/
void cancella_profilo(utente [], int, int);


void popola_utenti(FILE *pt_utente, utente utn[])
{
    char dim_struct[sizeof(utente)];
    int i = 0;
    //si legge ogni riga del file e man mano si leggono i valori immediatamente precedenti alla virgola
    while(!feof(pt_utente))
    {
        fgets(dim_struct, sizeof( utente), pt_utente);
        strcpy(utn[i].nome, strtok(dim_struct, ","));
        strcpy(utn[i].cognome, strtok(NULL, ","));
        strcpy(utn[i].username, strtok(NULL, ","));
        strcpy(utn[i].password, strtok(NULL, ","));
        utn[i].prenotazione = atoi(strtok(NULL, ","));
        utn[i].giorno_prenot = atoi(strtok(NULL, ","));
        utn[i].mese_prenot = atoi(strtok(NULL, "\n"));
        i++;
    }
}


void profilo(mostra mst[], utente utn[], char username[], int num_utenti)
{
    int selez, ind_utn;

    printf("\n  Cosa vuoi fare?\n  1 - Visualizza profilo\n  2 - Modifica profilo\n  3 - Cancella profilo\n");
    do
    {
        printf(">>> ");
        scanf("%d", &selez);
    }
    while(selez < 1 || selez > 3);

    for(ind_utn = 0; ind_utn < num_utenti; ind_utn++) //si usa il ciclo for per ottenere l'ind_utn
    {
        if(strcmp(username, utn[ind_utn].username) == 0)
        {
            break;
        }
    }

    switch(selez)
    {
    case 1:
        visualizza_utn(mst, utn, ind_utn);
        break;

    case 2:
        modifica_profilo(utn, ind_utn, num_utenti);
        break;

    case 3:
        cancella_profilo(utn, ind_utn, num_utenti);
        break;
    }

    if(selez == 3)
    {
        strcpy(username, "none"); //se il profilo è stato cancellato non si chiede all'utente se vuole continuare ad usare il programma, ma si esce direttamente
    }
}


void visualizza_utn(mostra mst[], utente utn[], int ind_utn)
{
    printf("\n  Informazioni sul tuo profilo:\n");
    printf("  - Nome: %s\n", utn[ind_utn].nome);
    printf("  - Cognome: %s\n", utn[ind_utn].cognome);
    printf("  - Username: %s\n", utn[ind_utn].username);
    decritt(utn[ind_utn].password); //si mette in chiaro la password perché vuole vedere la password non crittata
    printf("  - Password: %s\n", utn[ind_utn].password);
    critt(utn[ind_utn].password);
    if(utn[ind_utn].prenotazione == 0)
    {
        printf("  - Non hai ancora effettuato una prenotazione\n");
    }
    else
    {
        printf("  - Prenotato a: %s\n", mst[(utn[ind_utn].prenotazione - 1)].nome);
        printf("  - Prenotazione effettuata per il %d/%d\n", utn[ind_utn].giorno_prenot, utn[ind_utn].mese_prenot);
    }
}


void modifica_profilo(utente utn[], int ind_utn, int num_utenti)
{
    int selez;

    printf("\n  Cosa vuoi fare?\n  1 - Modifica nome\n  2 - Modifica cognome\n  3 - Modifica password\n  4 - Cancella prenotazione\n");
    do
    {
        printf(">>> ");
        scanf("%d", &selez);
    }
    while(selez < 1 || selez > 4);

    switch(selez)
    {
    case 1: //caso in cui voglio modificare il nome
        printf("\n  Inserisci nuovo nome:\n>>> ");
        char nuovo_nome[dim];
        scanf("%s", &nuovo_nome);
        strcpy(utn[ind_utn].nome, nuovo_nome);
        printf("\n  Nome modificato correttamente\n");
        break;

    case 2: //il cognome
        printf("\n  Inserisci nuovo cognome:\n>>> ");
        char nuovo_cogn[dim];
        scanf("%s", &nuovo_cogn);
        strcpy(utn[ind_utn].cognome, nuovo_cogn);
        printf("\n  Cognome modificato correttamente\n");
        break;

    case 3: //la password
        printf("\n  Inserisci nuova password (almeno 8 caratteri):\n");
        char nuova_passw[dim];
        do
        {
            printf(">>> ");
            scanf("%s", &nuova_passw);
        }
        while(strlen(nuova_passw) < 8);
        critt(nuova_passw);
        strcpy(utn[ind_utn].password, nuova_passw);
        printf("\n  Password modificata correttamente\n");
        break;

    case 4: //cancellare prenotazione
        disdici_prenotazione(utn, ind_utn);
        break;
    }
    stampa_utn(utn, num_utenti); //scrittura delle modifiche sul file
}


void cancella_profilo(utente utn[], int ind_utn, int num_utenti)
{
    FILE *pt_utente = fopen("file_utenti.csv", "w");

    for(int i = 0; i < num_utenti; i++)
    {
        if(strcmp(utn[i].username, utn[ind_utn].username) != 0) //stampo tutti gli utenti tranne quello che vuole cancellare il profilo
        {
            fprintf(pt_utente, "%s,%s,%s,%s,%d,%d,", utn[i].nome, utn[i].cognome, utn[i].username, utn[i].password, utn[i].prenotazione, utn[i].giorno_prenot);
            if(ind_utn == (num_utenti - 1))
            //se l'utente da cancellare è l'ultimo nel file (cioè ind_utn == num_utenti - 1) allora quando si arriva al penultimo non si deve stampare \n (non ci possono essere righe vuote)
            {
                if(i < (num_utenti - 2))
                {
                    fprintf(pt_utente, "%d\n", utn[i].mese_prenot);
                }
                else
                {
                    fprintf(pt_utente, "%d", utn[i].mese_prenot);
                }
            }
            else
            {
                if(i < (num_utenti - 1))
                {
                    fprintf(pt_utente, "%d\n", utn[i].mese_prenot);
                }
                else
                {
                    fprintf(pt_utente, "%d", utn[i].mese_prenot);
                }
            }
        }
    }

    printf("\n  Profilo eliminato\n");
    fclose(pt_utente);
}

#endif // UTENTI_H_INCLUDED
