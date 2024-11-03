# Dokumentacja wstępna
## Narzędzie do wizualizacji grafów
Celem projektu jest stworzenie aplikacji desktopowej, która pozwala na wizualizacje grafów.  
Referencyjnym przykładem takiej aplikacji jest [gephi](https://gephi.org).  
Aplikacja powinna być wydajna i napisana w sposób pozwalający na jej rozszerzanie za pomocą wtyczek użytkowników, które np. pozwalają na implementację własnych algorytmów rozłożenia grafu w przestrzeni.

## Realizacja
Aplikacja będzie opierała się na dwóch głównych komponentach:
- `C++` - wydajne przetwarzanie grafów, implementacja algorytmów rozłożenia grafu w przestrzeni oraz obsługa wtyczek
- `Python` - część wizualna i GUI


### Technologie i narzędzia
- [`C++`](https://cplusplus.com/):
    - [`conan`](https://github.com/conan-io/conan) - zarządzanie pakietami
    - [`Catch2`](https://github.com/catchorg/Catch2/) - testowanie
    - [`Boost.DLL`](https://github.com/boostorg/dll) - obsługa wtyczek
- [`Python`](https://www.python.org/):
    - [`pdm`](https://github.com/pdm-project/pdm) - zarządzanie pakietami
    - [`pytest`](https://docs.pytest.org/en/stable/) - testowanie
    - [`Tkinter`](https://docs.python.org/3/library/tkinter.html) - GUI
- [`pybind11`](https://pybind11.readthedocs.io/en/stable/) - generacja wiązań `Python` <-> `C++`
- [`CMake`](https://cmake.org/) - zarządzanie projektem (budowanie paczki, testowanie, generacja dokumentacji itd.)

### Podproblemy
- Aby zapewnić wydajność przetwarzania grafów, część za to odpowiedzialna zostanie zaimplementowana w `C++`
- Aby umożliwić użytkownikom rozszerzenie działania aplikacji za pomocą wtyczek implementujących dodatkowe algorytmy rozłożenia grafu w przestrzeni, zostanie zdefiniowane API implementowane przez wtyczki.
- Zostanie zdefiniowane API umożliwiające rozszerzenie aplikacji o dodatkowe formaty grafów
- Wtyczki będą dynamicznie ładowanymi bibliotekami (Windows: *.dll*; Linux: *.so*)
- Przenośność kodu obsługi wtyczek zostanie zapewniona przy pomocy biblioteki `Boost.DLL`
- Wizualizacja zostanie zrealizowana w `Pythonie` ze względu na wygodę tworzenia aplikacji oraz brak wymagających obliczeń
- Rozszerzenie `Pythona` w `C++` zostanie zrealizowane przy użyciu biblioteki `pybind11`

### Funkcje zaplanowane do realizacji
- Wczytywanie grafu w formacie `GraphML`
- Przybliżanie i oddalanie widoku grafu
- Grupowanie węzłów - węzły będą mogły być scalone w jeden, zawierający połączenia wszystkich wchłoniętych węzłów
- Ręczne przesuwanie węzłów
- Tworzenie, edytowanie oraz zapisywanie grafów
- Wyświetlanie informacji w węźle
- Dwie przykładowe wtyczki implementujące algorytmy rozłożenia grafu w przestrzeni
