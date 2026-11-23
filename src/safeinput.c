#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "safeinput.h"

void rensa_rad(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* töm resten av raden */
    }
}

int las_rad(char *buffert, size_t storlek) {
    if (buffert == NULL || storlek == 0) {
        return 0;
    }

    if (fgets(buffert, (int)storlek, stdin) == NULL) {
        buffert[0] = '\0';
        return 0;
    }

    size_t langd = strlen(buffert);
    if (langd > 0 && buffert[langd - 1] == '\n') {
        buffert[langd - 1] = '\0';
    } else {
        rensa_rad();
    }

    return 1;
}

int las_heltal(int *varde) {
    char rad[64];
    char *slut = NULL;
    long tal;

    if (varde == NULL) {
        return 0;
    }

    if (!las_rad(rad, sizeof(rad)) || rad[0] == '\0') {
        return 0;
    }

    tal = strtol(rad, &slut, 10);
    if (slut == rad || *slut != '\0') {
        return 0;
    }

    *varde = (int)tal;
    return 1;
}