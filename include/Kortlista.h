#ifndef KORTLISTA_H
#define KORTLISTA_H

#include <stddef.h>
#include "passerkort.h"

typedef enum {
    LAGG_TILL_OK = 1,
    LAGG_TILL_FINNS_REDAN = 0,
    LAGG_TILL_MINNESFEL = -1,
    LAGG_TILL_OGILTIGT = -2
} LaggTillResultat;

int init_kortlista(Kortlista *lista, const char *filnamn);
LaggTillResultat lagg_till_kort(Kortlista *lista, const char *kortnummer, Behorighet status);
void visa_kort(const Kortlista *lista);
int andra_behorighet(Kortlista *lista, const char *kortnummer);
int ladda_kort(Kortlista *lista);
int spara_kort(const Kortlista *lista);
void frigor_kortlista(Kortlista *lista);

#endif