#include "Passerkort.h"

const char *behorighet_till_text(Behorighet status) {
    return (status == BEHORIGHET_AKTIV) ? "Aktiv" : "Ingen";
}