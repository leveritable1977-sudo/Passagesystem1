# Passagesystem1

Ett C-baserat passersystem utvecklat som ett strukturerat projekt med fokus på säker inmatning, dynamisk minneshantering, modulär arkitektur och god källkodsstruktur utan globala variabler.

---

## 📂 Projektstruktur

Projektet är uppdelat i en tydlig katalogstruktur för att skilja på källkod, header-filer, dokumentation och kompilerade filer:

```text
Passagesystem1/
├── include/       # Header-filer (Passerkort.h, Kortlista.h)
├── src/           # Källkodsfiler (main.c, passerkort.c, Kortlista.c)
├── docs/          # Kravspecifikationer, testfall och spårbarhetsmatris
├── build/         # Kompilerade objektfiler och binärer (ignoreras av Git)
├── .gitignore     # Konfigurationsfil för Git (exkluderar build/)
├── README.md      # Projektbeskrivning, bygg- och körinstruktioner
└── Makefile       # Automatiserad byggfil för kompilering med gcc
🛠️ Bygg- och körinstruktioner
Bygg programmet från projektroten med make (och rensa byggfiler vid behov med make clean):

Bash
make
make clean
Kör den färdigbyggda binären från projektroten:

Bash
./build/passagesystem