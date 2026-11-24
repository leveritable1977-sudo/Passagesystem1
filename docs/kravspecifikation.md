Markdown
# Kravspecifikation – Passagesystem (`passagesystem`)

## 1. Syfte och omfattning
Detta dokument beskriver kraven för ett modulärt passagesystem skrivet i C. Systemet hanterar registrerade passerkort, behörighetskontroller, distansöppning av dörr samt filpersistens utan globala variabler. Gränssnittsutskrifter (`printf`) hanteras i `main.c` medan modulerna ansvarar för datamodell, list- och filhantering samt dörr- och passagekontroll.

## 2. Funktionella och icke-funktionella krav

### REQ 01 – Kortnummer som text
Kortnummer ska lagras som text (`char[]`) för att bevara eventuella inledande nollor, till exempel `"01234"` eller `"00123"`, och behandlas som strängar vid sökning och jämförelse.

### REQ 02 – Kortinnehåll
Varje kort ska innehålla information om kortnummer, behörighetsstatus (`Aktiv` / `Ingen`) och registreringsdatum.

### REQ 03 – Textlängder och buffertsäkerhet
Textfält i kortposten och inmatningsbuffertar ska ha definierade maxlängder (`KORTNUMMER_MAX`, `DATUM_MAX` samt begränsad inmatning via `las_rad`) för att undvika buffertspill och säkerställa att minnesgränser inte överskrids.

### REQ 04 – Structs och dynamisk lista
Programmet ska använda `struct` för att organisera informationen om varje passerkort (`Passerkort`) samt samlingen/tillståndet för kortregistret (`Kortlista`) med dynamisk minnesallokering (`malloc`, `realloc`, `free`) och kontroll av returvärden vid allokering.

### REQ 05 – Inga globala variabler och tydlig ansvarsfördelning
Programmet ska inte använda globala variabler. Systemets tillstånd (`Kortlista`) ska skapas lokalt i `main()` och skickas mellan funktioner via pekare (`Kortlista *` och `const Kortlista *`), med `const` vid läsning. Kärnlogiken ska returnera status eller resultat till `main.c`, som ansvarar för meny- och statusutskrifter.

### REQ 06 – Öppna dörren på distans
Programmet ska kunna öppna dörren på distans via ett menyval genom `oppna_dorr_pa_distans()`. Funktionen returnerar resultat/status till `main.c`, som skriver ut resultatet i terminalen.

### REQ 07 – Lista samtliga kort
Programmet ska kunna läsa samtliga registrerade kort via `const Kortlista *` och presentera kortnummer, behörighet och registreringsdatum i `main.c` (`visa_kort`).

### REQ 08 – Lägg till kort
Programmet ska kunna registrera nya kort via `lagg_till_kort`. Indata ska valideras, dubbletter av kortnummer ska förhindras och listan ska växa dynamiskt vid behov.

### REQ 09 – Ändra behörighet
Programmet ska kunna ändra behörigheten för ett befintligt kort (`andra_behorighet`) genom att ge eller återkalla behörighet (`Aktiv` / `Ingen`) utan att radera kortet ur listan.

### REQ 10 – Simulera kortskanning och passagekontroll
Programmet ska kunna simulera en kortskanning (`hantera_kortskanning` i `main.c` i samspel med `kontrollera_passage` i `door.c`) genom att söka efter angivet kortnummer och returnera en tydlig statuskod (`PassageResultat`, såsom `PASSAGE_BEVILJAD`, `PASSAGE_NEKAD_INAKTIV`, `PASSAGE_NEKAD_EJ_REGISTRERAT` och `PASSAGE_NEKAD_OGILTIG_INMATA`). `main.c` skriver ut motsvarande besked för användaren.

### REQ 11 – Filhantering
Programmet ska kunna läsa in befintliga kort från registerfilen vid start (`ladda_kort`) och spara uppdaterat kortregister (`spara_kort`) så att kort och behörigheter bevaras mellan körningar.

### REQ 12 – Avsluta programmet kontrollerat
Programmet ska kunna avslutas på ett kontrollerat sätt med en iterativ huvudloop (ingen okontrollerad rekursion) när användaren väljer att avsluta via menyn, spara data och frigöra allokerat heap-minne innan programmet avslutas.

## 3. Översiktstabell – Hur kraven hänger ihop

| Område | Krav | Hur de hänger ihop |
| :--- | :--- | :--- |
| Arkitektur | REQ 05 | Ingen global data; `Kortlista *` och `const Kortlista *` skickas från `main()`. `printf` sker i `main.c`. |
| Datastruktur | REQ 02–04 | `Passerkort` och `Kortlista` styr fält, maxlängder och dynamisk minneshantering. |
| Registrering | REQ 01, 04, 08 | Kortnummer sparas som text, valideras och läggs till utan dubbletter. |
| Visning | REQ 02, 05, 07 | Läser kortdata via `const Kortlista *` och skriver ut i `main.c`. |
| Skanning | REQ 01, 05, 10 | Jämför kortnummer som text via `kontrollera_passage` och returnerar `PassageResultat` till `main.c`. |
| Distansöppning | REQ 05, 06 | `oppna_dorr_pa_distans()` returnerar utfall och `main.c` skriver ut statusmeddelandet. |
| Behörighet | REQ 02–05, 09 | Uppdaterar behörighet på befintligt kort utan att ta bort det. |
| Filhantering | REQ 01–02, 04, 11 | Läser in (`ladda_kort`) och sparar (`spara_kort`) kortregistret mellan körningar. |
| Avslutning | REQ 04–05, 11–12 | Avslutar den iterativa menyloopen, sparar data och frigör heap-minne. |

## 4. Sammanfattning
Programmets uppbyggnad kan ses som en kedja:

* **REQ 01–05:** Grundstruktur med `Passerkort` och `Kortlista`, textfält med maxlängder, pekare utan globala variabler och separation mellan logik och utskrift.
* **REQ 06–11:** Kärnflöden för distansöppning, visning, registrering, behörighetsändring, kortskanning med `PassageResultat` samt inläsning och sparning mot fil.
* **REQ 12:** Kontrollerad avslutning av den iterativa menyloopen, sparning och frigöring av heap-minne.

Tillsammans skapar kraven ett modulärt och spårbart system som går att bygga med kompilatorvarningar aktiverade och verifiera med tydliga testfall.