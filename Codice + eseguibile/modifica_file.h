#ifndef MODIFICA_FILE_H_INCLUDED
#define MODIFICA_FILE_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/**
*Menù per modificare le mostre da parte dell'admin
*@paramin[in]mostra:struct mostra
*@paramin[in]int:indice mostre
*@paramin[in]int:numero delle mostre dopo il conteggio
*@paramin[in]int:variabile per selezionare l'azione da compiere
*@paramin[in]bool:rimuovere i numeri magici
*/
void modifica_mst(mostra [], int, int, int, bool *); //modifica da parte dell'admin
/**
*Funzione per aggiungere una data disponibile alla prenotazione in una mostra
*@paramin[in]mostra:struct mostra
*@paramin[in]int:indice mostre
*/
void nuova_data(mostra [], int);
/**
*Menù per modificare le opere da parte dell'admin
*@paramin[in]opera:struct opera
*@paramin[in]int:indice opere
*@paramin[in]int:numero delle opere dopo il conteggio
*@paramin[in]int:variabile per selezionare l'azione da compiere
*@paramin[in]bool:rimuovere i numeri magici
*/
void modifica_opr(opera [], int, int, int, bool *);
/**
*Menù per modificare il profilo da parte dell'admin
*@paramin[in]utente:struct utente
*@paramin[in]int:indice utenti
*@paramin[in]int:numero degli utenti dopo il conteggio
*@paramin[in]int:variabile per selezionare l'azione da compiere
*@paramin[in]bool:rimuovere i numeri magici
*/
void modifica_utn(utente [], int, int, int, bool *);
/**
*Funzione per aggiungere una mostra al file
*/
void aggiungi_mostra();
/**
*Funzione per aggiungere un'opera al file
*/
void aggiungi_opera();
/**
*Funzione per aggiungere un utente al file
*/
void aggiungi_utente();


void modifica_mst(mostra mst[], int ind_mst, int num_mostre, int selez, bool *elimina)
{
    FILE *pt_mostra = fopen("file_mostre.csv", "w");

    switch(selez)
    {
    case 1: //modifica nome mostra
        printf("\n  Inserisci nuovo nome:\n>>> ");
        gets(mst[ind_mst].nome);
        break;

    case 2: //modifica luogo mostra
        printf("\n  Inserisci nuovo luogo di esposizione:\n>>> ");
        gets(mst[ind_mst].luogo);
        break;

    case 3: //modifica data esposizione mostra
        nuova_data(mst, ind_mst);
        break;

    case 4: //modifica numero massimo visitatori
        printf("\n  Isnerisci il numero massimo di visitatori della mostra:\n>>> ");
        scanf("%d", &mst[ind_mst].max_partecipanti);
        break;

    case 5: //modifica responsabile mostra
        printf("\n  Inserisci il responsabile della mostra:\n>>> ");
        gets(mst[ind_mst].responsabile);
        break;

    case 6: //cancella mostra
        printf("\n  Per evitare malfunzionamenti il programma sara' chiuso");
        *elimina = true;
        break;
    }

    for(int i = 0; i < num_mostre; i++)
    {
        if(ind_mst != i || !*elimina) //se voglio cancellare la mostra non la riscrivo nel file
        {
            fprintf(pt_mostra, "%s,%s,%d,%d,", mst[i].nome, mst[i].luogo, mst[i].giorno_inizio, mst[i].mese_inizio);
            fprintf(pt_mostra, "%d,%d,%d,%s", mst[i].giorno_fine, mst[i].mese_fine, mst[i].max_partecipanti, mst[i].responsabile);
            if(*elimina && ind_mst == num_mostre - 1) //se devo cancellare l'ultima riga...
            {
                if(i != num_mostre - 2)
                {
                    fprintf(pt_mostra, "\n"); //...allora quando mi trovo alla penultima non devo andare a capo
                }
            }
            else
            {
                if(i != num_mostre - 1)
                {
                    fprintf(pt_mostra, "\n"); //quando riscrivo il file non devo andare a capo se mi trovo all'ultima riga
                }
            }
        }
    }
    fclose(pt_mostra);
}


void nuova_data(mostra mst[], int ind_mst)
{
    int nuova_data;

    printf("\n  Se la mostra e' sempre aperta ai visitatori inserisci 1:\n>>> ");
    scanf("%d", &nuova_data);
    if(nuova_data == 1)
    {
        mst[ind_mst].giorno_inizio = 0;
        mst[ind_mst].mese_inizio = 0;
        mst[ind_mst].giorno_fine = 0;
        mst[ind_mst].mese_fine = 0;
    }
    else
    {
        printf("\n  Inserisci il giorno in cui inizia l'esposizione della mostra:\n>>> ");
        scanf("%d", &mst[ind_mst].giorno_inizio);
        printf("\n  Inserisci il mese in cui inizia l'esposizione della mostra:\n>>> ");
        scanf("%d", &mst[ind_mst].mese_inizio);
        printf("\n  Inserisci il giorno in cui finisce l'esposizione della mostra:\n>>> ");
        scanf("%d", &mst[ind_mst].giorno_fine);
        printf("\n  Inserisci il mese in cui inizia l'esposizione della mostra:\n>>> ");
        scanf("%d", &mst[ind_mst].mese_fine);
    }
}


void modifica_opr(opera opr[], int ind_opr, int num_opere, int selez, bool *elimina)
{
    FILE *pt_opera = fopen("file_opere.csv", "w");

    switch(selez)
    {
    case 1: //modifica nome opera
        printf("\n  Inserisci nuovo nome:\n>>> ");
        gets(opr[ind_opr].nome);
        break;

    case 2: //modifica autore opera
        printf("\n  Inserisci nuovo autore:\n>>> ");
        gets(opr[ind_opr].autore);
        break;

    case 3: //modifica tipo opera
        printf("\n  Inserisci nuovo tipo:\n>>> ");
        gets(opr[ind_opr].tipo);
        break;

    case 4: //modifica genere mostra
        printf("\n  Inserisci nuovo genere:\n>>> ");
        gets(opr[ind_opr].genere);
        break;

    case 5: //modifica periodo mostra
        printf("\n  Inserisci il periodo artistico:\n>>> ");
        gets(opr[ind_opr].periodo);
        break;

    case 6: //modifica anno opera
        printf("\n  Inserisci anno di produzione:\n>>> ");
        scanf("%d", &opr[ind_opr].anno);
        break;

    case 7: //modifica codice opera
        printf("\n  Inserisci codice:\n>>> ");
        scanf("%d", &opr[ind_opr].codice);
        break;

    case 8: //cancella opera
        printf("\n  Per evitare malfunzionamenti il programma sara' chiuso");
        *elimina = true;
        break;
    }

    for(int i = 0; i < num_opere; i++) //scrittura delle modifiche sul file
    {
        if(ind_opr != i || !*elimina)
        {
            fprintf(pt_opera, "%s,%s,%s,%s,%s,%d,%d", opr[i].nome, opr[i].autore, opr[i].tipo, opr[i].genere, opr[i].periodo, opr[i].anno, opr[i].codice);
            if(*elimina && ind_opr == num_opere - 1)
            {
                if(i != num_opere - 2)
                {
                    fprintf(pt_opera, "\n");
                }
            }
            else
            {
                if(i != num_opere - 1)
                {
                    fprintf(pt_opera, "\n");
                }
            }
        }
    }
    fclose(pt_opera);
}


void modifica_utn(utente utn[], int ind_utn, int num_utenti, int selez, bool *elimina)
{
    FILE *pt_utente = fopen("file_utenti.csv", "w");

    switch(selez)
    {
    case 1:
        printf("\n  Inserisci nuovo nome:\n>>> ");
        gets(utn[ind_utn].nome);
        break;

    case 2:
        printf("\n  Inserisci nuovo cognome:\n>>> ");
        gets(utn[ind_utn].cognome);
        break;

    case 3:
        printf("\n\a  ATTENZIONE: l'inserimento di un username gia' usato per un altro utente potrebbe causare malfunzionamenti critici\n  Inserisci nuovo username:\n>>> ");
        gets(utn[ind_utn].username);
        break;

    case 4:
        printf("\n  Inserisci nuova password:\n>>> ");
        gets(utn[ind_utn].password);
        critt(utn[ind_utn].password);
        break;

    case 5:
        printf("\n  Inserisci il numero della mostra di prenotazione:\n>>> ");
        scanf("%d", &utn[ind_utn].prenotazione);
        break;

    case 6:
        printf("\n  Inserisci giorno di prenotazione:\n>>> ");
        scanf("%d", &utn[ind_utn].giorno_prenot);
        break;

    case 7:
        printf("\n  Inserisci mese di prenotazione:\n>>> ");
        scanf("%d", &utn[ind_utn].mese_prenot);
        break;

    case 8:
        printf("\n  Per evitare malfunzionamenti il programma sara' chiuso");
        *elimina = true;
        break;
    }

    for(int i = 0; i < num_utenti; i++) //scrittura delle modifiche sul file
    {
        if(ind_utn != i || !*elimina)
        {
            fprintf(pt_utente, "%s,%s,%s,%s,%d,%d,%d", utn[i].nome, utn[i].cognome, utn[i].username, utn[i].password, utn[i].prenotazione, utn[i].giorno_prenot, utn[i].mese_prenot);
            if(*elimina && ind_utn == num_utenti - 1)
            {
                if(i != num_utenti - 2)
                {
                    fprintf(pt_utente, "\n");
                }
            }
            else
            {
                if(i != num_utenti - 1)
                {
                    fprintf(pt_utente, "\n");
                }
            }
        }
    }
    fclose(pt_utente);
}


void aggiungi_mostra()
{
    FILE *pt_mostra = fopen("file_mostre.csv", "r+");
    int no_scadenza;
    char riga[dim];

    fseek(pt_mostra, 0, SEEK_END);
    printf("\n  Inserisci il nome della nuova mostra:\n>>> ");
    gets(riga);
    fprintf(pt_mostra, "\n%s,", riga);
    printf("\n  Inserisci il luogo di esposizione:\n>>> ");
    gets(riga);
    fprintf(pt_mostra, "%s,", riga);
    printf("\n  Inserisci 1 se la nuova mostra e' disponibile sempre ai vistatori:\n>>> ");
    scanf("%d", &no_scadenza);
    fflush(stdin);
    if(no_scadenza == 1)
    {
        fprintf(pt_mostra, "0,0,0,0,"); //perché nella formattazione del file se la mostra non ha scadenza allora si mette 0 al posto delle date
    }
    else
    {
        printf("\n\a  ATTENZIONE: l'inserimento di date non esistenti potrebbe causare malfunzionamenti critici\n");
        printf("\n  Inserisci il giorno di inizio dell'esposizione della nuova mostra:\n>>> ");
        gets(riga);
        fprintf(pt_mostra, "%s,", riga);
        printf("\n  Inserisci il mese di inizio dell'esposizione della nuova mostra:\n>>> ");
        gets(riga);
        fprintf(pt_mostra, "%s,", riga);
        printf("\n  Inserisci il giorno di fine dell'esposizione della nuova mostra:\n>>> ");
        gets(riga);
        fprintf(pt_mostra, "%s,", riga);
        printf("\n  Inserisci il mese di fine dell'esposizione della nuova mostra:\n>>> ");
        gets(riga);
        fprintf(pt_mostra, "%s,", riga);
    }
    printf("\n  Inserisci il numero massimo di visitatori per la mostra:\n>>> ");
    gets(riga);
    fprintf(pt_mostra, "%s,", riga);
    printf("\n  Inserisci il responsabile della mostra:\n>>> ");
    gets(riga);
    fprintf(pt_mostra, "%s", riga);
    fclose(pt_mostra);
}


void aggiungi_opera()
{
    FILE *pt_opera = fopen("file_opere.csv", "r+");
    char riga[dim];

    fseek(pt_opera, 0, SEEK_END);
    printf("\n  Inserisci il nome della nuova opera:\n>>> ");
    gets(riga);
    fprintf(pt_opera, "\n%s,", riga);
    printf("\n  Inserisci l'autore:\n>>> ");
    gets(riga);
    fprintf(pt_opera, "%s,", riga);
    printf("\n  Inserisci il tipo:\n>>> ");
    gets(riga);
    fprintf(pt_opera, "%s,", riga);
    printf("\n  Inserisci il genere:\n>>> ");
    gets(riga);
    fprintf(pt_opera, "%s,", riga);
    printf("\n  Inserisci il periodo artistico:\n>>> ");
    gets(riga);
    fprintf(pt_opera, "%s,", riga);
    printf("\n  Inserisci l'anno di produzione (con - davanti se A.C.):\n>>> ");
    gets(riga);
    fprintf(pt_opera, "%s,", riga);
    printf("\n  Inserisci il codice riferito alla mostra in cui l'opera e' esposta:\n>>> ");
    gets(riga);
    fprintf(pt_opera, "%s", riga);
    fclose(pt_opera);
}


void aggiungi_utente()
{
    FILE *pt_utente = fopen("file_utenti.csv", "r+");
    char riga[dim];

    fseek(pt_utente, 0, SEEK_END);
    printf("\n  Inserisci il nome del nuovo utente:\n>>> ");
    gets(riga);
    fprintf(pt_utente, "\n%s,", riga);
    printf("\n  Inserisci il cognome:\n>>> ");
    gets(riga);
    fprintf(pt_utente, "%s,", riga);
    printf("\n\a  ATTENZIONE: l'inserimento di un username gia' usato per un altro utente potrebbe causare malfunzionamenti critici\n  Inserisci username:\n>>> ");
    gets(riga);
    fprintf(pt_utente, "%s,", riga);
    printf("\n  Inserisci la password:\n>>> ");
    gets(riga);
    critt(riga);
    fprintf(pt_utente, "%s,", riga);
    printf("\n  Inserisci il codice della mostra a cui si e' prenotato l'utente:\n>>> ");
    gets(riga);
    fprintf(pt_utente, "%s,", riga);
    printf("\n  Inserisci il giorno di prenotazione:\n>>> ");
    gets(riga);
    fprintf(pt_utente, "%s,", riga);
    printf("\n  Inserisci il mese di prenotazione:\n>>> ");
    gets(riga);
    fprintf(pt_utente, "%s", riga);
    fclose(pt_utente);
}

#endif
