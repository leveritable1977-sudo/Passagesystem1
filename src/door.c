#include <stdio.h>
#include <string.h>
#include "door.h"

void oppna_dorr_pa_distans(void) {
    printf("Dorren oppnad pa distans.\n");
}

int kontrollera_passage(const Passerkort *kort, size_t antal, const char *kortnummer) {
    if (kortnummer == NULL || kortnummer[0] == '\0') {
        printf("Passage nekad: inget kortnummer angivet.\n");
        return 0;
    }

    if (kort == NULL || antal == 0) {
        printf("Passage nekad: kortnummer %s ar inte registrerat.\n", kortnummer);
        return 0;
    }

    for (size_t i = 0; i < antal; i++) {
        if (strcmp(kort[i].kortnummer, kortnummer) == 0) {
            if (kort[i].behorighet == BEHORIGHET_AKTIV) {
                printf("Passage beviljad for kort %s (%s).\n",
                       kort[i].kortnummer, kort[i].datum);
                return 1;
            }
            printf("Passage nekad: kort %s har ingen aktiv behorighet.\n", kort[i].kortnummer);
            return 0;
        }
    }

    printf("Passage nekad: kortnummer %s ar inte registrerat.\n", kortnummer);
    return 0;
}