## 4. Design

### Moduler i systemet

- **`safeinput` (`safeinput.h` / `safeinput.c`):** Hanterar säker textinmatning från `stdin` och inmatningsfel med `read_line` och `read_menu_choice`.
- **`door` (`door.h` / `door.c`):** Hanterar dörröppning på distans och utskrift av statuslampan (`GRÖN`, `RÖD`, `SLÄCKT`) samt paus med `sleep`.
- **`cards` (`cards.h` / `cards.c`):** Hanterar datastrukturerna `Card` och `AccessSystem`, dynamisk minnesallokering, kortoperationer och filhantering (`cards.dat`).
- **`main` (`main.c`):** Skapar `AccessSystem sys` lokalt, laddar kort från `cards.dat`, driver meny-loopen och frigör minnet vid avslut.

### Datastrukturer

- **`Card`:** Innehåller kortnummer som text (`char id[CARD_ID_MAX]`), behörighet (`int authorized`) och registreringsdatum (`char registered[DATE_MAX]`).
- **`AccessSystem`:** Håller dynamisk kortarray (`Card *cards`), antal kort (`size_t count`), kapacitet (`size_t capacity`) och filnamn (`const char *storage_file`), till exempel `cards.dat`.

### Huvudfunktioner

```c
int system_init(AccessSystem *sys, const char *filename);
void system_free(AccessSystem *sys);
int load_cards(AccessSystem *sys);
int save_cards(const AccessSystem *sys);

void door_open_remote(void);
void door_show_scan_result(const char *card_id, int found, int authorized);

void list_cards(const AccessSystem *sys);
int add_card_interactive(AccessSystem *sys);
int toggle_card_permission(AccessSystem *sys);
void simulate_card_scan(const AccessSystem *sys);