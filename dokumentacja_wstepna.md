# Dokumentacja wstępna
## Narzędzie do wizualizacji grafów
Celem projektu jest stworzenie aplikacji (webowa lub desktopowa), która pozwala na wizualizacje grafów. Referencyjnym przykładem takiej aplikacji jest [gephi](https://gephi.org). Aplikacja powinna być wydajna i napisana w sposób pozwalający na jej rozszerzanie za pomocą wtyczek użytkowników, które np. pozwalają na implementację własnych algorytmów rozłożenia grafu w przestrzeni.


## Podproblemy i rozwiązania
- Aplikacja będzie pozwalała na wczytania grafu w formacie *JSON*
- Współrzędne wierzchołków grafu będą generowane poprzez wtyczkę napisaną w *Pythonie*
- Wyświetlanie będzie realizowane w *C++* za pomocą biblioteki *Qt*
- Podstawowe operacje na grafach będą zaimplementowane w *C++* i będą udostępnione wtyczkom za pomocą *pybind11*
- Aplikacja umożliwi przybliżanie oraz oddalanie grafu
- Możliwe będzie grupowanie węzłów - węzły zostaną scalone w jeden, zawierający połączenia wszystkich węzłów
- Możliwe będzie przesuwanie węzłów
- Zostanie stworzony menadżer umożliwiający tworzenie, edytowanie oraz zapisywanie grafów
- Możliwe będzie wyświetlanie informacji w węźle