#ifndef OPERE_H_INCLUDED
#define OPERE_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
*Funzione che inserisce le mostre lette da file in un array di struct
*@paramin[in]FILE:file opere
*@paramin[in]opera:struct opere
*/
void popola_opere(FILE *, opera []);
/**
*Funzione che visualizza le informazione di un'opera
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opere
*@paramin[in]int:indice opere
*/
void visualizza_opr(mostra [], opera [], int);


void popola_opere(FILE *pt_opera, opera opr[])
{
    char dim_struct[sizeof(opera)];
    int i = 0;
    //si legge ogni riga del file e man mano si leggono i valori immediatamente precedenti alla virgola
    while(!feof(pt_opera))
    {
        fgets(dim_struct, sizeof(opera), pt_opera);
        strcpy(opr[i].nome, strtok(dim_struct, ","));
        strcpy(opr[i].autore, strtok(NULL, ","));
        strcpy(opr[i].tipo, strtok(NULL, ","));
        strcpy(opr[i].genere, strtok(NULL, ","));
        strcpy(opr[i].periodo, strtok(NULL, ","));
        opr[i].anno = atoi(strtok(NULL, ","));
        opr[i].codice = atoi(strtok(NULL, "\n"));
        i++;
    }
}


void visualizza_opr(mostra mst[], opera opr[], int ind_opr)
{
    int ind_mst = opr[ind_opr].codice; //il codice indica la mostra in cui è esposta l'opera, e quindi corrisponde all'ind_mst

    printf("\n  Nome opera: %s\n  Autore: %s\n  Tipo: %s\n  Genere: %s\n  Periodo: %s\n", opr[ind_opr].nome, opr[ind_opr].autore, opr[ind_opr].tipo, opr[ind_opr].genere, opr[ind_opr].periodo);
    if(opr[ind_opr].anno < 0)
    {
        printf("  Anno di produzione: %d A.C.\n", (opr[ind_opr].anno * -1));
    }
    else
    {
        printf("  Anno di produzione: %d\n", opr[ind_opr].anno);
    }
    printf("  L'opera d'arte e' esposta in: '%s'\n", mst[ind_mst].nome);
}

#endif // OPERE_H_INCLUDED
