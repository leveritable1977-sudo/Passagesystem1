

Kravspecifikation – Passagesystem (passagesystem)
1. Syfte och omfattning
Detta dokument beskriver kraven för ett modulärt passagesystem skrivet i C. Systemet hanterar registrerade passerkort, behörighetskontroller, dörrstyrning med statuslampa samt filpersistens i cards.dat utan globala variabler.

2. Funktionella och icke-funktionella krav
REQ 01 – Kortnummer som text
Kortnummer ska lagras som text (char[]) för att bevara eventuella inledande nollor, till exempel "00123".

REQ 02 – Kortinnehåll
Varje kort ska innehålla information om kortnummer, behörighet och registreringsdatum.

REQ 03 – Textlängder
Textfält ska ha bestämda maxlängder (CARD_ID_MAX, DATE_MAX) för att undvika buffertspill och säkerställa att minnesgränser inte överskrids.

REQ 04 – Structs
Programmet ska använda struct för att organisera informationen om varje kort (Card) samt systemets övergripande tillstånd (AccessSystem).

REQ 05 – Inga globala variabler
Programmet ska inte använda globala variabler. Systemets tillstånd ska hanteras lokalt i main() och skickas mellan funktioner via parametrar och pekare (AccessSystem *sys och const AccessSystem *sys). const ska användas när data endast behöver läsas.

REQ 06 – Öppna dörren på distans
Programmet ska kunna öppna dörren på distans via ett menyval. Funktionerna skriver ut statuslampan (GRÖN, SLÄCKT) och använder sleep för att simulera att dörren är öppen innan den återgår till släckt läge.

REQ 07 – Lista samtliga kort
Programmet ska kunna visa samtliga registrerade kort med tillhörande kortnummer, behörighet och datum via const AccessSystem *sys.

REQ 08 – Lägg till kort
Programmet ska kunna registrera nya kort via add_card_interactive(AccessSystem *sys). Informationen ska valideras innan kortet sparas och dubbletter ska kontrolleras.

REQ 09 – Ändra behörighet
Programmet ska kunna ändra behörigheten för ett befintligt kort (toggle_card_permission) genom att ge eller återkalla behörighet utan att radera kortet ur listan.

REQ 10 – Simulera skanning
Programmet ska kunna simulera en kortskanning (simulate_card_scan) genom att söka efter ett angivet kortnummer, kontrollera om kortet finns registrerat och skriva ut statuslampan (GRÖN eller RÖD) samt skanningsresultat.

REQ 11 – Filhantering (cards.dat)
Programmet ska kunna läsa in befintliga kort från cards.dat vid start (load_cards) och spara kortregistret till cards.dat vid avslut (save_cards).

REQ 12 – Avsluta programmet kontrollerat
Programmet ska kunna avslutas på ett kontrollerat sätt när användaren väljer att avsluta via menyn. Programmets huvudloop ska avslutas korrekt, data sparas till cards.dat och allokerat heap-minne ska frigöras (system_free).

3. Översiktstabell – Hur kraven hänger ihop

| Område | Krav | Hur de hänger ihop |
| :--- | :--- | :--- |
| Arkitektur | REQ 05 | Ingen global data; `sys` och `const sys` skickas mellan funktioner. |
| Datastruktur | REQ 02–04 | `Card` och `AccessSystem` styr fält, maxlängder och minne. |
| Registrering | REQ 01, 04, 08 | Kortnummer sparas som text, valideras och läggs till utan dubbletter. |
| Visning | REQ 02, 07 | Läser kortdata med `const AccessSystem *sys` och skriver ut listan. |
| Skanning | REQ 01, 10 | Jämför kortnummer som text och visar statuslampa (`GRÖN` / `RÖD`). |
| Dörrstyrning | REQ 06, 10 | Skriver statuslampan (`GRÖN`, `RÖD`, `SLÄCKT`) och pausar med `sleep`. |
| Behörighet | REQ 02–05, 09 | Växlar behörighet på befintligt kort utan att ta bort det. |
| Filhantering | REQ 01–02, 04, 11 | Läser in och sparar kortregistret i `cards.dat` mellan körningar. |
| Avslutning | REQ 04–05, 11–12 | Avslutar loopen, sparar till `cards.dat` och frigör minne. |

4. Sammanfattning
Programmets uppbyggnad kan ses som en kedja:

REQ 01–05: Grundstruktur, datastruktur, textlängder och pekare utan globala variabler.

REQ 06–11: Programmets funktioner: dörrstyrning med statuslampa och sleep, visning, registrering, behörighet, skanning och filhantering mot cards.dat.

REQ 12: Kontrollerad avslutning av programmet och frigöring av minne.

De första kraven skapar grunden för programmets datastruktur och arkitektur. Därefter använder de funktionella kraven och filhanteringen denna grund för att hantera kort, behörigheter och dörrstyrning. Det sista kravet säkerställer att programmet kan avslutas på ett korrekt sätt. Tillsammans bildar alla 12 krav ett sammanhängande system.