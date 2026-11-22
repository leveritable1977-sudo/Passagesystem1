#ifndef PASSERKORT_H
#define PASSERKORT_H

typedef struct {
    char kortnummer[10];
    char behorighet;
    char datum[11];
} Passerkort;

#endif