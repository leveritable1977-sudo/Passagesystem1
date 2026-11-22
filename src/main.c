#include <stdio.h>
#include <stddef.h>
#include "Kortlista.h"

int main(void) {
    Passerkort *kort = NULL;
    size_t antal = 0;
    size_t kapacitet = 0;

    init_kortlista(&kort, &antal, &kapacitet);
    visa_kort(kort, antal);
    frigor_kortlista(&kort, &antal, &kapacitet);

    return 0;
}