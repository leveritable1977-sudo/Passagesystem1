
1. Kravspecifikation
Req 01 – Kortnummer som text

Kortnummer ska lagras som text för att bevara eventuella inledande nollor, exempelvis "00123".

Req 02 – Kortinnehåll

Varje kort ska innehålla information om kortnummer, behörighet och datum.

Req 03 – Textlängder

Textfält ska ha bestämda maxlängder för att undvika att minnesgränser överskrids.

Req 04 – Structs

Programmet ska använda struct för att organisera informationen om varje kort i en gemensam datastruktur.

Req 05 – Inga globala variabler

Programmet ska inte använda globala variabler. Systemets tillstånd ska hanteras lokalt i main() och skickas mellan funktioner via parametrar och pekare. const ska användas när data endast behöver läsas.

Req 06 – Öppna dörren på distans

Programmet ska kunna öppna dörren på distans via ett menyval. Dörrstatus ska ändras till grön i tre sekunder och därefter återgå till släckt läge.

Req 07 – Lista samtliga kort

Programmet ska kunna visa samtliga registrerade kort med tillhörande kortnummer, behörighet och datum.

Req 08 – Lägg till kort

Programmet ska kunna registrera nya kort. Informationen ska valideras innan kortet sparas och dubbletter ska kontrolleras.

Req 09 – Ändra behörighet

Programmet ska kunna ändra behörigheten för ett befintligt kort genom att ge eller återkalla behörighet utan att radera kortet ur listan.

Req 10 – Simulera skanning

Programmet ska kunna simulera en kortskanning genom att söka efter ett angivet kortnummer och kontrollera om kortet finns registrerat samt visa relevant status.

Req 11 – Avsluta programmet kontrollerat

Programmet ska kunna avslutas på ett kontrollerat sätt när användaren väljer att avsluta via menyn. Programmets huvudloop ska avslutas korrekt och eventuellt allokerat minne ska frigöras.




2. Översiktstabell – Hur kraven hänger ihop
Område	Krav som samverkar	Samband
Arkitektur:	Req 05	Påverkar hela programmet och hur data skickas mellan funktioner.

Datastruktur:	Req 02, 03, 04	Bestämmer vilken information som lagras, hur den organiseras och hur mycket minne den får använda.

Registrering:	Req 01, 04, 08	Kortnummer sparas som text och ny kortinformation registreras i en struct.

Visning : 	Req 02, 07	Den sparade kortinformationen används för att visa alla kort.

Skanning : Req 01, 10	Kortnummer jämförs som text för att hitta rätt kort.

Dörrstyrning :	Req 05, 06, 10	Pekare används för att ändra dörrstatus och status kan visas i programmet.

Behörighet	: Req 02, 03, 04, 05, 09	Befintliga kort hittas och deras behörighet ändras utan att kortet raderas.

Avslutning:	Req 04, 05, 11	Programmet avslutas kontrollerat och eventuellt dynamiskt minne frigörs.

3. Sammanfattning :
Man kan se programmets uppbyggnad som en kedja:
Req 01–05  :Grundstruktur, datastruktur och lagring


Req 06–10 : Programmets funktioner: dörrstyrning, visning, registrering, behörighet och skanning


Req 11 : Kontrollerad avslutning av programmet


Slutsats: De första kraven skapar grunden för programmets datastruktur och arkitektur. Därefter använder de funktionella kraven denna grund för att hantera kort, behörigheter och dörrstyrning. Det sista kravet säkerställer att programmet kan avslutas på ett korrekt sätt. På så sätt bildar alla 11 krav tillsammans ett sammanhängande system.