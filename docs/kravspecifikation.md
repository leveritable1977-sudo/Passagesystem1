Kravspecifikation – Passagesystem (Passagesystem1)
1. Syfte och omfattning
Detta dokument beskriver kraven för ett modulärt passagesystem skrivet i C. Systemet hanterar registrerade passerkort, behörighetskontroller, dörrstyrning med statuslampa (GRÖN, RÖD, SLÄCKT) samt filpersistens i kortregister.txt utan globala variabler. Projektet är uppdelat i modulerna Passerkort, Kortlista, door, safeinput och main.c.

2. Funktionella och icke-funktionella krav
REQ 01 – Kortnummer som text: Kortnummer ska lagras som text (char[]) för att bevara eventuella inledande nollor, till exempel "00123" eller "12345".

REQ 02 – Kortinnehåll: Varje passerkort ska innehålla uppgifter om kortnummer, behörighetsstatus (aktiv/inaktiv) samt registreringsdatum.

REQ 03 – Textlängder och buffertsäkerhet: Textfält ska ha tydliga maxlängder (KORTNUMMER_MAX, DATUM_MAX eller motsvarande konstanter i Passerkort.h) för att undvika buffertspill och säkerställa att minnesgränser inte överskrids.

REQ 04 – Structs och dynamisk kortlista: Programmet ska använda struct för att representera passerkort (Passerkort) och den dynamiska kortlistan/systemtillståndet (Kortlista), med dynamisk heap-allokering och storleksökning vid behov.

REQ 05 – Inga globala variabler: Programmet ska inte använda globala variabler. Tillstånd och data (Kortlista) ska hanteras lokalt i main() och skickas mellan funktioner via parametrar och pekare (Kortlista * och const Kortlista *). const ska användas när data endast behöver läsas.

REQ 06 – Säker inmatning: All inmatning från användaren (menyval, kortnummer, datum och text) ska hanteras säkert via safeinput (las_rad, las_heltal eller motsvarande funktioner) så att ogiltig inmatning eller överlånga rader inte orsakar krascher eller oändliga loopar.

REQ 07 – Öppna dörren på distans: Programmet ska kunna öppna dörren på distans via ett menyval och anropa oppna_dorr_pa_distans i modulen door. Funktionen ska skriva ut statuslampan (GRÖN, SLÄCKT) och använda sleep för att simulera att dörren är öppen innan den återgår till släckt läge.

REQ 08 – Lista samtliga kort: Programmet ska kunna visa samtliga registrerade kort med kortnummer, behörighet och datum via en läsande pekare (const Kortlista *).

REQ 09 – Lägg till kort: Programmet ska kunna registrera nya kort i listan. Indata ska valideras innan kortet sparas, dubbletter av kortnummer ska förhindras och listan ska kunna utökas dynamiskt vid behov.

REQ 10 – Ändra behörighet: Programmet ska kunna ändra behörigheten för ett befintligt kort (aktivera eller inaktivera behörighet) utan att radera kortet ur listan.

REQ 11 – Simulera skanning: Programmet ska kunna simulera en kortskanning genom att söka efter ett angivet kortnummer, kontrollera om kortet finns registrerat och har aktiv behörighet samt visa skanningsresultat och statuslampa (GRÖN vid godkänd passage, RÖD vid nekad passage eller okänt kort).

REQ 12 – Filhantering (kortregister.txt): Programmet ska kunna läsa in befintliga kort från kortregister.txt vid start (ladda_kort) och spara kortregistret till kortregister.txt (spara_kort) i formatet kortnummer;behorighet;datum med Unix-radslut (\n).

REQ 13 – Avsluta programmet kontrollerat: Programmet ska kunna avslutas på ett kontrollerat sätt via menyn. Huvudloopen ska avslutas rent, kortregistret ska sparas till kortregister.txt och allt allokerat heap-minne ska frigöras utan minnesläckor.


## 3. Översiktstabell – Hur kraven hänger ihop

| Område | Krav | Hur de hänger ihop |
| :--- | :--- | :--- |
| Arkitektur | REQ 05 | Ingen global data; `Kortlista *` och `const Kortlista *` skickas mellan moduler. |
| Datastruktur & minne | REQ 03–04, 13 | `Passerkort` och `Kortlista` styr fält, maxlängder, dynamisk allokering och frigöring. |
| Inmatning | REQ 06, 09–11 | `safeinput` skyddar inläsning av menyval, kortnummer och datum. |
| Registrering | REQ 01–04, 06, 09 | Kortnummer sparas som text, valideras, dubblettkontrolleras och läggs till. |
| Visning | REQ 02, 05, 08 | Läser kortdata med `const Kortlista *` och skriver ut hela listan. |
| Skanning & dörrstyrning | REQ 01, 07, 11 | Skanning visar `GRÖN`/`RÖD`; distansöppning (`oppna_dorr_pa_distans`) visar `GRÖN`, pausar med `sleep` och går till `SLÄCKT`. |
| Behörighet | REQ 02, 05, 10 | Växlar aktiv/inaktiv behörighet på befintligt kort utan att ta bort posten. |
| Filhantering | REQ 01–02, 04, 12 | Läser in och sparar kort i `kortregister.txt` (`kortnummer;behorighet;datum`). |
| Avslutning | REQ 04–05, 12–13 | Avslutar loopen, sparar till `kortregister.txt` och frigör allt heap-minne. |





4. Sammanfattning
Systemet är uppbyggt i tre tydliga steg:

Grund och säkerhet (REQ 01–06): Kortnummer sparas som text med fasta maxlängder, Passerkort och Kortlista hanteras utan globala variabler med const där data bara läses, och safeinput skyddar all användarinmatning.

Kärnfunktioner och persistens (REQ 07–12): Användaren kan lista kort, lägga till kort utan dubbletter, ändra behörighet, simulera skanning, öppna dörr på distans med oppna_dorr_pa_distans och spara/läsa data i kortregister.txt.

Kontrollerad avslutning (REQ 13): Programmet lämnar huvudloopen på ett ordnat sätt, sparar tillståndet till kortregister.txt och frigör allokerat heap-minne så att bygget och körningen förblir stabila och fria från minnesläckor.