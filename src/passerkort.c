#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "Passerkort.h"

const char *behorighet_till_text(Behorighet status) {
    return (status == BEHORIGHET_AKTIV) ? "Aktiv" : "Ingen";
}

int giltigt_kortnummer(const char *kortnummer) {
    if (kortnummer == NULL || kortnummer[0] == '\0') {
        return 0;
    }

    for (size_t i = 0; kortnummer[i] != '\0'; i++) {
        if (!isalnum((unsigned char)kortnummer[i])) {
            return 0;
        }
    }

    return 1;
}

void initiera_kort(Passerkort *kort, const char *kortnummer, Behorighet status, const char *datum) {
    if (kort == NULL) {
        return;
    }

    if (kortnummer != NULL) {
        snprintf(kort->kortnummer, sizeof(kort->kortnummer), "%s", kortnummer);
    } else {
        kort->kortnummer[0] = '\0';
    }

    kort->behorighet = status;

    if (datum != NULL && datum[0] != '\0') {
        snprintf(kort->datum, sizeof(kort->datum), "%s", datum);
    } else {
        snprintf(kort->datum, sizeof(kort->datum), "okant-datum");
    }
}