Micha� Belniak, grupa I3, informatyka semest 5.
Projekt: AAL-11-LS kartony
Prowadz�cy: �ukasz Skonieczny.

Tre�� zadania:
Ortodyksyjny kolekcjoner tekturowych karton�w zaczyna narzeka� na brak miejsca do przechowywania swoich 
cennych zdobyczy. Postanowi� oszcz�dzi� miejsce przez wk�adanie karton�w jeden w drugi. 
W trosce o zachowanie dobrego stanu karton�w, umieszcza tylko jeden karton wewn�trz wi�kszego,
a woln� przestrze� wype�nia materia�em ochronnym. 
Tak zabezpieczony karton mo�e nast�pnie umie�ci� wewn�trz innego wi�kszego kartonu, 
ale nie mo�e umie�ci� dw�ch karton�w obok siebie w jednym kartonie. 
Dla danego zbioru karton�w nale�y znale�� najlepsze upakowanie karton�w, 
tzn. takie, kt�re zwalnia najwi�cej miejsca.

Mo�liwe polecenia aktywacji programu:

./kartony -p  	//Wywo�anie programu, je�li chcemy podawa� wymiary kolejnych pude�ek z klawiatury lub innego, standardowego wej�cia.
Dobre rozwi�zanie dla sprawdzania poprawno�ci dzia�ania algorytmu.

./kartony -p <file_name.txt>  //Wywo�anie programu z wczytaniem danych z pliku tekstowego. Plik powinien zawiera� 
tylko i wy��cznie wymiary kolejnych karton�w rozdzielone enterem, z podw�jnym enterem mi�dzy kolejnymi kartonami.

./kartony -c <complexity>   //Wywo�anie programu z losowym problemem o wielko�ci <complexity> karton�w.

./kartony -t <portions_per_step> <step1> [step2] [step3] ... //Wywo�anie programu, kt�ry dla ka�dej wielko�ci
problemu <step1>, <step2>... wykonuje <portions_per_step> losowych problem�w i podaje czasy dla ka�dego wykonania algorytmu.

./kartony -t -g [-n] <step1> [step2] [step3] ... //Wywo�anie programu, kt�ry dla ka�dej wielko�ci
problemu <step1>, <step2>... wykonuje losowy problem i tworzy tabele ze zgodnosciami czasu wykonania 
z oszacowaniem teoretycznym problemu. Dodanie flagi -n powoduje, �e wymiary b�d� ca�kowicie losowe,
bez generowania trudnych przypadk�w.

Konwencja zwi�zana z danymi wej�ciowymi i wyj�ciowymi.
Dane wej�ciowe to tr�jki liczb zmiennoprzecinkowych oznaczaj�cych wymiary pude�ek, np.:
123
152.2
124.5

12.2
14.42
12.75
oznacza dwa pude�ka o podanych wymiarach.
Dane wyj�ciowe s� postaci:
5<-1<-3

2

4
co oznacza, �e pude�ko nr 3 powinni�my umie�ci� w pude�ku nr 1, a to za� w pude�ku nr 5. Pude�ka 2 i 4 powinny
pozosta� niezapakowane. Dodatkowo program podaje ca�kowit� obj�to�� karton�w oraz obj�to�� zaoszcz�dzon� 
dzi�ki optymalnemu zapakowaniu. 

Kr�tki opis metody rozwi�zania, zastosowanych algorytm�w i struktur danych.
Zastosowa�em graf acykliczny skierowany wa�ony. Wagi kraw�dzi to obj�to�ci pude�ek na kt�re wskazuje kraw�d�.
Wierzcho�ki odpowiadaj� kartonom. 
Algorytm dzia�a ze z�o�ono�ci� O(n^3) i polega na znajdowaniu roz��cznych �cie�ek,
kt�rych suma daje ca�y graf i suma wag kraw�dzi w �cie�kach jest najwi�ksza.

Informacje o funkcjonalnej dekompozycji programu na modu�y �r�d�owe - nag��wkowe i
implementacyjne ("przewodnik" po plikach �r�d�owych).

main.cpp - w tej funkcji odczytywane jest wywo�anie programu oraz tworzone instancje problemu.
Graph.h - w tym pliku znajduje si� definicja klasy Graph, kt�ra jest realizacj�struktury grafu skierowanego wa�onego.
MPacking.h - w tym pliku znajduje si� definicje klasy MPacking, kt�ra rozszerza klas� Graph
wzbogacaj�c j� o funkcje potrzebne do rozwi�zania algorytmu oraz tworz�ce graf z wej�cia.
EfficiencyTest.h - plik, w kt�rym znajduje si� klasa testuj�ca MPacking wydajno�ciowo.

Inne informacje dodatkowe o szczeg�lnych decyzjach projektowych (np. ograniczenia dotycz�ce
rozmiaru problemu, charakterystyki generator�w danych testowych, specjalne konwencje w
alokacji pami�ci dynamicznej, wymagania dotycz�ce typ�w parametryzuj�cych szablony,
konwencje zwi�zane z obs�ug� sytuacji wyj�tkowych, itp.).

Rozmiar problemu, z kt�rym dobrze sobie radzi algorytm to 1-1200 (czas rozwi�zania poni�ej 5 sekund na 
laptopie Dell Inspiron 7570 Intel Core i7-8550U (4 rdzenie, od 1.80 GHz do 4.00 GHz), 8gb RAM). 
Dane testowe s� generowane wraz z trudnymi przypadkami, w kt�rych co pewn� ilo�� pude�ek generowane s�
pude�ka o tych samych wymiarach w ilo�ci (wielko�� problemu / 100).



