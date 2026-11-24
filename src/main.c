#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Kortlista.h"
#include "door.h"
#include "safeinput.h"

#define KORTFIL "kortregister.txt"

static void skriv_meny(void) {
    printf("\n=== Passagesystem - Huvudmeny ===\n");
    printf("1. Oppna dorren pa distans\n");
    printf("2. Lista samtliga kort\n");
    printf("3. Lagg till ett nytt kort\n");
    printf("4. Andra behorighet for befintligt kort\n");
    printf("5. Simulera en kortskanning\n");
    printf("6. Avsluta programmet\n");
}

static void hantera_lagg_till_kort(Kortlista *lista) {
    char kortnummer[KORTNUMMER_MAX];
    int behorighet_val = 0;

    printf("Ange kortnummer (endast bokstaver/siffror): ");
    if (!las_rad(kortnummer, sizeof(kortnummer))) {
        printf("Kunde inte lasa kortnummer.\n");
        return;
    }

    if (!giltigt_kortnummer(kortnummer)) {
        printf("Ogiltigt kortnummer. Anvand minst ett tecken (A-Z, a-z, 0-9).\n");
        return;
    }

    printf("Behorighet (0 = Ingen, 1 = Aktiv): ");
    if (!las_heltal(&behorighet_val) ||
        (behorighet_val != BEHORIGHET_INGEN && behorighet_val != BEHORIGHET_AKTIV)) {
        printf("Ogiltig behorighet. Kortet lades inte till.\n");
        return;
    }

    Behorighet status = (behorighet_val == BEHORIGHET_AKTIV)
                            ? BEHORIGHET_AKTIV
                            : BEHORIGHET_INGEN;

    LaggTillResultat resultat = lagg_till_kort(lista, kortnummer, status);

    switch (resultat) {
        case LAGG_TILL_OK:
            printf("Kort '%s' tillagt (%s).\n", kortnummer, behorighet_till_text(status));
            if (!spara_kort(lista)) {
                fprintf(stderr, "Varning: Kortregistret kunde inte sparas till %s.\n", KORTFIL);
            }
            break;

        case LAGG_TILL_FINNS_REDAN:
            printf("Kort '%s' finns redan registrerat.\n", kortnummer);
            break;

        case LAGG_TILL_MINNESFEL:
            printf("Kunde inte lagga till kort '%s' (saknar ledigt minne).\n", kortnummer);
            break;

        case LAGG_TILL_OGILTIGT:
        default:
            printf("Kunde inte lagga till kort '%s' (ogiltig data).\n", kortnummer);
            break;
    }
}

static void hantera_kortskanning(const Kortlista *lista) {
    char testkort[KORTNUMMER_MAX];

    printf("Ange kortnummer att testa vid dorren: ");
    if (!las_rad(testkort, sizeof(testkort))) {
        printf("Kunde inte lasa kortnummer.\n");
        return;
    }

    PassageResultat resultat = kontrollera_passage(lista->kort, lista->antal, testkort);

    switch (resultat) {
        case PASSAGE_BEVILJAD:
            printf("Passage beviljad for kort %s.\n", testkort);
            break;
        case PASSAGE_NEKAD_INAKTIV:
            printf("Passage nekad: kort %s har ingen aktiv behorighet.\n", testkort);
            break;
        case PASSAGE_NEKAD_EJ_REGISTRERAT:
            printf("Passage nekad: kortnummer %s ar inte registrerat.\n", testkort);
            break;
        case PASSAGE_NEKAD_OGILTIG_INMATA:
        default:
            printf("Passage nekad: inget kortnummer angivet.\n");
            break;
    }
}

int main(void) {
    Kortlista lista;
    int val = 0;
    int kor = 1;

    if (!init_kortlista(&lista, KORTFIL)) {
        fprintf(stderr, "Kunde inte initiera kortlistan.\n");
        return EXIT_FAILURE;
    }

    if (!ladda_kort(&lista)) {
        fprintf(stderr, "Varning: Kunde inte lasa in hela kortregistret fran %s.\n", KORTFIL);
    }

    while (kor) {
        skriv_meny();
        if (!las_heltal(&val)) {
            printf("Ogiltigt val. Ange en siffra mellan 1 och 6.\n");
            continue;
        }

        switch (val) {
            case 1:
                if (oppna_dorr_pa_distans()) {
                    printf("Dorren oppnad pa distans.\n");
                } else {
                    printf("Kunde inte oppna dorren pa distans.\n");
                }
                break;

            case 2:
                visa_kort(&lista);
                break;

            case 3:
                hantera_lagg_till_kort(&lista);
                break;

            case 4: {
                char kortnummer[KORTNUMMER_MAX];
                printf("Ange kortnummer for att andra behorighet: ");
                if (las_rad(kortnummer, sizeof(kortnummer))) {
                    if (andra_behorighet(&lista, kortnummer)) {
                        printf("Behorigheten for kort '%s' har andrats.\n", kortnummer);
                        if (!spara_kort(&lista)) {
                            fprintf(stderr, "Varning: Kortregistret kunde inte sparas till %s.\n", KORTFIL);
                        }
                    } else {
                        printf("Kunde inte andra behorighet (kortet hittades inte).\n");
                    }
                } else {
                    printf("Kunde inte lasa kortnummer.\n");
                }
                break;
            }

            case 5:
                hantera_kortskanning(&lista);
                break;

            case 6:
                if (!spara_kort(&lista)) {
                    fprintf(stderr, "Varning: Kortregistret kunde inte sparas till %s.\n", KORTFIL);
                }
                kor = 0;
                break;

            default:
                printf("Ogiltigt val. Ange en siffra mellan 1 och 6.\n");
                break;
        }
    }

    frigor_kortlista(&lista);
    printf("Programmet avslutat.\n");
    return EXIT_SUCCESS;
}