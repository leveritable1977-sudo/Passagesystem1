#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kortlista.h"

#define START_KAPACITET 4

static void rensa_nyrad(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void init_kortlista(Passerkort **kort, size_t *antal, size_t *kapacitet) {
    if (kort == NULL || antal == NULL || kapacitet == NULL) {
        return;
    }
    *kort = NULL;
    *antal = 0;
    *kapacitet = 0;
}

int lagg_till_kort(Passerkort **kort, size_t *antal, size_t *kapacitet) {
    if (kort == NULL || antal == NULL || kapacitet == NULL) {
        return 0;
    }

    if (*antal == *kapacitet) {
        size_t ny_kapacitet = (*kapacitet == 0) ? START_KAPACITET : (*kapacitet * 2);
        Passerkort *temp = realloc(*kort, ny_kapacitet * sizeof(Passerkort));
        if (temp == NULL) {
            printf("Fel: Kunde inte allokera minne for kortlistan.\n");
            return 0;
        }
        *kort = temp;
        *kapacitet = ny_kapacitet;
    }

    Passerkort nytt_kort;
    memset(&nytt_kort, 0, sizeof(nytt_kort));

    printf("Ange kortnummer: ");
    if (fgets(nytt_kort.kortnummer, sizeof(nytt_kort.kortnummer), stdin) == NULL) {
        return 0;
    }
    rensa_nyrad(nytt_kort.kortnummer);

    int val = 0;
    char buffert[16];
    printf("Behorighet (0 = Ingen, 1 = Aktiv): ");
    if (fgets(buffert, sizeof(buffert), stdin) == NULL) {
        return 0;
    }
    if (sscanf(buffert, "%d", &val) != 1 || (val != BEHORIGHET_INGEN && val != BEHORIGHET_AKTIV)) {
        printf("Ogiltig behorighet. Kortet lades inte till.\n");
        return 0;
    }
    nytt_kort.behorighet = (val == BEHORIGHET_AKTIV) ? BEHORIGHET_AKTIV : BEHORIGHET_INGEN;

    printf("Ange datum (YYYY-MM-DD): ");
    if (fgets(nytt_kort.datum, sizeof(nytt_kort.datum), stdin) == NULL) {
        return 0;
    }
    rensa_nyrad(nytt_kort.datum);

    nytt_kort.kort = NULL;

    (*kort)[*antal] = nytt_kort;
    (*antal)++;
    return 1;
}

void visa_kort(const Passerkort *kort, size_t antal) {
    if (kort == NULL || antal == 0) {
        printf("Inga passerkort registrerade.\n");
        return;
    }

    for (size_t i = 0; i < antal; i++) {
        const char *status_text = (kort[i].behorighet == BEHORIGHET_AKTIV) ? "Aktiv" : "Ingen";
        printf("[%zu] Kortnummer: %s | Behorighet: %s | Datum: %s\n",
               i + 1, kort[i].kortnummer, status_text, kort[i].datum);
    }
}

void frigor_kortlista(Passerkort **kort, size_t *antal, size_t *kapacitet) {
    if (kort != NULL && *kort != NULL) {
        free(*kort);
        *kort = NULL;
    }
    if (antal != NULL) {
        *antal = 0;
    }
    if (kapacitet != NULL) {
        *kapacitet = 0;
    }
}