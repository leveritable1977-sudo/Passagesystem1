#include <string.h>
#include "door.h"

int oppna_dorr_pa_distans(void) {
    return 1;
}

PassageResultat kontrollera_passage(const Passerkort *kort, size_t antal, const char *kortnummer) {
    if (kortnummer == NULL || kortnummer[0] == '\0') {
        return PASSAGE_NEKAD_OGILTIG_INMATA;
    }

    if (kort == NULL || antal == 0) {
        return PASSAGE_NEKAD_EJ_REGISTRERAT;
    }

    for (size_t i = 0; i < antal; i++) {
        if (strcmp(kort[i].kortnummer, kortnummer) == 0) {
            if (kort[i].behorighet == BEHORIGHET_AKTIV) {
                return PASSAGE_BEVILJAD;
            }
            return PASSAGE_NEKAD_INAKTIV;
        }
    }

    return PASSAGE_NEKAD_EJ_REGISTRERAT;
}