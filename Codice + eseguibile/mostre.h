#ifndef MOSTRE_H_INCLUDED
#define MOSTRE_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
*Funzione che inserisce le mostre lette da file in un array di struct
*@paramin[in]FILE:file mostre
*@paramin[in]mostra:struct mostra
*/
void popola_mostre(FILE *, mostra []);
/**
*Funzione che fa visualizzare le informazioni di una mostra
*@paramin[in]mostra:struct mostra
*@paramin[in]int:indice mostre
*/
void visualizza_mst(mostra [], int);


void popola_mostre(FILE *pt_mostra, mostra mst[])
{
    char dim_struct[sizeof(mostra)];
    int i = 0;
    //si legge ogni riga del file e man mano si leggono i valori immediatamente precedenti alla virgola
    while(!feof(pt_mostra))
    {
        fgets(dim_struct, sizeof(mostra), pt_mostra);
        strcpy(mst[i].nome, strtok(dim_struct, ","));
        strcpy(mst[i].luogo, strtok(NULL, ","));
        mst[i].giorno_inizio = atoi(strtok(NULL, ","));
        mst[i].mese_inizio = atoi(strtok(NULL, ","));
        mst[i].giorno_fine = atoi(strtok(NULL, ","));
        mst[i].mese_fine = atoi(strtok(NULL, ","));
        mst[i].max_partecipanti = atoi(strtok(NULL, ","));
        strcpy(mst[i].responsabile, strtok(NULL, "\n"));
        i++;
    }
}


void visualizza_mst(mostra mst[], int ind_mst)
{
    printf("  Luogo d'esposizione: %s\n", mst[ind_mst].luogo);
    if(mst[ind_mst].giorno_inizio == 0)
    {
        printf("  La mostra e' disponibile per tutto l'anno\n");
    }
    else
    {
        printf("  La mostra e' disponibile dal %d/%d al %d/%d\n", mst[ind_mst].giorno_inizio, mst[ind_mst].mese_inizio, mst[ind_mst].giorno_fine, mst[ind_mst].mese_fine);
    }
    printf("  Il numero massimo di prenotazioni per un singolo giorno e': %d\n", mst[ind_mst].max_partecipanti);
    printf("  Responsabile della mostra: %s\n", mst[ind_mst].responsabile);
    //in base alle politiche sulla privacy della galleria d'arte, il responsabile della mostra potrebbe anche essere non visibile (cancellando la riga di codice)
}

#endif // MOSTRE_H_INCLUDED
