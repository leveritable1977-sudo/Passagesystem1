#ifndef KORTLISTA_H
#define KORTLISTA_H

#include <stddef.h>
#include "Passerkort.h"

int init_kortlista(Kortlista *lista, const char *filnamn);
int lagg_till_kort(Kortlista *lista);
void visa_kort(const Kortlista *lista);
int andra_behorighet(Kortlista *lista, const char *kortnummer);
int ladda_kort(Kortlista *lista);
int spara_kort(const Kortlista *lista);
void frigor_kortlista(Kortlista *lista);

#endif