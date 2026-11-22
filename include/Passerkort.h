#ifndef PASSERKORT_H
#define PASSERKORT_H

#ifndef PASSERKORT_H
#define PASSERKORT_H

typedef enum {
    BEHORIGHET_INGEN = 0,
    BEHORIGHET_AKTIV = 1
} Behorighet;

typedef struct {
    char kortnummer[20];
    Behorighet behorighet;
    char datum[20];
    Passerkort *kort;
} Passerkort;

#endif