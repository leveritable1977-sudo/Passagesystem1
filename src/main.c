#include <stdio.h>
#include <stddef.h>
#include "Kortlista.h"
#include "door.h"

int main(void) {
    Passerkort *kort = NULL;
    size_t antal = 0;
    size_t kapacitet = 0;
    char testkort[20] = {0};

    init_kortlista(&kort, &antal, &kapacitet);

    if (lagg_till_kort(&kort, &antal, &kapacitet)) {
        visa_kort(kort, antal);

        printf("Ange kortnummer att testa vid dorren: ");
        if (scanf("%19s", testkort) == 1) {
            kontrollera_passage(kort, antal, testkort);
        }
    } else {
        visa_kort(kort, antal);
    }

    frigor_kortlista(&kort, &antal, &kapacitet);

    return 0;
}