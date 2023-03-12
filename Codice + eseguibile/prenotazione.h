#ifndef PRENOTAZIONE_H_INCLUDED
#define PRENOTAZIONE_H_INCLUDED
#define giorni_disdetta 7
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


/**
*Funzione che consente la prenotazione all'utente per una mostra
*@paramin[in]mostra:struct mostra
*@paramin[in]utente:struct utente
*@paramin[in]char:username dell'utente
*@paramin[in]int:numero mostre dopo il conteggio
*/
void prenotazione(mostra [], utente [], char [], int);
/**
*Funzione che consente l'inserimento della data per la prenotazione
*@paramin[in]mostra:struct mostra
*@paramin[in]utente:struct utente
*@paramin[in]char:username dell'utente
*@paramin[in]int:indice mostre
*/
void inserisci_data(mostra [], utente [], char [], int);
/**
*Funzione che rileva la data odierna
*@paramin[in]int: vettore data
*/
void data_odierna(int []);
/**
*Funzione che controlla il mese della data della prenotazione
*@paramin[in]mostra:struct mostra
*@paramin[in]int:vettore data
*@paramin[in]int:indice mostre
*@paramin[in]int:mese inserito per prenotare
*/
void controllo_mese(mostra [], int [], int , int *);
/**
*Funzione che controlla il giorno della data della prenotazione
*@paramin[in]mostra:struct mostra
*@paramin[in]utente:struct utente
*@paramin[in]int:vettore data
*@paramin[in]int:indice mostre
*@paramin[in]int:mese inserito per prenotare
*@paramin[in]int:giorno inserito per prenotare
*/
void controllo_giorno(mostra [], utente [], int [], int , int, int *);
/**
*Funzione che consente di disdire una prenotazione
*@paramin[in]utente:struct utente
*@paramin[in]int:indice utenti
*/
void disdici_prenotazione(utente [], int);
/**
*Funzione che restituisce il numero di giorni del mese corrente
*/
int giorni_mensili();


void prenotazione(mostra mst[], utente utn[], char username[], int num_mostre)
{
    FILE *pt_utente = fopen("file_utenti.csv","r");
    int ind_mst, ind_utn;

    for(ind_utn = 0; ind_utn < conta_righe(pt_utente); ind_utn++) //ciclo for utlizzato per ottenere l'ind_utn
    {
        if(strcmp(username, utn[ind_utn].username) == 0)
        {
            break;
        }
    }

    fclose(pt_utente);
    if(utn[ind_utn].prenotazione != 0) //se l'utente è prenotato, cioè il campo prenotazione non è 0, allora posso chiedergli a quale mostra prenotarsi
    {
        printf("\n\a  Hai gia' effettuato una prenotazione\n  Per prenotarti nuovamente devi eliminare la prenotazione precedente\n");
        printf("  Per farlo seleziona 'Visualizza/modifica profilo' e poi 'Modifica profilo'\n");
    }
    else
    {
        printf("\n  A quale mostra vuoi prenotarti? Inserisci il numero corrispondente\n");
        for(int i = 0; i < num_mostre; i++)
        {
            printf("  %d - %s\n", i+1, mst[i].nome);
        }

        do
        {
            printf(">>> ");
            scanf("%d", &ind_mst);
        }
        while (ind_mst < 1 || ind_mst > num_mostre);

        ind_mst--; //decremento perché l'utente solitamente inserisce i valori a partire da 1, ma nell'array si parte dalla posizione 0
        if(mst[ind_mst].giorno_inizio == 0)
        {
            printf("\n  La mostra e' sempre aperta ai visitatori\n");
        }
        else
        {
            printf("\n  Per questa mostra e' possibile prenotarsi dal %d/%d al %d/%d\n", mst[ind_mst].giorno_inizio, mst[ind_mst].mese_inizio, mst[ind_mst].giorno_fine, mst[ind_mst].mese_fine);
        }
        inserisci_data(mst, utn, username, ind_mst);
        printf("\n  Prenotazione avvenuta con successo\n");
    }
}


void inserisci_data(mostra mst[], utente utn[], char username[], int ind_mst)
{
    FILE *pt_utente = fopen("file_utenti.csv","r");
    int num_utenti = conta_righe(pt_utente), ind_utn;
    int mese_inserito, giorno_inserito, data[3];

    fclose(pt_utente);
    data_odierna(data);
    controllo_mese(mst, data, ind_mst, &mese_inserito);
    controllo_giorno(mst, utn, data, ind_mst, mese_inserito, &giorno_inserito);
    for(ind_utn = 0; ind_utn < num_utenti; ind_utn++)
    {
        if(strcmp(username, utn[ind_utn].username) == 0)
        {
            break;
        }
    }

    ind_mst++; //perché prima avevo decrementato la variabile
    utn[ind_utn].prenotazione = ind_mst;
    utn[ind_utn].giorno_prenot = giorno_inserito;
    utn[ind_utn].mese_prenot = mese_inserito;
    stampa_utn(utn, num_utenti);
}


void data_odierna(int data[])
{
    const int anno_base = 1900; //offset
    time_t tempo;
    struct tm *info_tempo;

    time(&tempo);
    info_tempo = localtime(&tempo);
    data[0] = info_tempo->tm_mday;
    data[1] = info_tempo->tm_mon + 1; //perché il mese è indicato da 0 a 11, e quindi ho bisogno di incrementare
    data[2] = info_tempo->tm_year + anno_base; //si somma perché tm_year considera il 1900 come anno 0
}


void controllo_mese(mostra mst[], int data[], int ind_mst, int *mese_inserito)
{
    bool data_err;

    printf("\n  Inserisci mese di prenotazione (da 1 a 12):\n");
    do
    {
        data_err = false;
        printf(">>> ");
        scanf("%d", &*mese_inserito);
        if(*mese_inserito < 1 || *mese_inserito > 12 || *mese_inserito < data[1]) //non si può prenotare per l'anno prossimo o per i mesi già passati
        {
            data_err = true;
        }
        if(mst[ind_mst].giorno_inizio != 0)
        {
            if(*mese_inserito < mst[ind_mst].mese_inizio || *mese_inserito > mst[ind_mst].mese_fine) //si controlla che il mese inserito sia compreso nel periodo della mostra
            {
                data_err = true;
            }
        }
        if(data_err) printf("\n\a  Mese non valido. Reinserisci il mese:\n");
    }
    while(data_err);
}


void controllo_giorno(mostra mst[], utente utn[], int data[], int ind_mst, int mese_inserito, int *giorno_inserito)
{
    FILE *pt_utente = fopen("file_utenti.csv", "r");
    int num_utenti = conta_righe(pt_utente);
    bool data_err;

    fclose(pt_utente);
    printf("\n  Inserisci giorno di prenotazione:\n>>> ");
    do
    {
        int num_prenotati = 0; //bugfix, num_prenotati l'avevo messo fuori dal do
        data_err = false;
        scanf("%d", &*giorno_inserito);
        //si controlla che l'utente abbia inserito un giorno compreso tra 1 e 31
        if(*giorno_inserito < 1 || *giorno_inserito > 31)
        {
            data_err = true;
        }
        //se l'anno non è bisestile non si può inserire un giorno maggiore di 28 a febbraio
        if(*giorno_inserito > 28 && mese_inserito == 2 && (data[2] % 4) != 0)
        {
            data_err = true;
        }
        //se l'anno è bisestile il 29 febbraio è accettato
        if(*giorno_inserito > 29 && mese_inserito == 2)
        {
            data_err = true;
        }
        //controllo per i mesi con 30 giorni
        if(*giorno_inserito == 31 && (mese_inserito == 4 || mese_inserito == 6 || mese_inserito == 9 || mese_inserito == 11))
        {
            data_err = true;
        }
        //si controlla che il mese inserito sia compreso nel periodo della mostra
        if(mst[ind_mst].giorno_inizio != 0)
        {
            if(mese_inserito == mst[ind_mst].mese_inizio && *giorno_inserito < mst[ind_mst].giorno_inizio)
            {
                data_err = true;
            }

            if(mese_inserito == mst[ind_mst].mese_fine && *giorno_inserito > mst[ind_mst].giorno_fine)
            {
                data_err = true;
            }
        }
        //se si prenota nel corrente mese non si puoò prenotare in un giorno già passato
        if(mese_inserito == data[1] && *giorno_inserito < data[0])
        {
            data_err = true;
        }
        //si controlla se si è raggiunto il numero massimo di prenotazioni giornaliere per quella mostra
        for(int i = 0; i < num_utenti; i++)
        {
            if(utn[i].prenotazione == (ind_mst + 1) && utn[i].giorno_prenot == *giorno_inserito && utn[i].mese_prenot == mese_inserito)
            {
                num_prenotati++;
            }
        }
        if(num_prenotati >= mst[ind_mst].max_partecipanti)
        {
            printf("\n\a  Per quel giorno e' stato raggiunto il massimo di prenotazioni\n");
            data_err = true;
        }
        //se si è verificato anche solo un errore (controllo in OR) si richiede di inserire il giorno
        if(data_err)
        {
            printf("\n\a  Giorno non valido, inserisci nuovamente il giorno di prenotazione:\n>>> ");
        }
    }
    while(data_err);
}


void disdici_prenotazione(utente utn[], int ind_utn)
{
    if(utn[ind_utn].prenotazione == 0)
    {
        printf("\n  Non hai ancora effettuato una prenotazione\n");
    }
    else
    {
        int data[3];
        //si verifica che la disdetta della prenotazione non sia a 7 giorni dall'evento
        data_odierna(data);
        if(utn[ind_utn].mese_prenot == data[1])
        {
            if(data[0] + giorni_disdetta <= utn[ind_utn].giorno_prenot)
            {
                utn[ind_utn].prenotazione = 0;
                utn[ind_utn].giorno_prenot = 0;
                utn[ind_utn].mese_prenot = 0;
                printf("\n  Prenotazione disdettata con successo\n");
            }
            else
            {
                printf("\n  Impossibile disidre la prenotazione a meno di una settimana dall'evento\n");
            }
        }
        else
        {
            int intervallo, lung_mese = giorni_mensili;

            intervallo = (lung_mese - data[0]) + utn[ind_utn].giorno_prenot;
            if(intervallo >= giorni_disdetta)
            {
                utn[ind_utn].prenotazione = 0;
                utn[ind_utn].giorno_prenot = 0;
                utn[ind_utn].mese_prenot = 0;
                printf("\n  Prenotazione disdettata con successo\n");
            }
            else
            {
                printf("\n  Impossibile disidre la prenotazione a meno di una settimana dall'evento\n");
            }
        }
    }
}

int giorni_mensili()
{
    int data[3], lung_mese;

    data_odierna(data);
    if(data[1] == 1 || data[1] == 3 || data[1] == 5 || data[1] == 7)
    {
        lung_mese = 31; //qui i "numeri magici" vanno bene perchè si tratta di mesi e giorni (anche se si potrebbe comunque usare i nomi dei mesi, invece che i numeri)
    }

    if(data[1] == 8 || data[1] == 10 || data[1] == 12)
    {
        lung_mese = 31;
    }

    if(data[1] == 4 || data[1] == 6 || data[1] == 9 || data[1] == 11)
    {
        lung_mese = 30;
    }

    if(data[1] == 2)
    {
        if((data[2] % 4) == 0)
        {
            lung_mese = 29;
        }
        else
        {
            lung_mese = 28;
        }
    }

    return lung_mese;
}

#endif // PRENOTAZIONE_H_INCLUDED
