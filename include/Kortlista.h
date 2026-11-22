#ifndef KORTLISTA_H
#define KORTLISTA_H

#include <stddef.h>
#include "Passerkort.h"

void init_kortlista(Passerkort **kort, size_t *antal, size_t *kapacitet);
int lagg_till_kort(Passerkort **kort, size_t *antal, size_t *kapacitet);
void visa_kort(const Passerkort *kort, size_t antal);
void frigor_kortlista(Passerkort **kort, size_t *antal, size_t *kapacitet);

#endif