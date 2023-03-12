#ifndef GESTIONE_FILE_H_INCLUDED
#define GESTIONE_FILE_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/**
*Funzione che conta le righe del file aperto
*@paramin[in]FILE:file delle mostre
*@paramin[in]FILE:file delle opere
*@paramin[in]FILE:file degli utenti
*/
int conta_righe(FILE *);
/**
*Funzione di stampa del contenuto del file utenti
*@paramin[in]utente:struct utente
*@paramin[in]int:numero utenti dopo il conteggio
*/
void stampa_utn(utente [], int);/**
/**
*Funzione che aggiorna il file prendendo la data odierna ed eliminando eventuali prenotazioni passate
*@paramin[in]utente:struct utente
*@paramin[in]int:numero utenti dopo il conteggio
*/
void aggiorna_file(utente [], int);
/**
*Funzione che consente all'utente di visualizzare informazioni su un utente, una mostra o un'opera in particolare
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]utente:struct utente
*@paramin[in]int:numero mostra dopo il conteggio
*@paramin[in]int:numero opere dopo il conteggio
*@paramin[in]int:numero utenti dopo il conteggio
*/
void visualizza_file(mostra [], opera [], utente [], int, int, int);


int conta_righe(FILE *ptr)
{
    int i = 0;
    char c;

    while(!feof(ptr))
    {
        c = getc(ptr);
        if(c == '\n')
        {
            i++;
        }
    }
    rewind(ptr);
    return(++i); //si incrementa perché si deve considerare anche l'ultima riga, che non ha la sequenza di escape \n alla fine
}


void stampa_utn(utente utn[], int num_utenti)
{
    FILE *pt_utente = fopen("file_utenti.csv", "w");

    for(int i = 0; i < num_utenti; i++)
    {
        fprintf(pt_utente, "%s,%s,%s,%s,%d,%d,", utn[i].nome, utn[i].cognome, utn[i].username, utn[i].password, utn[i].prenotazione, utn[i].giorno_prenot);
        if(i < (num_utenti - 1)) //se è l'ultimo utente da stampare non devo aggiungere \n perché i file non devono avere una riga vuota
        {
            fprintf(pt_utente, "%d\n", utn[i].mese_prenot);
        }
        else
        {
            fprintf(pt_utente, "%d", utn[i].mese_prenot);
        }
    }
    fclose(pt_utente);
}


void aggiorna_file(utente utn[], int num_utenti)
{
    int data[3]; //formato: giorno, mese, anno
    bool aggiorna = false;

    data_odierna(data);
    for(int i = 0; i < num_utenti; i++)
    {
        if(data[0] > utn[i].giorno_prenot && data[1] == utn[i].mese_prenot)
        {
            utn[i].prenotazione = 0;
            utn[i].giorno_prenot = 0;
            utn[i].mese_prenot = 0;
            aggiorna = true;
        }
        if(data[1] > utn[i].mese_prenot)
        {
           utn[i].prenotazione = 0;
           utn[i].giorno_prenot = 0;
           utn[i].mese_prenot = 0;
           aggiorna = true;
        }
    }

    if(aggiorna)
    {
        stampa_utn(utn, num_utenti); //stampo su file solo se è avvenuto un reset di prenotazione almeno una volta
    }
}


void visualizza_file(mostra mst[], opera opr[], utente utn[], int num_mostre, int num_opere, int num_utenti)
{
    int selez, ripeti, ind;

    do
    {
        printf("\n  Cosa vuoi visualizzare?\n  1 - Mostre\n  2 - Opere\n  3 - Utenti\n");
        do
        {
            printf(">>> ");
            scanf("%d", &selez);
        }
        while(selez < 1 || selez > 3);

        switch(selez)
        {
        case 1: //visualizza mostre
            printf("\n  Di quale mostra vuoi visualizzare le informazioni?\n");
            for(int i = 0; i <  num_mostre; i++)
            {
                printf("  %d - %s\n", i+1, mst[i].nome);
            }

            do
            {
                printf(">>> ");
                scanf("%d", &ind);
            }
            while(ind < 1 || ind > num_mostre);

            ind--;
            printf("\n");
            visualizza_mst(mst, ind);
            break;

        case 2: // visualizza opere
            printf("\n  Di quale opera vuoi visualizzare le informazioni?\n");
            for(int i = 0; i <  num_opere; i++)
            {
                printf("  %d - %s\n", i+1, opr[i].nome);
            }

            do
            {
                printf(">>> ");
                scanf("%d", &ind);
            }
            while(ind < 1 || ind > num_opere);

            ind--;
            printf("\n");
            visualizza_opr(mst, opr, ind);
            break;

        case 3: //visualizza utenti
            printf("\n  Di quale utente vuoi visualizzare le informazioni?\n");
            for(int i = 0; i <  num_utenti; i++)
            {
                printf("  %d - %s\n", i+1, utn[i].username);
            }

            do
            {
                printf(">>> ");
                scanf("%d", &ind);
            }
            while(ind < 1 || ind > num_utenti);

            ind--;
            printf("\n");
            visualizza_utn(mst, utn, ind);
            break;
        }

        printf("\n  Inserisci 1 se vuoi continuare a visualizzare i dati presenti nei file:\n>>> ");
        scanf("%d", &ripeti);
    }
    while(ripeti == 1);
}




#endif // GESTIONE_FILE_H_INCLUDED
