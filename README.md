# PJATK-MHE
Metaheuristics at PJATK-Gdańsk

## ZADANIE 1
    Na zajęciach naszym głównym językiem programowania będzie C++. Korzystamy ze współczesnej wersji C++,
    to znaczy powyżej C++11. Sugeruję C++17 lub C++20.    
    Zadanie polega na przygotowaniu sobie środowiska pracy i zrobieniu przykładowego programu. 
    Program będzie korzystał z plików JSON i pozwoli nam na przetrenowanie  przydatnych elementów.
 
    Zadanie: Przygotuj program do wyświetlania tekstu w ramce. Niech konfiguracja będzie w pliku JSON.
    Skorzystaj z biblioteki do obsługi plików JSON:    https://github.com/nlohmann/json .
    Sam plik nagłówkowy do umieszczenia w katalogu z projektem jest tu: 
    https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
 
    Program Twój powinien działać według opisu:

    NAZWA
     zadanie1 - wyświetlenie tekstu w ramce według konfiguracji w pliku JSON
    SKŁADNIA
     zadanie1 NAZWAPLIKU
    OPIS
     Program ładuje konfigurację z pliku NAZWAPLIKU w którym opisany jest
    rozmiar ramki oraz tekst do umieszczenia w środku. Ramka będzie tekstowa wymiarów w na h
    z tekstem wyśrodkowanym w pionie i poziomie.
    
      Plik konfiguracyjny ma taki format: 
      {"w":SZEROKOSCRAMKI,"h":WYSOKOSCRAMKI,"text":TEKSTDOWPISANIAWRAMCE}
      PRZYKŁAD   zadanie1 config.json
    
    Na dodatkowy punkt:
     Jeśli tekst nie mieści się w ramce, to proszę go połamać na kawałki o długości takiej, aby zmieściły się w szerokości ramki.
  
