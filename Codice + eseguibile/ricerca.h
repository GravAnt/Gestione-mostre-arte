#ifndef RICERCA_H_INCLUDED
#define RICERCA_H_INCLUDED
#define url_dim 100
#define command_length 13 //per la ricerca google, quando devo sostituire gli spazi con +, non devo sostituire gli spazi del comando cmd start, ma solo quelli dell'url_dim
#define spazio 32
#define piu 43
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>


/**
*Funzione che apre il menù per la ricerca
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]int:numero mostre dopo il conteggio
*@paramin[in]int:numero opere dopo il conteggio
*/
void ricerca(mostra [], opera [], int, int);
/**
*Funzione che apre il menù per la ricerca di un'opera
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]int:numero opere dopo il conteggio
*/
void ricerca_opr(mostra [], opera [], int);
/**
*Funzione che apre il menù per la ricerca di un'opera tramite il nome
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]int:numero opere dopo il conteggio
*/
void ricerca_nome(mostra [], opera [], int);
/**
*Funzione che apre il menù per la ricerca di un'opera tramite l'autore
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]int:numero opere dopo il conteggio
*/
void ricerca_autore(mostra [], opera [], int);
/**
*Funzione che apre il menù per la ricerca di un'opera tramite il tipo
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]int:numero opere dopo il conteggio
*/
void ricerca_tipo(mostra [], opera [], int);
/**
*Funzione che apre il menù per la ricerca di un'opera tramite il genere
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]int:numero opere dopo il conteggio
*/
void ricerca_genere(mostra [], opera [], int);
/**
*Funzione che apre il menù per la ricerca di un'opera tramite il periodo
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]int:numero opere dopo il conteggio
*/
void ricerca_periodo(mostra [], opera [], int);
/**
*Funzione che apre il menù per la ricerca di un'opera tramite l'anno
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]int:numero opere dopo il conteggio
*/
void ricerca_anno(mostra [], opera [], int);
/**
*Funzione che apre il menù per la ricerca di una mostra specifica
*@paramin[in]mostra:struct mostra
*@paramin[in]opera:struct opera
*@paramin[in]int:numero mostre dopo il conteggio
*@paramin[in]int:numero opere dopo il conteggio
*/
void ricerca_mst(mostra [], opera [], int, int);
/**
*Funzione che consente la ricerca su google di un'opera
*@paramin[in]opera:struct opera
*@paramin[in]int:indice
*/
void ricerca_google(opera [], int);


void ricerca(mostra mst[], opera opr[], int num_mostre, int num_opere)
{
    int selez;

    printf("\n  Cosa vuoi fare?\n  1 - Cerca opere d'arte\n  2 - Informazioni sulle mostre\n");
    do
    {
        printf(">>> ");
        scanf("%d", &selez);
    }
    while(selez != 1 && selez != 2);

    switch(selez)
    {
    case 1: //caso in cui voglio cercare opere d'arte
        ricerca_opr(mst, opr, num_opere);
        break;

    case 2: //caso in cui voglio vedere info sulle mostre
        ricerca_mst(mst, opr, num_mostre, num_opere);
        break;
    }
}


void ricerca_opr(mostra mst[], opera opr[], int num_opere)
{
    int selez;

    printf("\n  Cerca in base a:\n  1 - Nome dell'opera\n  2 - Autore\n  3 - Tipo\n  4 - Genere\n  5 - Periodo storico\n  6 - Anno di produzione\n  7 - Annulla ricerca\n");
    do
    {
        printf(">>> ");
        scanf("%d", &selez);
    }
    while(selez < 1 && selez > 7);

    switch(selez)
    {
    case 1: //cerco in base a nome opera
        ricerca_nome(mst, opr, num_opere);
        break;

    case 2: //cerco in base all'autore
        ricerca_autore(mst, opr, num_opere);
        break;

    case 3: //cerco in base al tipo
        ricerca_tipo(mst, opr, num_opere);
        break;

    case 4: //cerco in base al genere
        ricerca_genere(mst, opr, num_opere);
        break;

    case 5: //cerco in base al periodo storico
        ricerca_periodo(mst, opr, num_opere);
        break;

    case 6: //cerco in base all'anno di produzione
        ricerca_anno(mst, opr, num_opere);
        break;

    case 7: //annullamento ricerca
        printf("\n  Ricerca annullata\n");
        break;
    }
}


void ricerca_nome(mostra mst[], opera opr[], int num_opere)
{
    int ripeti;
    char nome_cercato[dim], nome_opera[dim];

    do
    {
        bool trovato = false;
        printf("\n  Inserisci il nome dell'opera da cercare (ad esempio 'Guernica'):\n>>> ");
        ripeti = 0;
        fflush(stdin);
        gets(nome_cercato);
        int lung = strlen(nome_cercato);
        for(int i = 0; i < lung; i++)
        {
            nome_cercato[i] = toupper(nome_cercato[i]); //rendo il nome da cercare in maiuscolo
        }

        for(int i = 0; i < num_opere; i++)
        {
            strcpy(nome_opera, opr[i].nome);
            lung = strlen(nome_opera);
            for(int i = 0; i < lung; i++)
            {
                nome_opera[i] = toupper(nome_opera[i]); /*rendo il nome da confrontare in maiuscolo. In questo modo ho evitato che la ricerca sia case sensitive
                per migliorare l'esperienza d'uso dell'utente */
            }

            if(strcmp(nome_cercato, nome_opera) == 0) //il nome dev'essere esatto, non sono valide sottostringhe
            {
                visualizza_opr(mst, opr, i);
                ricerca_google(opr, i);
                trovato = true;
            }
        }

        if(!trovato)
        {
            printf("\n\a  Non e' stata trovata alcuna opera d'arte con quel nome nelle nostre mostre\n");
        }
        printf("\n  Se vuoi ripetere la ricerca premi 1\n>>> ");
        scanf("%d", &ripeti);
    }
    while(ripeti == 1);
}


void ricerca_autore(mostra mst[], opera opr[], int num_opere)
{
    int ripeti;
    char autore_cercato[dim], autore_opera[dim];

    do
    {
        bool trovato = false;
        printf("\n  Inserisci l'autore di cui vuoi cercare le opere (ad esempio 'Van Gogh'):\n>>> ");
        ripeti = 0;
        fflush(stdin);
        gets(autore_cercato);
        int lung = strlen(autore_cercato);
        for(int i = 0; i < lung; i++)
        {
            autore_cercato[i] = toupper(autore_cercato[i]);
        }

        for(int i = 0; i < num_opere; i++)
        {
            strcpy(autore_opera, opr[i].autore);
            lung = strlen(autore_opera);
            for(int i = 0; i < lung; i++)
            {
                autore_opera[i] = toupper(autore_opera[i]);
            }

            if(strcmp(autore_cercato, autore_opera) == 0)
            {
                visualizza_opr(mst, opr, i);
                ricerca_google(opr, i);
                trovato = true;
            }
        }

        if(!trovato)
        {
            printf("\n\a  Non e' stata trovata alcuna opera d'arte realizzata dall'autore inserito\n");
        }
        printf("\n  Se vuoi ripetere la ricerca premi 1\n>>> ");
        scanf("%d", &ripeti);
    }
    while(ripeti == 1);
}


void ricerca_tipo(mostra mst[], opera opr[], int num_opere)
{
    int ripeti;
    char tipo_cercato[dim], tipo_opera[dim];

    do
    {
        bool trovato = false;
        printf("\n  Inserisci il tipo delle opere da ricercare (ad esempio 'Scultura'):\n>>> ");
        ripeti = 0;
        fflush(stdin);
        gets(tipo_cercato);
        int lung = strlen(tipo_cercato);
        for(int i = 0; i < lung; i++)
        {
            tipo_cercato[i] = toupper(tipo_cercato[i]);
        }

        for(int i = 0; i < num_opere; i++)
        {
            strcpy(tipo_opera, opr[i].tipo);
            lung = strlen(tipo_opera);
            for(int i = 0; i < lung; i++)
            {
                tipo_opera[i] = toupper(tipo_opera[i]);
            }
            if(strcmp(tipo_cercato, tipo_opera) == 0)
            {
                visualizza_opr(mst, opr, i);
                ricerca_google(opr, i);
                trovato = true;
            }
        }

        if(!trovato)
        {
            printf("\n\a  Non e' stata trovata alcuna opera appartenente al tipo inserito\n");
        }
        printf("\n  Se vuoi ripetere la ricerca premi 1\n>>> ");
        scanf("%d", &ripeti);
    }
    while(ripeti == 1);
}


void ricerca_genere(mostra mst[], opera opr[], int num_opere)
{
    int ripeti;
    char genere_cercato[dim], genere_opera[dim];

    do
    {
        bool trovato = false;
        printf("\n  Inserisci il genere delle opere da ricercare (ad esempio 'Ritratto'):\n>>> ");
        ripeti = 0;
        fflush(stdin);
        gets(genere_cercato);
        int lung = strlen(genere_cercato);
        for(int i = 0; i < lung; i++)
        {
            genere_cercato[i] = toupper(genere_cercato[i]);
        }

        for(int i = 0; i < num_opere; i++)
        {
            strcpy(genere_opera, opr[i].genere);
            lung = strlen(genere_opera);
            for(int i = 0; i < lung; i++)
            {
                genere_opera[i] = toupper(genere_opera[i]);
            }

            if(strcmp(genere_cercato, genere_opera) == 0)
            {
                visualizza_opr(mst, opr, i);
                ricerca_google(opr, i);
                trovato = true;
            }
        }

        if(!trovato)
        {
            printf("\n\a  Non e' stata trovata alcuna opera appartenente al genere inserito\n");
        }
        printf("\n  Se vuoi ripetere la ricerca premi 1\n>>> ");
        scanf("%d", &ripeti);
    }
    while(ripeti == 1);
}


void ricerca_periodo(mostra mst[], opera opr[], int num_opere)
{
    int ripeti;
    char periodo_cercato[dim], periodo_opera[dim];

    do
    {
        bool trovato = false;
        printf("\n  Inserisci il periodo storico delle opere da ricercare (ad esempio 'Rinascimento'):\n>>> ");
        ripeti = 0;
        fflush(stdin);
        gets(periodo_cercato);
        int lung = strlen(periodo_cercato);
        for(int i = 0; i < lung; i++)
        {
            periodo_cercato[i] = toupper(periodo_cercato[i]);
        }

        for(int i = 0; i < num_opere; i++)
        {
            strcpy(periodo_opera, opr[i].periodo);
            lung = strlen(periodo_opera);
            for(int i = 0; i < lung; i++)
            {
                periodo_opera[i] = toupper(periodo_opera[i]);
            }

            if(strcmp(periodo_cercato, periodo_opera) == 0)
            {
                visualizza_opr(mst, opr, i);
                ricerca_google(opr, i);
                trovato = true;
            }
        }

        if(!trovato)
        {
            printf("\n\a  Non e' stata trovata alcuna opera appartenente al genere inserito\n");
        }
        printf("\n  Se vuoi ripetere la ricerca premi 1\n>>> ");
        scanf("%d", &ripeti);
    }
    while(ripeti == 1);
}


void ricerca_anno(mostra mst[], opera opr[], int num_opere)
{
    int anno_cercato, ripeti;

    do
    {
        bool trovato = false;
        printf("\n  Inserisci l'anno di produzione delle opere da ricercare (ad esempio '1504').\n  Se e' A.C. inserisci l'anno preceduto dal simbolo -\n>>> ");
        ripeti = 0;
        scanf("%d", &anno_cercato);
        for(int i = 0; i < num_opere; i++)
        {
            if(anno_cercato == opr[i].anno)
            {
                visualizza_opr(mst, opr, i);
                ricerca_google(opr, i);
                trovato = true;
            }
        }

        if(!trovato)
        {
            printf("\n\a  Non e' stata trovata alcuna opera prodotta nell'anno inserito\n");
        }
        printf("\n  Se vuoi ripetere la ricerca premi 1\n>>> ");
        scanf("%d", &ripeti);
    }
    while(ripeti == 1);
}


void ricerca_mst(mostra mst[], opera opr[], int num_mostre, int num_opere)
{
    int mostra_selez, info_opere, ripeti;

    printf("\n  Queste sono le mostre di cui e' possibile visualizzare le informazioni:\n");
    for(int i = 0; i < num_mostre; i++)
    {
        printf("  - %d: %s\n", (i+1), mst[i].nome);
    }
    do
    {
        ripeti = 0;
        printf("\n  Inserisci il numero corrispondente alla mostra di cui vuoi visualizzare le informazioni:\n");
        do
        {
            printf(">>> ");
            scanf("%d", &mostra_selez);
        }
        while(mostra_selez < 1 || mostra_selez > num_mostre);

        mostra_selez--; //decremento perché l'utente solitamente inserisce i valori a partire da 1, ma nell'array si parte dalla posizione 0
        printf("\n  Hai selezionato: %s\n", mst[mostra_selez].nome);
        visualizza_mst(mst, mostra_selez);
        printf("\n  Inserisci 1 se vuoi visualizzare l'elenco delle opere esposte nella mostra selezionata:\n>>> ");
        scanf("%d", &info_opere);
        if(info_opere == 1)
        {
            printf("\n  Nella mostra sono esposte le seguenti opere:\n");
            for(int i = 0; i < num_opere; i++)
            {
                if(opr[i].codice == mostra_selez)
                {
                    printf("  - %s di %s\n", opr[i].nome, opr[i].autore);
                }
            }
            printf("\n  Per altre informazioni su una specifica opera seleziona 'Cerca opere d'arte' nel menu' principale\n");
        }
        printf("  Inserisci 1 se vuoi visualizzare le informazioni di un'altra mostra:\n>>> ");
        scanf("%d", &ripeti);
    }
    while(ripeti == 1);
}


void ricerca_google(opera opr[], int i)
{
    int ricerca;

    printf("  Vuoi avere piu' informazioni su quest'opera? Se si' inserisci 1\n>>> ");
    scanf("%d", &ricerca);
    if(ricerca == 1)
    {
        char url[url_dim];
        strcpy(url, "cmd /c start www.google.it/search?q=");
        strcat(url, opr[i].nome);
        strcat(url, "+");
        strcat(url, opr[i].autore);
        int lung = strlen(url);
        for(int j = command_length; j < lung; j++)
        {
            if(url[j] == spazio)
            {
                url[j] = piu; //al posto degli spazi si mette il simbolo + per ottenere l'url corretto
            }
        }
        system(url);
    }
}

#endif // RICERCA_H_INCLUDED
