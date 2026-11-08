

Här är hur hela TC-01 ser ut när vi väver in funktionsdeklarationen:

TC-01 – Specialfall: Kortnummer med inledande nollor
Krav: REQ 01, REQ 02, REQ 03, REQ 05 och REQ 07.

Design / Funktion (Funktionskontrakt):
Följande funktioner används för att implementera och testa kravet utan globala variabler (REQ 05):



// REQ 07 & REQ 05: Visar samtliga kort 
void list_cards();
Test / Indata:
Funktionen register_card() anropas med kortnummer "00123", behörighet 1 och datum "2026-11-08". Därefter anropas list_cards() för att skriva ut informationen.

Förväntat resultat:
Programmet ska spara och visa kortnumret exakt som "00123". Även behörighet (1) och datum ("2026-11-08") ska visas korrekt.


Syfte:
Testet kontrollerar att funktionskontraktet hanterar kortnumret som text och inte omvandlar det till ett heltal, vilket säkerställer att REQ 01 och REQ 05 uppfylls.

		
### TC-01 – Specialfall: Kortnummer med inledande nollor

* **Krav:** REQ 01, REQ 02, REQ 03, REQ 05, REQ 07
* **Design / Funktion (Kontrakt):**
  ```c
  // REQ 07 & REQ 05: Visar samtliga kort
  void list_cards();


| Testkomponent | Beskrivning / Värde |
| :--- | :--- |
| **Test-ID & Namn** | TC-01 – Specialfall: Kortnummer med inledande nollor |
| **Krav** | REQ 01, REQ 02, REQ 03, REQ 05, REQ 07 |
| **Design / Funktion (Kontrakt)** | <br>```c<br>// REQ 07 & REQ 05: Visar samtliga kort<br>void list_cards();<br>```<br> |
| **Test / Indata** |  Funktionen `list_cards()` anropas för att skriva ut informationen. |
| **Förväntat resultat** | Programmet ska spara och visa kortnumret exakt som `"00123"`. Även behörighet (`1`) och datum (`"2026-11-08"`) ska visas korrekt. |
| **Syfte** | Testet kontrollerar att funktionskontraktet hanterar kortnumret som text och inte omvandlar det till ett heltal, vilket säkerställer att REQ 01 och REQ 05 uppfylls. |





### TC-01 – Specialfall: Kortnummer med inledande nollor

* **Krav:** REQ 01, REQ 02, REQ 03, REQ 05 och REQ 07.
* **Design / Funktion (Kontrakt):**
  Följande funktioner används för att implementera och testa kravet utan globala variabler (**REQ 05**):
  ```c
 

  // REQ 07 & REQ 05: Visar samtliga kort (använder const då data enbart läses)
  void list_cards();