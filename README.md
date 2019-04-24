# elte-ik-orsi-1-beadando-reloaded
Első beadandó az ELTE IK Osztott Rendszerek Implementációja és Sepcifikációja (ORSI) tárgyához.
A második beadandó az elsőre épül. Lásd: [ITT](https://github.com/SandorBalazsHU/elte-ik-orsi-1-beadando-reloaded)

# Leírás

## Keretsztori:
A civilizációk megalapítását követően már elérkezett az idő, hogy az egyes államok az alapvető közigazgatási intézkedések után az ott lakók kényelmét - illetve a logisztikai problémákat is megoldják. Ennek megvalósulása két új repülőtérben fog kiteljesedni, ám annak eldöntése, hogy pontosan hol is épüljön, nem volt triviális feladat.

Mivel demokratikus úton nem tudtak egyezségre jutni (mivel minden államfő a saját országát akarta elsőnek), ismét a te segítségedet kérték, hogy objektív módon adj megoldást a problémára. Arra jutottál, hogy a legjobb módszer az első repülőjárat kijelölésére legyen egy gazdasági szempontokat is (üzemanyag) figyelembe vevő tényező, ez pedig a távolságot veszi alapul. Mivel az első repterek szimbolikus jelleggel bírnak, ezért nagy volt a nyomás rajtad, de végül sikerült mindenkit meggyőznöd ahhoz, hogy erre a legjobb módszer a két, egymáshoz legközelebb eső város közötti légiforgalom elindítása.

Ahhoz, hogy ne kelljen minden egyes várost minden másikkal párba állítani (mely rengeteg időt elvisz), egy másik, kevésbé triviális algoritmus alapján döntöttél a kiindulási és érkezési helyszínekről. Hogy tovább növeld a hatékonyságodat, az így kapott módszert párhuzamosítottad is, hogy mégjobb hatásfokkal dolgozhass.

## A megoldandó probléma tehát a következő:

A bemeneti fájlban (world.map) elsőként egy hexagonális (hatszögletű) rácson alapuló világ térképe található. A térképnél esetén feltesszük, hogy annak “hasznos része” az, amit a fájlból tudunk beolvasni, az összes, fájlban nem szereplő mezőre a világot körülölelő tengerként tekintünk.

A térkép hasznos részéhez meg van adva hány sorból és hány oszlopból áll (N x M), ezt követik az egyes mezők azonosítói.

A korábbiak alapján az összes civilizáció már választott magának fővárost, így ezeket is a térképből tudjuk kiolvasni (11-es szám jelzi a városok helyét).

A feladatunk meghatározni, hogy melyik két város van a legközelebb egymáshoz, hogy így az első hivatalos légitársaság megkezdhesse a működését! Az így kiszámított eredményt (a kiindulási és érkezési koordináta alapján) írjuk ki az output.txt fájlba!

Tekintve, hogy egy-egy ilyen számítás sok időt is igénybe vehet ( O(n^2) ), ezért a megoldást párhuzamos módon készítjük el, melyben egy optimalizált algoritmust fogunk tovább gyorsítani párhuzamos futással felturbózva azt ( O(n log(n)) )!

### Az inputfájl felépítése az alábbi:

Az inputfájl felépítése az alábbi:

Az első sorban két nemnegatív egész szám olvasható (jelölje ezt N és M), ezt követően egy N x M méretű, azaz N sorból és M oszlopból felépített világ térképe.

Az ezt következő N sor a térkép egy-egy sorának reprezentációját tartalmazza, pozitív egész számokat az [0..11] intervallumból szóközzel tagolva.
Feltehetjük, hogy az input fájl a fent leírtaknak megfelelően van kitöltve, és nem található benne pl. negatív, valós vagy olyan szám, ami nem felel meg mezőknek. Feltehető továbbá, hogy legalább két város található a térképen, és ezek nem egy mezőre esnek.

A program olvassa be a térképet (a már implementált módon), majd hívja meg annak a get_shortest_flightpath() metódusát. Az így kapott út kiindulási és érkezési koordinátáit az output.txt fájlba írjuk ki!

#### Egy példa bemenet (world.map):

```
6 7
4 4 4 4 4 4 4
4 11 11 4 5 5 4
4 4 1 9 4 4 5
4 8 4 6 4 0 4
4 4 8 4 11 2 2
4 4 4 4 9 4 11
```

#### Az ehhez tartozó elvárt kimenet (output.txt):

```
From: (1,1)
To: (1,2)
```

A kapott út kiindulási városa legyen az, melynek pozíciója “kisebb” a másikénál (a<b, ha a.x<b.x, vagy a.x==b.x && a.y<=b.y). 

#### A fenti térkép vizuális megjelenítése és segítség a fenti térkép indexeléséhez:

##### Segítség a fenti térkép indexeléséhez:
<p align="center">
  <img src="https://github.com/SandorBalazsHU/elte-ik-orsi-2-beadando-reloaded/raw/master/img/map_sample.jpg">
</p>

##### Irányok:
<p align="center">
  <img src="https://github.com/SandorBalazsHU/elte-ik-orsi-2-beadando-reloaded/raw/master/img/directions.gif">
</p>

##### A térkép érdemleges részének indexelési módja
<p align="center">
  <img src="https://github.com/SandorBalazsHU/elte-ik-orsi-2-beadando-reloaded/raw/master/img/map_indexing.jpg">
</p>


## Az implementációs feladat

A feladat megoldásához kiindulásnak [innen](https://github.com/SandorBalazsHU/elte-ik-orsi-2-beadando-reloaded/raw/master/kiindulas.zip) tudtok letölteni egy ZIP állományt. Ebben három fájlt találtok - egy types.hpp és egy impl.cpp nevű fájlt.

A types.hpp fájlnak tartalmán nem kell változtatni - ezt csupán érdemes nagyjából átnézni, hogy mi minden található benne - a lentebbi segítségben található metódusok és osztályok prototípusát / definícióját tartalmazza.

A programozási feladat első része az impl.cpp fájlban található függvények rendes implementációja (működésüket lásd lejjebb). Ennek nagy részét az első beadandóhoz mindenki implementálta már, így elég a megfelelő komment rész alatt található függvényeket megvalósítani az előző fájlt folytatva.

## Segítség a megoldáshoz:

### Az egyes, (második feladat esetén) implementálandó függvények rövid működése:

A **Map::find_cities()** függvény a feltölti a cities_ halmazt az eltárolt térkép alapján a megfelelő koordinátákkal.
A **Map::get_cities()** az előbbi halmaz gettereként működik.
Az **alapmezők (FIELD) halmaza** egy új értékkel bővült: ez a CITY, 11-es sorszámmal, 10 értékkel. A későbbiekben ezekre is szükség lesz, kezeljük le a megfelelő függvényekben az új értéket.
A **Map::set_tile()** feladata karbantartani a cities_ halmazt, ha egy mező értékét városra módosítjuk, akkor az jelenjen meg a cities_ halmazban! Ha a felülírt mezőn eredetileg város állt, akkor távolítsuk el onnan.
A **Map::get_length(..)** egy repülési út hosszát adja meg (a kiindulási és az érkezési város/mező távolsága).
A **Map::get_distance(..)** függvény két mező távolságát adja meg. Az egyszerűség kedvéért ezt a távolságot definiáljuk a két mező koordinátáiból kapott szakasz hosszaként! (Azaz a (1,1) és a (4,5) mezők 5 távolságban vannak egymástól - lásd: Pythagoras-tétel illetve koordináta-geometria, általános iskola 8-ik osztály.)
A **closest_brute_force(..)** függvény brute-force módon keresi meg egy (koordinátákat tartalmazó) vektor elemei közül azt a kettőt, amelyek a legközelebb esnek egymáshoz (pl. dupla for-ciklus).
A **Map::find_shortest(..)** a rekurzív függényünk, mely a DnC algoritmust fogja megvalósítani. A konkrét implementációja később olvasható.
A **Map::get_shortest_flightpath()** az előbb említett két függvényt felhasználva adja vissza a megfelelő városok párját (FlightPath).

Az utóbbi két függvény működése lejjebb olvasható.

#### A **get_shortest_flightpath()** függvény működése:

A *cities_* halmazból két, rendezett vektort készítünk. Az egyik x, a másik y koordináták alapján rendezve tartalmazza a *cities_*-ben található koordinátákat.
A függvény a find_shortest(..) függvényt hívja meg az így kapott két vektorra, és az abból kapott eredményt adja vissza saját válaszául is.

#### A **find_shortest(..)** függvény működése:

Ez a metódus lesz a rekurzív algoritmust érdemileg megtestesítő függvény. Két paramétere van, melyek ugyan azokat a koordinátákat tartalmazzák, csupán más sorrendben - az egyik x, a másik y alapján rendezve (x_cities és y_cities).

A(z egyik) vektor méretét jelölje a továbbiakban N.

Ha a kapott vektor(ok) kevesebb, mint 4 elemet tartalmaz(nak), akkor hívjuk meg arra a closest_brute_force(..) metódust (valamelyik) kapott vektorral, és az ebből kapott eredménnyel térjünk vissza (a rekurzió elvarrása).

##### Egyébként:

Osszuk két részre az x koordináták alapján rendezett vektort. A [0..(N/2)-1] intervallumból képezzük az egyik vektort, az [(N/2)..N) alapján pedig a másikat (on_left_x és on_right_x) (tehát felezzük meg, az első N/2 elem kerüljön az egyik, a másik adag a másik vektorba. Páratlan esetben kerüljön a jobb oldalhoz a plusz elem).
Jelölje a középső elem x koordinátáját middle_X (ez a második részvektor első eleme).
Készítsünk két másik vektort, melyben a az (y_cities) vektor elemeit járjuk be sorra véve azokat. Amelyeknek az x koordinátája kisebb-egyenlő, mint a middle_X érték, azokat az egyik, a többi pontot a másik vektorba tegyük (on_left_y és on_right_y).
Rekurzívan számoljuk ki a két részben a legközelebbi repülőutakat (find_shortest(on_left_x, on_left_y); valamint find_shortest(on_right_x, on_right_y);)!
A rekurzió egyik felét külön szálon indítsuk!
A kettő közül a kisebb távolságú utat jelölje min_path. Jó esetben ez jelöli a legkisebb távolságot számunkra (a két, fele akkora részekből számítva), ám lehetséges, hogy a végeredmény szempontjából kedvező eset egyik eleme a bal rész jobb szélén, a másik fele a jobb rész bal szélén található, amit a rekurzió pont félbe vágott. Emiatt meg kell még vizsgálni, hogy van e olyan páros, amik ide esnek és a távolságuk is kedvező számunkra.
Készítsünk még egy vektort, nevezze ezt stripe. Gyűjtsük ebbe össze az eredeti (pl. y_cities) vektorból azokat, amelyeknek az x koordinátájának a middle_X ponthoz képest vett távolsága kisebb, mint a min_path út hossza.
Ha ennek a vektornak van eleme, nézzük meg, hogy találunk e benne olyan párost, melynek a távolsága kisebb, mint a min_path értéke. Ha igen, ez a páros legyen az új min_path.
A rekurzió térjen vissza a min_path értékkel.

**Megjegyzés:** előfordulhat, hogy több, ugyan olyan távolságú utat találnánk, ilyen esetekben (matematikailag) bármelyik eredményt jó megoldásnak vehetjük. A BEAD-os tesztelésben (annak korlátai miatt) azonban nem fordulnak elő olyan tesztfájlok, melyekben több, azonos táv is szerepelne, így mindegy, hogy ilyen esetekben melyik megoldást választja a programotok.

#### Szálindítás:
Mivel saját osztályon belüli függvényt kell meghívni az új szál indításakor, ezért a “sima”, eddigi szintaxist a fordító nem fogja szeretni, mivel nem fogja tudni feloldani, hogy melyik objektumon akarjuk az adott függvényt meghívni. Ennek kiküszöbölésére az új szálon induló rekurziót az alábbi két hívás egyikével érdemes indítani:

```
//A this átadása a függvény mellé:
std::future<FlightPath> path = std::async( std::launch::async, &Map::find_shortest, this, std::cref(on_left_x), std::cref(on_left_y) );
//A lambdás változat:
std::future<FlightPath> path = std::async(std::launch::async, [&]() { return find_shortest(on_left_x, on_left_y); });
```

[A problémáról általánosságban](https://en.wikipedia.org/wiki/Closest_pair_of_points_problem) 

## Általános elvárások:
Fokozottan kérünk mindenkit, hogy a beadandó határidejét (április 26, 19:59) vegye figyelembe! Kérjük osszátok be az időtöket, hogy ne csússzatok le a határidőről semmi esetben sem! Ez után nem áll módunkban elfogadni megoldásokat, kifogástól és indoklástól függetlenül! (Szült a halam, nem tudtam beadni, de elküldöm emailben; pont feltöltöttem volna, de lezárt a BEAD, jó lesz facebookon?; Késett a vonat de majd behozom pendriveon úgy jó? Nem, nem lesz jó egyik esetben sem.)

Kérünk mindenkit, hogy olvassa el a BEAD-on a hozzászólásokat, amiket írunk neki, mielőtt újra és újra feltölti a megoldást, így elkerülhető, hogy feleslegesen terheljétek a szervert, és egy körben lehet a legtöbb hibát javítani.

A megoldásaitokat egyetlen ZIP fájlba tömörítve töltsétek fel! Kérünk benneteket, hogy csak a szükséges forrásfájl(oka)t rakjátok bele az állomány gyökerébe, teljes projektet, solutiont (.cbp, .sln, illetve az ezekhez tartozó többi fájl), object fájlokat, vagy közvetlenül futtatható állományt (a.exe, a.out, etc..) semmiképp sem!

A **beadandót binárisan értékeljük**, de ettől függetlenül fogtok kapni (valószínűleg) megjegyzéseket a megoldásotokra vonatkozóan.

Javítani bármennyiszer lehet, de a határidő szoros közeledtével egyre kisebb az esély rá, hogy lesz időnk megnézni azt.
Szeretnénk mindenkit megkérni, hogy az alábbiak vegye figyelembe a feltöltés során:

A main.cpp, impl.cpp és types.hpp fájlokat mellékeljétek a ZIPbe, de a types.hpp fájlon kérünk ne módosítsatok (ha nem muszáj)!
A fájlokat a ZIP gyökerébe helyezzétek el, tehát ne mappát tömörítsetek, csupán a fájlokat!

Értékelési megjegyzés: Az automata tesztelő elutasítja a megoldást, ha az nem fordult le (ennek okát is jelezni fogja). Amennyiben fordítható, lefuttatja több különböző inputra, és összeveti a megoldásodat az elvárt kimenetekkel. Ha mindegyik egyezik (a whitespacek között nem tesz különbséget, így mindegy, hogy a sorok végén van -e plusz szóköz vagy nincs, illetve sorvégi enter az utolsó bejegyzés után), akkor a BEADon átment a megoldásod. Ez után még valamelyik oktató is ellenőrzi a megoldást - a kódot átnézve, megjegyzéseket fűzve hozzá. Ha ez is rendben van, akkor elfogadottnak minősítjük a beadandót. Ha valami problémába ütközünk (vagy a BEADon nem megy át), akkor elutasításra kerül a megoldásod. Ennek okát részletezni fogjuk.

[Egyéb segítség](https://people.inf.elte.hu/mykeesg/index.php?page=orsi&year=18_19_2)

Az értékelési / kódolási guide szintén az előbbi linken érhető el (FAQ és követelmények).

Az automatikus tesztelés is hamarosan működni fog!

Ha hibát találtok a types.hpp fájlban, jelezzétek, hogy javíthassuk!