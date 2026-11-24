Markdown
## 5. Testfall – Normalfall och inledande nolla (01234)

### Steg 1: Första testutfallet – Kort `01234` med inaktiv behörighet (fel/avvikelse vid första test)

| Testkomponent | Beskrivning / Värde |
| --- | --- |
| Test-ID & Namn | TC-01a – Inledande nolla (`01234`) med inaktiv behörighet |
| Aktuella funktioner | `lagg_till_kort`, `visa_kort`, `kontrollera_passage` (`PassageResultat`) |
| Indata | Kortnummer `01234` registrerat med behörighet `0` (Ingen), testat via menyval 5 (Simulera en kortskanning). |
| Faktiskt utfall (första test) | Kortnumret `01234` bevarade sin inledande nolla i listan (`Kortnummer: 01234`), men passage nekades (`PASSAGE_NEKAD_INAKTIV`) eftersom behörigheten var satt till `Ingen` (`0`). |
| Analys av felet / avvikelsen | Inledande nolla förlorades inte (kortnumret lagras som text), men jag hade satt inaktiv behörighet (`0`) i första testet när jag ville testa en godkänd passage med inledande nolla. |

### Steg 2: Uppföljning och rättning – Aktivering av `01234` samt jämförelse med normalfall `12345`

| Testkomponent | Beskrivning / Värde |
| --- | --- |
| Test-ID & Namn | TC-01b – Uppföljning: `01234` aktiverat samt normalfall `12345` |
| Aktuella funktioner | `andra_behorighet`, `spara_kort`, `ladda_kort`, `kontrollera_passage` |
| Indata / Åtgärd | Ändra behörighet för `01234` till `Aktiv` via menyval 4, spara till `kortregister.txt` och testa både `01234` och normalfallet `12345` via menyval 5. |
| Förväntat och verifierat resultat | `01234` visas med behållen inledande nolla (`01234`) och ger `PASSAGE_BEVILJAD` när det är aktivt; `12345` fungerar som normalfall (`PASSAGE_BEVILJAD`) när det är aktivt. |
| Syfte | Dokumentera hur en felaktig/ofullständig testkörning upptäcks, rättas och verifieras utan att tappa inledande nollor eller bryta filpersistensen. |