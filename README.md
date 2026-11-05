Markdown
# Passersystem

Ett C-baserat passersystem utvecklat som ett strukturerat projekt med fokus på säker inmatning, modulär arkitektur och god källkodsstruktur.

---

## 📂 Projektstruktur

Projektet är uppdelat i en tydlig katalogstruktur för att skilja på källkod, header-filer, dokumentation och kompilerade filer:
🛠️ Bygginstruktioner
Projektet levereras med en Makefile som automatiserar kompilering med gcc.

🚀 Körinstruktioner
När programmet har byggts framgångsrikt startar du det från terminalen genom att köra binären från roten:

```text
passagesystem/
├── src/           # Innehåller källkodsfiler (main.c, passerkort.c)
├── include/       # Innehåller header-filer (passerkort.h)
├── docs/          # Innehåller kravspecifikationer, tester och spårbarhet
├── build/         # Här hamnar kompilerade binärer (ignoreras av Git)
├── .gitignore     # Konfigurationsfil för Git (exkluderar build/)
├── README.md      # Projektbeskrivning, bygg- och körinstruktioner
└── Makefile       # Automatiserad byggfil för kompilering