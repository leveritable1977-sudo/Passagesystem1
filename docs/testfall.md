Här är 5. Testfall – Alla 3 varianter av TC-01 anpassad i ren Markdown så att du kan klistra in den direkt i en .md-fil i Visual Studio Code utan trasiga kodblock eller tabellrader:Markdown## 5. Testfall – Alla 3 varianter av TC-01

### Variant 1: Löpande textformat

**TC-01 – Specialfall: Kortnummer med inledande nollor**

- **Krav:** REQ 01, REQ 02, REQ 03, REQ 05 och REQ 07.
- **Design / Funktion (Funktionskontrakt):** Följande funktioner används för att implementera och testa kravet utan globala variabler (`REQ 05`):

```c
int add_card_interactive(AccessSystem *sys);
/* REQ 07 & REQ 05: Visar samtliga kort (använder const då data enbart läses) */
void list_cards(const AccessSystem *sys);
Test / Indata: Funktionen add_card_interactive(AccessSystem *sys) används för att registrera ett kort med kortnummer "00123", behörighet 1 och datum "2026-11-08". Därefter anropas list_cards(&sys) för att skriva ut informationen.
Förväntat resultat: Programmet ska spara och visa kortnumret exakt som "00123". Även behörighet (1) och datum ("2026-11-08") ska visas korrekt.
Syfte: Testet kontrollerar att funktionskontraktet hanterar kortnumret som text och inte omvandlar det till ett heltal, vilket säkerställer att REQ 01 och REQ 05 uppfylls.


### Variant 2: Tabellformat

| Testkomponent | Beskrivning / Värde |
| --- | --- |
| Test-ID & Namn | TC-01 – Specialfall: Kortnummer med inledande nollor |
| Krav | REQ 01, REQ 02, REQ 03, REQ 05, REQ 07 |
| Funktionskontrakt | int add_card_interactive(AccessSystem *sys); och void list_cards(const AccessSystem *sys); |
| Test / Indata | Ett kort registreras med add_card_interactive(&sys) med kortnummer "00123", behörighet 1 och datum "2026-11-08", varefter list_cards(&sys) anropas. |
| Förväntat resultat | Programmet ska spara och visa kortnumret exakt som "00123", tillsammans med behörighet (1) och datum ("2026-11-08"). |
| Syfte | Säkerställer att kortnummer sparas som text (char[]), att const används vid läsning och att REQ 01 och REQ 05 uppfylls. |

Variant 3: PunktlisteformatTC-01 – Specialfall: Kortnummer med inledande nollorKrav: REQ 01, REQ 02, REQ 03, REQ 05 och REQ 07.Design / Funktion (Kontrakt): Följande funktioner används för att implementera och testa kravet utan globala variabler (REQ 05):Cint add_card_interactive(AccessSystem *sys);
/* REQ 07 & REQ 05: Visar samtliga kort (använder const då data enbart läses) */
void list_cards(const AccessSystem *sys);
Test / Indata: Ett kort registreras via add_card_interactive(&sys) med kortnummer "00123", behörighet 1 och datum "2026-11-08", och därefter anropas list_cards(&sys).Förväntat resultat: Programmet ska spara och visa kortnumret exakt som "00123", tillsammans med behörighet (1) och datum ("2026-11-08").Syfte: Testet kontrollerar att kortnummer hanteras som text (char[]), att add_card_interactive och list_cards tar AccessSystem via pekare (const vid läsning) och att REQ 01 och REQ 05 uppfylls.

