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
Passerkort (Passerkort.h / passerkort.c) – Datatyper, konstanter (KORTNUMMER_MAX) och funktioner för passerkort, behörighetsstatus och validering av kortnummer (1–5 alfanumeriska tecken).

Kortlista (Kortlista.h / Kortlista.c) – Dynamisk minneshantering av kortlistan (malloc, realloc, free) samt inläsning och sparning mot fil (kortregister.txt), inklusive robust hantering av ogiltiga eller korrupta rader.

door (door.h / door.c) – Dörrkontroll, behörighetskontroll vid passage och fjärröppning av dörr.

safeinput (safeinput.h / safeinput.c) – Säker rad- och heltalsinmatning (las_rad, las_heltal, rensa_rad) med fgets och strtol utan scanf.

main.c – Huvudmeny, styrning av programflödet och presentation i terminalen.

🔒 Säker inmatning och buffertdesign
Separerad buffert- och längdgräns: KORTNUMMER_MAX är satt till 7 i include/Passerkort.h så att ett kortnummer på upp till 5 tecken (till exempel "01234") får plats tillsammans med radbrytning (\n) och nollterminering (\0) vid inläsning med fgets(). Tidigare buffertstorlek (6 byte) lämnade kvar \n i stdin vid 5-teckensinmatning.

Domänvalidering: giltigt_kortnummer() kontrollerar att längden är 1–5 tecken och att tecknen är giltiga innan inmatningen godkänns.

Skydd mot buffertspill och resttecken: las_rad() verifierar att radbrytning (\n) lästes in i bufferten. Om inmatningen är för lång töms överflödiga tecken från stdin med rensa_rad() och avvisas utan att påverka efterföljande menyval.

Inga globala variabler: Allt tillstånd hanteras lokalt och skickas via pekare (Kortlista * och const Kortlista *), med kompilering under strikta flaggor (-Wall -Wextra -Wpedantic).

🛠️ Bygg- och körinstruktioner
Bygg om programmet från grunden och rensa byggfiler med make:

Bash
make clean && make
make clean
Kör den färdigbyggda binären från projektroten:

Bash
./build/passagesystem

## 🧪 Testning

Bygg programmet med `make` och starta binären från projektroten för att verifiera huvudflöde, gränsfall och filpersistens (`kortregister.txt`):

1. **Lägga till och lista kort:** Testa giltiga kortnummer med 1–5 tecken (inklusive ledande nollor som `01234` och bokstäver som `ABC12`) och verifiera att listan uppdateras.
2. **Gränsfall och ogiltig inmatning:** Testa tomma strängar, för långa kortnummer (`ABC123`), ogiltiga tecken (`AB-1`), dubbletter, okända kort (`99999`), inaktiva kort samt felaktiga menyval utan att programmet kraschar eller lämnar resttecken i `stdin`.
3. **Ändra behörighet och dörrkontroll:** Växla behörighet mellan aktiv och ingen, kontrollera dörrstatus vid passageförsök och testa fjärröppning.
4. **Filpersistens och felaktiga filrader:** Avsluta programmet så kortregistret sparas i `kortregister.txt`, starta om och kontrollera att registret återställs. Testa även att `kortregister.txt` hanterar korrupta eller ogiltiga rader utan krasch.