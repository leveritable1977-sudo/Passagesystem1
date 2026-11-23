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
                /* Anpassa funktionsnamnet om din door.h använder ett annat namn */
                oppna_dorr_pa_distans();
                break;

            case 2:
                visa_kort(&lista);
                break;

            case 3:
                if (lagg_till_kort(&lista)) {
                    if (!spara_kort(&lista)) {
                        fprintf(stderr, "Varning: Kortregistret kunde inte sparas till %s.\n", KORTFIL);
                    }
                }
                break;

            case 4: {
                char kortnummer[KORTNUMMER_MAX];
                printf("Ange kortnummer for att andra behorighet: ");
                if (las_rad(kortnummer, sizeof(kortnummer))) {
                    if (andra_behorighet(&lista, kortnummer)) {
                        if (!spara_kort(&lista)) {
                            fprintf(stderr, "Varning: Kortregistret kunde inte sparas till %s.\n", KORTFIL);
                        }
                    }
                } else {
                    printf("Kunde inte lasa kortnummer.\n");
                }
                break;
            }

            case 5: {
                char testkort[KORTNUMMER_MAX];
                printf("Ange kortnummer att testa vid dorren: ");
                if (las_rad(testkort, sizeof(testkort))) {
                    kontrollera_passage(lista.kort, lista.antal, testkort);
                } else {
                    printf("Kunde inte lasa kortnummer.\n");
                }
                break;
            }

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