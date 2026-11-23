#ifndef DOOR_H
#define DOOR_H

#include <stddef.h>
#include "Passerkort.h"

int kontrollera_passage(const Passerkort *kort, size_t antal, const char *kortnummer);

#endif