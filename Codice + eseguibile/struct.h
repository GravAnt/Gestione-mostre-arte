#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#define dim 30

typedef struct mostra
{
    char nome[dim];
    char luogo[dim];
    int giorno_inizio;
    int mese_inizio;
    int giorno_fine;
    int mese_fine;
    int max_partecipanti;
    char responsabile[dim];
} mostra;


typedef struct opera
{
    char nome[dim];
    char autore[dim];
    char tipo[dim];
    char genere[dim];
    char periodo[dim];
    int anno;
    int codice; //il codice indica in quale mostra è esposta l'opera
} opera;


typedef struct utente
{
    char nome[dim];
    char cognome[dim];
    char username[dim];
    char password[dim];
    int prenotazione; //prenotazione indica in quale mostra si è prenotato l'utente. Se non si è prenotato, allora prenotazione ha valore 0
    int giorno_prenot;
    int mese_prenot;
} utente;

#endif
