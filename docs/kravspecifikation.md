Här är en sammanställning av de 5 punkter för kravspecifikationen :
REQ-01 : kortnummer blir en text som innehåller nollor.

Req 02: Varje kort ska innehålla kortnummer, behörighetsstatus, och registreringsdatum.

Req 03: Man väljer själv rimliga maximala längder för textfält som lagras i varje kort.

Req 04:  Vi använder en eller flera structs för data insamling.

Req 05:  Globala variabler får inte användas.

Programmet ska innehålla en återkommande huvudmeny med följande funktioner.
Req 06:	Öppna dörren på distans. Programmet visar grön status i tre sekunder och återgår därefter till släckt status.
Req 07 :	Lista samtliga kort. För varje kort visas kortnummer, om kortet har behörighet, och registreringsdatum.
Req 08:	Lägg till ett nytt kort. Samma kortnummer får inte registreras mer än en gång.
Req 09:	Ändra behörighet för ett befintligt kort. Det ska gå att ge och återkalla behörighet utan att ta bort kortet.
Req 10:	Simulera en kortskanning. Ett behörigt kort ger grön status, ett registrerat kort utan behörighet ger röd status, och ett okänt kort ger röd status tillsammans med ett tydligt meddelande.
Req 11:	Avsluta programmet kontrollerat.