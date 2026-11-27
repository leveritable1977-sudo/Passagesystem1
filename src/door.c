#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "door.h"

static void paxa_tre_sekunder(void) {
    struct timespec vanta;
    vanta.tv_sec = 3;
    vanta.tv_nsec = 0;

    while (nanosleep(&vanta, &vanta) != 0) {
        /* fortsätt återstående tid om avbruten av signal */
    }
}

const char *behorighet_till_text(Behorighet status) {
    return (status == BEHORIGHET_AKTIV) ? "Aktiv" : "Ingen";
}

void oppna_dorr_pa_distans(void) {
    printf("Dorren oppnad pa distans. Statuslampa: GRON (3 sekunder)...\n");
    fflush(stdout);
    paxa_tre_sekunder();
    printf("Statuslampa: SLACKT (dorren aterstalld).\n");
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