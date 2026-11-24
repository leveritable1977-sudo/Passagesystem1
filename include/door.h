#ifndef DOOR_H
#define DOOR_H

#include <stddef.h>
#include "Passerkort.h"

typedef enum {
    PASSAGE_NEKAD_OGILTIG_INMATA = -2,
    PASSAGE_NEKAD_EJ_REGISTRERAT = -1,
    PASSAGE_NEKAD_INAKTIV = 0,
    PASSAGE_BEVILJAD = 1
} PassageResultat;

int oppna_dorr_pa_distans(void);
PassageResultat kontrollera_passage(const Passerkort *kort, size_t antal, const char *kortnummer);

#endif