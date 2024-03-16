# Sorting-Algorithms

Sortowanie kubełkowe
- Złożoność obliczeniowa:
  - Średni przypadek: O(n)
  - Najgorszy przypadek: O(n^2)
- Opis działania: Algorytm dzieli dane w zależności od zakresu, który jest ustalony na podstawie wartości minimalnej i maksymalnej z tablicy danych. Dzieli dane na podzakresy (kubły), wpisując wartości same w sobie jako indeks kubła, aby następnie, gdy taka wartość pojawi się w tablicy, zwiększyć licznik o jeden. Ostatecznie należy przypisać do tablicy indeksy, w zależności od tego jak duży jest licznik danego indeksu.

Sortowanie przez scalanie
- Złożoność obliczeniowa:
  - Średni przypadek: O(n log n)
  - Najgorszy przypadek: O(n log n)
- Opis działania: Algorytm dzieli dane na mniejsze podtablice. Wykonuje to dla prawej i lewej strony w zależności od elementu środkowego (m). Następnie dane są scalane w jedną tablicę. Scalanie polega na przyrównaniu do siebie lewej wartości z prawą wartością w następującej po sobie kolejności. Algorytm wykorzystuje rekurencję.

Sortowanie szybkie
- Złożoność czasowa:
  - Najlepszy przypadek: O(n log n)
  - Średni przypadek: O(n log n)
  - Najgorszy przypadek: O(n^2)
- Opis działania: Algorytm wybiera element bazowy (pivot), a następnie wyszukuje z lewej strony elementu większego od elementu bazowego, a z prawej strony szuka elementu większego niż nasz pivot, następnie zamienia je ze sobą. Dzieje się tak do momentu, gdy lewa strona przekroczy prawą, co jest uwarunkowane tym, że chcemy, aby nasze dane były posortowane od najmniejszego do największego. Wszystko dzieje się rekurencyjnie.
