# Dokumentacja końcowa
## Narzędzie do wizualizacji grafów

### Rozwiązane podproblemy
- Aby zapewnić wydajność przetwarzania grafów, część za to odpowiedzialna została zaimplementowana w `C++`
- Zostało zdefiniowane API umożliwiające rozszerzenie aplikacji za pomocą wtyczek implementujących obsługę algorytmów rozłożenia
- Wtyczki są dynamicznie ładowanymi bibliotekami (Windows: *.dll*; Linux: *.so*)
- Przenośność kodu obsługi wtyczek została zapewniona przy pomocy biblioteki `Boost.DLL`
- Wizualizacja została zrealizowana w `Pythonie` ze względu na wygodę tworzenia aplikacji oraz brak wymagających obliczeń
- Rozszerzenie `Pythona` w `C++` zostało zrealizowane przy użyciu biblioteki `pybind11`

### Zaimplementowane funkcje (wszystkie jakie zaplanowano)
- Wczytywanie grafu w formacie `GraphML`
- Przybliżanie i oddalanie widoku grafu
- Grupowanie węzłów - węzły będą mogły być scalone w jeden, zawierający połączenia wszystkich wchłoniętych węzłów
- Ręczne przesuwanie węzłów
- Tworzenie, edytowanie oraz zapisywanie grafów
- Wyświetlanie informacji w węźle
- Dwie przykładowe wtyczki implementujące algorytmy rozłożenia grafu w przestrzeni

### Komentarz do zakresu wykonanych prac
Zaimplementowane zostały wszystkie z wstępnie zaplanowanych funkcjonalności, jednak nie został rozwiązany jeden podproblem - *zdefiniowanie API umożliwiającego rozszerzenie aplikacji za pomocą wtyczek implementujących obsługę dodatkowych formatów plików*. Problematyczne jest wczytywanie grafu, ponieważ trzeba założyć jakie dane (*properties*) mogą być przechowywane w wierzchołkach i krawędziach.

Ze względu na ustawienie restrykcyjnych flag kompilacji, pojawił się również problem z kompilacją aplikacji w `C++` w wersji release wynikający z możliwego braku inicjacji zmiennej (iteratora krawędzi) w bibliotece `Boost`, nie znaleźliśmy sposobu, aby rozwiązać dany problem, więc przy kompilacji została ustawiona flaga `-Wno-uninitialized`.

![Screen błędu](image.png)

### Struktura projektu
W części `C++` zostały napisane dwie wtyczki kompilowane jako biblioteki dynamiczne: *plugin_circular* i *plugin_grid*. Implementują one zdefiniowane API wyznaczając pozycje wierzchołków grafu za pomocą różnych algorytmów rozłożenia.

Wtyczki te są ładowane przez bibliotekę statyczną - *graphs_core*, podczas działania programu. Umożliwia ona wczytanie i zapisanie grafu do pliku oraz jego edycję.

Biblioteka ta jest udostępniana `Pythonowej` części dzięki kompilacji jako moduł `Pythonowy` ze zdefiniowanymi bindingami przy użyciu `pybind11`.

Część `Pythonowa` składa się jedynie z klasy *GraphViewer* która odpowiedzialna jest za graficzną prezentację grafów obsługiwanych za pomocą biblioteki *graphs_core*