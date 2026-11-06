Här är en sammanställning av de 5 punkter för kravspecifikationen :
1) kortnummer blir en text som innehåller nollor.

2. Varje kort ska innehålla kortnummer, behörighetsstatus, och registreringsdatum.

3. Man väljer själv rimliga maximala längder för textfält som lagras i varje kort.

4. Vi använder en eller flera structs för data insamling.

5. Globala variabler får inte användas.

Programmet ska innehålla en återkommande huvudmeny med följande funktioner.
1.	Öppna dörren på distans. Programmet visar grön status i tre sekunder och återgår därefter till släckt status.
2.	Lista samtliga kort. För varje kort visas kortnummer, om kortet har behörighet, och registreringsdatum.
3.	Lägg till ett nytt kort. Samma kortnummer får inte registreras mer än en gång.
4.	Ändra behörighet för ett befintligt kort. Det ska gå att ge och återkalla behörighet utan att ta bort kortet.
5.	Simulera en kortskanning. Ett behörigt kort ger grön status, ett registrerat kort utan behörighet ger röd status, och ett okänt kort ger röd status tillsammans med ett tydligt meddelande.
6.	Avsluta programmet kontrollerat.