Markdown
## 4. Design

### Moduler i systemet

- **Inmatningsmodul (`safeinput.h` / `safeinput.c`):** Hanterar längdbegränsad och validerad text- och menyinmatning från `stdin` (till exempel `las_rad` och menyvalshantering) utan buffertspill.
- **Dörr- och passage modul (`include/door.h` / `src/door.c`):** Hanterar kärnlogik för distansöppning (`oppna_dorr_pa_distans`) och passagekontroll (`kontrollera_passage`) med statuskoder (`PassageResultat`) utan direkta gränssnittsutskrifter.
- **Kort- och listmodul (`include/Kortlista.h` / `src/Kortlista.c`):** Hanterar datastrukturerna `Passerkort` och `Kortlista`, dynamisk minnesallokering (`malloc`, `realloc`, `free`), kortoperationer (registrering, sökning, behörighetsändring) samt filinläsning och filsparning.
- **Huvudprogram (`src/main.c`):** Skapar `Kortlista` lokalt i `main()`, laddar kort vid start, driver den iterativa meny-loopen, tolkar returvärden och statuskoder med gränssnittsutskrifter (`printf`), sparar data samt frigör minnet vid avslut.

### Datastrukturer

- **`Passerkort`:** Innehåller kortnummer som text (`char kortnummer[KORTNUMMER_MAX]`), behörighetsstatus (`Aktiv` / `Ingen`) och registreringsdatum (`char datum[DATUM_MAX]`).
- **`Kortlista`:** Håller dynamisk kortarray (`Passerkort *kort`), aktuellt antal kort (`size_t antal`), allokerad kapacitet (`size_t kapacitet`) och sökväg/filnamn för registret (till exempel `kortregister.txt`).
- **`PassageResultat`:** Enum-typ i `include/door.h` som representerar utfallet av en passagekontroll (`PASSAGE_BEVILJAD`, `PASSAGE_NEKAD_INAKTIV`, `PASSAGE_NEKAD_EJ_REGISTRERAT`, `PASSAGE_NEKAD_OGILTIG_INMATA`).

### Huvudfunktioner

```c
int ladda_kort(Kortlista *lista, const char *filnamn);
int spara_kort(const Kortlista *lista, const char *filnamn);
void frigör_kortlista(Kortlista *lista);

int oppna_dorr_pa_distans(void);
PassageResultat kontrollera_passage(const Kortlista *lista, const char *kortnummer);

int lagg_till_kort(Kortlista *lista, /* parametrar */);
int andra_behorighet(Kortlista *lista, const char *kortnummer);
void visa_kort(const Kortlista *lista);