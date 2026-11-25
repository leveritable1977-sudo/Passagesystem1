Markdown
# Passagesystem1

Ett C-baserat passersystem utvecklat som ett strukturerat projekt med fokus på säker inmatning, dynamisk minneshantering, filpersistens, modulär arkitektur och god källkodsstruktur utan globala variabler.

---

## 📂 Projektstruktur

Projektet är uppdelat i en tydlig katalogstruktur för att skilja på källkod, header-filer, dokumentation och kompilerade filer:

```text
Passagesystem1/
├── include/       # Header-filer (Passerkort.h, Kortlista.h, door.h, safeinput.h)
├── src/           # Källkodsfiler (main.c, passerkort.c, Kortlista.c, door.c, safeinput.c)
├── docs/          # Kravspecifikation, designdokument, testfall och spårbarhetsmatris
├── build/         # Kompilerade objektfiler (*.o) och körbar binär (ignoreras av Git)
├── .gitignore     # Konfigurationsfil för Git (exkluderar build/ och lokal testdata)
├── README.md      # Projektbeskrivning, bygg- och körinstruktioner
└── Makefile       # Automatiserad byggfil för kompilering och länkning med gcc
🧩 Moduler och ansvar
Passerkort (Passerkort.h / passerkort.c) – Datatyper, konstanter och funktioner för passerkort, behörighetsstatus och validering.

Kortlista (Kortlista.h / Kortlista.c) – Dynamisk minneshantering av kortlistan samt inläsning och sparning mot fil (kortregister.txt).

door (door.h / door.c) – Dörrkontroll, behörighetskontroll vid passage och fjärröppning av dörr.

safeinput (safeinput.h / safeinput.c) – Säker rad- och heltalsinmatning från användaren.

main.c – Huvudmeny och styrning av programflödet.

🛠️ Bygg- och körinstruktioner
Bygg programmet från projektroten med make (eller bygg om från grunden och rensa byggfiler med make clean):

Bash
make clean && make
make clean
Kör den färdigbyggda binären från projektroten:

Bash
./build/passagesystem