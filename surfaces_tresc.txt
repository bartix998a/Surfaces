Celem zadania jest zaimplementowanie funkcyjnej biblioteki obsługującej
trójwymiarowe powierzchnie R^2 -> R.

Do reprezentowania punktu na płaszczyźnie R^2 należy zdefiniować typ Point
przechowujący współrzędne punktu jako dwie niemodyfikowalne liczby rzeczywiste
reprezentowane za pomocą typu Real, który jest zdefiniowany w dostarczonym pliku
real.h. O typie Real zakładamy, że można na nim wykonywać takie same operacje
jak na wbudowanych w C++ typach zmiennoprzecinkowych.

Współrzędne punktu mogą być inicjowane jedynie w konstruktorze. Typ Point nie ma
konstruktora domyślnego. Z typem tym powinien być powiązany operator wysyłania
do strumienia wyjściowego współrzędnych punktu w postaci dwóch liczb
oddzielonych spacją.

Do reprezentowania powierzchni R^2 -> R należy zdefiniować typ Surface będący
funkcją z typu Point w typ Real.

W bibliotece powinny się znaleźć specjalne funkcje, których wynikiem jest
funkcja typu Point-> Real generująca pewne specyficzne powierzchnie:

// Generuje płaszczyznę f(x, y) = 0.
plain()

// Generuje powierzchnię f(x, y) = x.
slope()

// Generuje powierzchnię schodkową wzdłuż osi X o szerokości schodka s
// (domyślnie 1) i wysokości schodka 1. Dla 0 <= x < s mamy f(x, y) = 0,
// dla -s <= x < 0 mamy f(x, y) = -1 itd. Jeśli s <= 0, to f(x, y) = 0.
steps(s)

// Generuje powierzchnię, która jest szachownicą o szerokości kratki s
// (domyślnie 1). Dla 0 <= x < s mamy f(x, y) = 1, gdy 0 <= y < s
// oraz f(x, y) = 0, gdy s <= y < 2 * s itd. Jeśli s <= 0, to f(x, y) = 0.
checker(s)

// Generuje powierzchnię f(x, y) = x * x.
sqr()

// Generuje powierzchnię sinusoidalną względem argumentu x.
sin_wave()

// Generuje powierzchnię kosinusoidalną względem argumentu x.
cos_wave()

// Generuje powierzchnię z koncentrycznymi naprzemiennymi pasami szerokości s
// (domyślnie 1) o środku w punkcie (0, 0), gdzie f(x, y) = 1 w najbardziej
// wewnętrznym okręgu (łącznie z tym okręgiem). Jeśli s <= 0, to f(x, y) = 0.
rings(s)

// Generuje powierzchnię z elipsą o środku w punkcie (0, 0) o półosi długości
// a wzdłuż osi X (domyślnie 1) i o półosi długości b wzdłuż osi Y
// (domyślnie 1). Zachodzi f(x, y) = 1, gdy (x, y) leży wewnątrz lub na brzegu
// elipsy, zaś f(x, y) = 0, w. p.p. Jeśli a <= 0 lub b <= 0, to f(x, y) = 0.
ellipse(a, b)

// Generuje powierzchnię z prostokątem o środku w punkcie (0, 0) o brzegu
// długości 2a wzdłuż X (domyślnie a = 1) i o brzegu długości 2b wzdłuż osi Y
// (domyślnie b = 1), czyli f(x, y) = 1, gdy (x, y) leży wewnątrz lub na brzegu
// prostokąta, zaś f(x, y) = 0, w. p.p. Jeśli a <= 0 lub b <= 0, to f(x, y) = 0.
rectangle(a, b)

// Generuje powierzchnię z paskami o szerokości s, ułożonymi wzdłuż osi X,
// równoległymi do osi Y. Zachodzi f(x, y) = 1, gdy 0 < x <= s oraz f(x, y) = 0,
// gdy -s < x <= 0 itd. Jeśli s <= 0, to f(x, y) = 0.
stripes(s)

Biblioteka powinna również dawać możliwość wykonywania podstawowych modyfikacji
powierzchni. W tym celu powinna udostępniać następujące funkcje, których
wynikiem jest funkcja typu Point-> Real wykonująca poniższe transformacje:

// Obraca dziedzinę powierzchni o kąt wyrażony w stopniach.
rotate(f, deg)

// Przesuwa dziedzinę powierzchni o wektor v (typu Point).
translate(f, v)

// Skaluje dziedzinę powierzchni parą współczynników s (typu Point).
scale(f, s)

// Odwraca dziedzinę powierzchni, tzn. zamienia (x, y) na (y, x).
invert(f)

// Odbija dziedzinę powierzchni względem osi Y, tzn. zamienia x na -x.
flip(f)

// Mnoży wartości podanej powierzchni f przez podaną wartość c.
mul(f, c)

// Dodaje podaną wartość c do wartości podanej powierzchni f.
add(f, c)

Oprócz tego biblioteka powinna udostępniać następujące funkcje generyczne
(szablony):

// Oblicza wartość funkcji h(f1(p), ..., fs(p)).
// Wywołanie evaluate bez parametrów nie powinno się kompilować.
evaluate(h, f1, ..., fs)

// Generuje złożenie funkcji fs(...(f2(f1))...).
compose(f1, f2, ..., fs)

W implementacji  wyżej wymienionych funkcji i szablonów funkcji należy
wykorzystywać funkcje lambda języka C++.

Rozwiązanie powinno być zawarte w pliku surfaces.h.

Przykład użycia biblioteki składa się z plików example.cc, real.h, ps_plot.h,
ps_plot.cc. Oczekiwany wynik wykonania przykładu składa się z rysunków
w formacie PostScript zawartych w plikach plot*.ps.

Całość kompiluje się poleceniem

g++ -Wall -Wextra -O2 -std=c++20 *.cc

Plik z rozwiązaniem należy umieścić w repozytorium w katalogu

grupaN/zadanie7/ab123456

gdzie N jest numerem grupy, a ab123456 jest identyfikatorem osoby składającej
rozwiązanie. Katalog z rozwiązaniem nie powinien zawierać innych plików. Nie
wolno umieszczać w repozytorium plików dużych, wykonywalnych, binarnych,
tymczasowych (np. *.o) ani innych zbędnych. W szczególności do rozwiązania nie
należy  dołączać plików graficznych (*.ps, *.pdf).
