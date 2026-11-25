#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "kortlista.h"
#include "door.h"

static void rensa_nyrad(char *str) {
    if (str == NULL) {
        return;
    }
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

static int hitta_kort_index(const Kortlista *lista, const char *kortnummer) {
    if (lista == NULL || lista->kort == NULL || kortnummer == NULL) {
        return -1;
    }

    for (size_t i = 0; i < lista->antal; i++) {
        if (strcmp(lista->kort[i].kortnummer, kortnummer) == 0) {
            return (int)i;
        }
    }
    return -1;
}

static int sakerstall_kapacitet(Kortlista *lista, size_t behov) {
    if (lista == NULL) {
        return 0;
    }

    if (behov <= lista->kapacitet) {
        return 1;
    }

    size_t ny_kapacitet = (lista->kapacitet == 0) ? START_KAPACITET : lista->kapacitet;
    while (ny_kapacitet < behov) {
        if (ny_kapacitet > (size_t)-1 / 2) {
            return 0;
        }
        ny_kapacitet *= 2;
    }

    Passerkort *temp = realloc(lista->kort, ny_kapacitet * sizeof(Passerkort));
    if (temp == NULL) {
        fprintf(stderr, "Fel: Kunde inte allokera minne for kortlistan.\n");
        return 0;
    }

    lista->kort = temp;
    lista->kapacitet = ny_kapacitet;
    return 1;
}

static void dagens_datum(char *buffert, size_t storlek) {
    if (buffert == NULL || storlek == 0) {
        return;
    }

    time_t nu = time(NULL);
    struct tm tm_lokal;
    struct tm *tm_pekare = localtime_r(&nu, &tm_lokal);

    if (tm_pekare != NULL && strftime(buffert, storlek, "%Y-%m-%d", tm_pekare) > 0) {
        return;
    }

    snprintf(buffert, storlek, "okant-datum");
}

int init_kortlista(Kortlista *lista, const char *filnamn) {
    if (lista == NULL) {
        return 0;
    }

    lista->kort = calloc(START_KAPACITET, sizeof(Passerkort));
    if (lista->kort == NULL) {
        fprintf(stderr, "Fel: Misslyckades med initial minnesallokering.\n");
        lista->antal = 0;
        lista->kapacitet = 0;
        lista->filnamn = filnamn;
        return 0;
    }

    lista->antal = 0;
    lista->kapacitet = START_KAPACITET;
    lista->filnamn = filnamn;
    return 1;
}

LaggTillResultat lagg_till_kort(Kortlista *lista, const char *kortnummer, Behorighet status) {
    if (lista == NULL || kortnummer == NULL) {
        return LAGG_TILL_OGILTIGT;
    }

    if (!giltigt_kortnummer(kortnummer)) {
        return LAGG_TILL_OGILTIGT;
    }

    if (hitta_kort_index(lista, kortnummer) != -1) {
        return LAGG_TILL_FINNS_REDAN;
    }

    if (status != BEHORIGHET_INGEN && status != BEHORIGHET_AKTIV) {
        return LAGG_TILL_OGILTIGT;
    }

    if (!sakerstall_kapacitet(lista, lista->antal + 1)) {
        return LAGG_TILL_MINNESFEL;
    }

    char datum[DATUM_MAX];
    dagens_datum(datum, sizeof(datum));

    initiera_kort(&lista->kort[lista->antal], kortnummer, status, datum);
    lista->antal++;
    return LAGG_TILL_OK;
}

void visa_kort(const Kortlista *lista) {
    if (lista == NULL || lista->kort == NULL || lista->antal == 0) {
        printf("Inga passerkort registrerade.\n");
        return;
    }

    printf("\n--- Registrerade kort (%zu st) ---\n", lista->antal);
    for (size_t i = 0; i < lista->antal; i++) {
        const Passerkort *k = &lista->kort[i];
        printf("[%zu] Kortnummer: %-15s | Behorighet: %-8s | Datum: %s\n",
               i + 1,
               k->kortnummer,
               behorighet_till_text(k->behorighet),
               k->datum);
    }
}

int andra_behorighet(Kortlista *lista, const char *kortnummer) {
    if (lista == NULL || lista->kort == NULL || kortnummer == NULL) {
        return 0;
    }

    int idx = hitta_kort_index(lista, kortnummer);
    if (idx == -1) {
        return 0;
    }

    lista->kort[idx].behorighet =
        (lista->kort[idx].behorighet == BEHORIGHET_AKTIV)
            ? BEHORIGHET_INGEN
            : BEHORIGHET_AKTIV;
    return 1;
}

int ladda_kort(Kortlista *lista) {
    if (lista == NULL || lista->filnamn == NULL) {
        return 0;
    }

    FILE *fp = fopen(lista->filnamn, "r");
    if (fp == NULL) {
        return 1;
    }

    char rad[128];
    while (fgets(rad, sizeof(rad), fp) != NULL) {
        rensa_nyrad(rad);
        if (rad[0] == '\0') {
            continue;
        }

        char *sep1 = strchr(rad, ';');
        if (sep1 == NULL) {
            fprintf(stderr, "Varning: Ogiltig rad i kortfil hoppas over.\n");
            continue;
        }
        *sep1 = '\0';

        char *sep2 = strchr(sep1 + 1, ';');
        if (sep2 == NULL) {
            fprintf(stderr, "Varning: Ogiltig rad i kortfil hoppas over.\n");
            continue;
        }
        *sep2 = '\0';

        const char *kortnummer = rad;
        const char *behorighet_str = sep1 + 1;
        const char *datum = sep2 + 1;

        if (!giltigt_kortnummer(kortnummer) || strlen(kortnummer) >= KORTNUMMER_MAX ||
            (strcmp(behorighet_str, "0") != 0 && strcmp(behorighet_str, "1") != 0) ||
            datum[0] == '\0' || strlen(datum) >= DATUM_MAX) {
            fprintf(stderr, "Varning: Korrupt post i kortfil ignorerades.\n");
            continue;
        }

        if (hitta_kort_index(lista, kortnummer) != -1) {
            fprintf(stderr, "Varning: Dubblettkort '%s' i fil ignorerades.\n", kortnummer);
            continue;
        }

        if (!sakerstall_kapacitet(lista, lista->antal + 1)) {
            fclose(fp);
            return 0;
        }

        Behorighet status = (strcmp(behorighet_str, "1") == 0)
                                ? BEHORIGHET_AKTIV
                                : BEHORIGHET_INGEN;
        initiera_kort(&lista->kort[lista->antal], kortnummer, status, datum);
        lista->antal++;
    }

    fclose(fp);
    return 1;
}

int spara_kort(const Kortlista *lista) {
    if (lista == NULL || lista->kort == NULL || lista->filnamn == NULL) {
        return 0;
    }

    FILE *fp = fopen(lista->filnamn, "w");
    if (fp == NULL) {
        perror("Fel vid oppning av kortfil for skrivning");
        return 0;
    }

    for (size_t i = 0; i < lista->antal; i++) {
        const Passerkort *k = &lista->kort[i];
        int status_int = (k->behorighet == BEHORIGHET_AKTIV) ? 1 : 0;
        if (fprintf(fp, "%s;%d;%s\n", k->kortnummer, status_int, k->datum) < 0) {
            perror("Fel vid skrivning till kortfil");
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

void frigor_kortlista(Kortlista *lista) {
    if (lista == NULL) {
        return;
    }
    free(lista->kort);
    lista->kort = NULL;
    lista->antal = 0;
    lista->kapacitet = 0;
    lista->filnamn = NULL;
}