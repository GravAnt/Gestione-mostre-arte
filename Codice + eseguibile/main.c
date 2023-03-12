#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "gestione_file.h"
#include "avvio.h"
#include "mostre.h"
#include "opere.h"
#include "utenti.h"

int main()
{
    FILE *pt_mostra = fopen("file_mostre.csv", "r");
    FILE *pt_opera = fopen("file_opere.csv", "r");
    FILE *pt_utente = fopen("file_utenti.csv", "r");

    if(pt_mostra == NULL || pt_opera == NULL || pt_utente == NULL)
    {
        printf("\n\a  Errore di apertura file\n");
    }
    else
    {
        int num_mostre = conta_righe(pt_mostra);
        int num_opere = conta_righe(pt_opera);
        int num_utenti = conta_righe(pt_utente);
        //dichiarazione degli array di struct la cui dimensione è il numero di righe per ogni file
        mostra mst[num_mostre];
        opera opr[num_opere];
        utente utn[num_utenti];
        //inserimento dei dati letti da file negli array di struct
        popola_mostre(pt_mostra, mst);
        popola_opere(pt_opera, opr);
        popola_utenti(pt_utente, utn);
        fclose(pt_mostra);
        fclose(pt_opera);
        fclose(pt_utente);
        //aggiorna_file serve per eliminare le prenotazioni se un giorno è passato
        aggiorna_file(utn, num_utenti);
        avvio(mst, opr, utn, num_utenti);
    }
    return 0;
}
