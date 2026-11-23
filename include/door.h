#ifndef DOOR_H
#define DOOR_H

#include <stddef.h>
#include "Passerkort.h"

void oppna_dorr_pa_distans(void);
int kontrollera_passage(const Passerkort *kort, size_t antal, const char *kortnummer);

#endif