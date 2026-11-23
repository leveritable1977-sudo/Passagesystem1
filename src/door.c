#include <stdio.h>
#include <string.h>
#include "door.h"

int kontrollera_passage(const Passerkort *kort, size_t antal, const char *kortnummer) {
    if (kort == NULL || antal == 0 || kortnummer == NULL) {
        printf("Passage nekad: inget giltigt kort hittades.\n");
        return 0;
    }

    for (size_t i = 0; i < antal; i++) {
        if (strcmp(kort[i].kortnummer, kortnummer) == 0) {
            if (kort[i].behorighet == BEHORIGHET_AKTIV) {
                printf("Dorren upplåst for kort %s.\n", kort[i].kortnummer);
                return 1;
            }
            printf("Passage nekad: kort %s har ingen aktiv behorighet.\n", kort[i].kortnummer);
            return 0;
        }
    }

    printf("Passage nekad: kortnummer %s ar inte registrerat.\n", kortnummer);
    return 0;
}