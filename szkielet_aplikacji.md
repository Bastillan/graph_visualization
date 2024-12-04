# Szkielet aplikacji
## Przykładowy program

## Instrukcja
### Budowanie
#### C++
- Wykorzystywane narzędzia: `conan`, `cmake`
- Przy pierwszym korzystaniu z `conan`a należy wykonać komendę:
    ```bash
    conan profile detect --force
    ```
- W katalogu *cpp* należy wykonać odpowiednie polecenia:
    - Release
        ```bash
        conan install . -s build_type=Release --build=missing
        cmake --preset conan-release
        cmake --build --preset conan-release
        ```
    - Debug
        ```bash
        conan install . -s build_type=Debug --build=missing
        cmake --preset conan-debug
        cmake --build --preset conan-debug
        ```
#### Python
- Wykorzystywane narzędzia: `pdm`
- W katalogu *python* należy wykonać odpowiednie polecenia:
    - Instalacja projektu
        ```bash
        pdm install
        ```
### Uruchomienie
- Aby uruchomić program należy wejść do katalogu *python*
- Aktywować wirtualne środowisko
    ```bash
    eval $(pdm venv activate)
    ```
- Uruchomić moduł
    ```bash
    python -m src.graph_viewer.gui
    ```
### Testowanie
- Aby uruchomić testy jednostkowe dla części napisanej w C++, należy po zbudowaniu projektu wywołać polecenie
    ```bash
    ctest --test-dir build/Debug
    ```
### Generowanie dokumentacji kodu
- Wykorzystywane narzędzia: `doxygen` oraz jako zależność `graphviz`
- Należy wejść do katalogu *docs*
- Wykonać polecenie
    ```bash
    doxygen
    ```
- Otworzyć za pomocą przeglądarki plik *html/index.html*