#ifndef PASSERKORT_H
#define PASSERKORT_H

typedef enum {
    BEHORIGHET_INGEN = 0,
    BEHORIGHET_AKTIV = 1
} Behorighet;

typedef struct Passerkort {
    char kortnummer[20];
    Behorighet behorighet;
    char datum[20];
    struct Passerkort *kort;
} Passerkort;

#endif