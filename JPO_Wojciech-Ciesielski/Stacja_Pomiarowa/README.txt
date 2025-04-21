# Aplikacja Monitoringu Jakości Powietrza

## Opis
Aplikacja umożliwia monitorowanie jakości powietrza na podstawie danych udostępnianych przez Główny Inspektorat Ochrony Środowiska (GIOŚ). Jest to gotowa aplikacja, którą można uruchomić bezpośrednio bez instalacji.

## Jak uruchomić
1. Wypakuj wszystkie pliki z archiwum do wybranego folderu
2. Uruchom plik "Stacje_pomiarowe.exe"
3. Przy pierwszym uruchomieniu niektóre systemy antywirusowe mogą chcieć zweryfikować aplikację - jest to normalne zachowanie

## Funkcje
- **Wyszukiwanie stacji** - znajdź stacje pomiarowe w całej Polsce lub w konkretnym mieście
- **Dane z czujników** - sprawdź szczegółowe informacje z czujników o różnych zanieczyszczeniach
- **Wykresy** - przeglądaj dane pomiarowe w formie wykresów dla łatwiejszej analizy
- **Indeks jakości powietrza** - sprawdź ogólny indeks jakości powietrza oraz indeksy dla poszczególnych zanieczyszczeń
- **Praca offline** - aplikacja zapisuje dane lokalnie, dzięki czemu działa również bez internetu

## Obsługa aplikacji
1. Po uruchomieniu aplikacji wybierz "Pobierz stacje" aby pobrać listę stacji pomiarowych
2. Możesz wpisać nazwę miasta w pole wyszukiwania aby zawęzić wyniki
3. Wybierz interesującą Cię stację pomiarową z listy
4. Przejrzyj dostępne czujniki i wybierz ten, którego dane chcesz zobaczyć
5. Sprawdź indeks jakości powietrza dla wybranej stacji, klikając odpowiedni przycisk

## Dane offline
Aplikacja automatycznie zapisuje pobrane dane.  Możesz wyłączyć zapisywanie danych w ustawieniach aplikacji. Zapisują się w Appdata/Roaming/stacje_pomiarowe/cache

## Źródło danych
Aplikacja wykorzystuje oficjalne dane z API Głównego Inspektoratu Ochrony Środowiska:
https://powietrze.gios.gov.pl/pjp/content/api

## Rozwiązywanie problemów
- Jeśli aplikacja nie uruchamia się, upewnij się, że wszystkie pliki DLL są wypakowane w tym samym folderze co plik .exe
- W przypadku problemów z pobieraniem danych, sprawdź swoje połączenie internetowe lub skorzystaj z danych zapisanych w pamięci podręcznej
- Jeśli dane są nieaktualne, pamiętaj że API GIOŚ aktualizuje dane co około godzinę

## Uwaga
Aplikacja nie wymaga instalacji ani uprawnień administratora. Tworzy folder cache w katalogu danych aplikacji użytkownika do przechowywania pobranych danych.