# Dokumentacja końcowa
## Narzędzie do wizualizacji grafów

### Rozwiązane podproblemy
- Aby zapewnić wydajność przetwarzania grafów, część za to odpowiedzialna zostanie zaimplementowana w `C++`
- Zostanie zdefiniowane API umożliwiające rozszerzenie aplikacji za pomocą wtyczek implementujących obsługę algorytmów rozłożenia
- Wtyczki będą dynamicznie ładowanymi bibliotekami (Windows: *.dll*; Linux: *.so*)
- Przenośność kodu obsługi wtyczek zostanie zapewniona przy pomocy biblioteki `Boost.DLL`
- Wizualizacja zostanie zrealizowana w `Pythonie` ze względu na wygodę tworzenia aplikacji oraz brak wymagających obliczeń
- Rozszerzenie `Pythona` w `C++` zostanie zrealizowane przy użyciu biblioteki `pybind11`

### Zaimplementowane funkcje
- Wczytywanie grafu w formacie `GraphML`
- Przybliżanie i oddalanie widoku grafu
- Grupowanie węzłów - węzły będą mogły być scalone w jeden, zawierający połączenia wszystkich wchłoniętych węzłów
- Ręczne przesuwanie węzłów
- Tworzenie, edytowanie oraz zapisywanie grafów
- Wyświetlanie informacji w węźle
- Dwie przykładowe wtyczki implementujące algorytmy rozłożenia grafu w przestrzeni

### Podsumowanie
Zaimplementowane zostały wszystkie z wstępnie zaplanowanych funkcjonalności, jednak nie został rozwiązany jedne podproblem - "zdefiniowanie API umożliwiającego rozszerzenie aplikacji za pomocą wtyczek implementujących obsługę dodatkowych formatów plików" z powodu ??? . Pojawił się również problem z kompilacją aplikacji w `C++` w wersji release wynikający z braku inicjacji zmiennej w bibliotece `Boost`, nie znaleźliśmy sposobu, aby rozwiązać dany problem, więc przy kompilacji została ustawiona flaga `-Wno-uninitialized`.