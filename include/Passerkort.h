#ifndef PASSERKORT_H
#define PASSERKORT_H

#include <stddef.h>

#define KORTNUMMER_MAX 6
#define DATUM_MAX 11
#define START_KAPACITET 4

typedef enum {
    BEHORIGHET_INGEN = 0,
    BEHORIGHET_AKTIV = 1
} Behorighet;

typedef struct {
    char kortnummer[KORTNUMMER_MAX];
    Behorighet behorighet;
    char datum[DATUM_MAX];
} Passerkort;

typedef struct {
    Passerkort *kort;
    size_t antal;
    size_t kapacitet;
    const char *filnamn;
} Kortlista;

const char *behorighet_till_text(Behorighet status);
int giltigt_kortnummer(const char *kortnummer);
void initiera_kort(Passerkort *kort, const char *kortnummer, Behorighet status, const char *datum);

#endif