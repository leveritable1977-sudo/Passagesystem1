
Testprotokoll – Testfall och verifiering
TC-01 – Specialfall: Kortnummer med inledande nollor
Krav: REQ 01, REQ 02, REQ 03 och REQ 07.

Test / Indata: Ett kort registreras med kortnummer "00123", behörighet 1 och datum "2026-11-08".

Förväntat resultat: Programmet ska spara och visa kortnumret exakt som "00123". De inledande nollorna får inte försvinna eller ändras. Även behörighet och datum ska visas korrekt.

Syfte: Testet kontrollerar att kortnumret lagras som text och inte omvandlas till ett heltal. Det säkerställer att REQ 01 uppfylls.
