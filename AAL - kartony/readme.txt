Micha³ Belniak, grupa I3, informatyka semest 5.
Projekt: AAL-11-LS kartony
Prowadz¹cy: £ukasz Skonieczny.

Treœæ zadania:
Ortodyksyjny kolekcjoner tekturowych kartonów zaczyna narzekaæ na brak miejsca do przechowywania swoich 
cennych zdobyczy. Postanowi³ oszczêdziæ miejsce przez wk³adanie kartonów jeden w drugi. 
W trosce o zachowanie dobrego stanu kartonów, umieszcza tylko jeden karton wewn¹trz wiêkszego,
a woln¹ przestrzeñ wype³nia materia³em ochronnym. 
Tak zabezpieczony karton mo¿e nastêpnie umieœciæ wewn¹trz innego wiêkszego kartonu, 
ale nie mo¿e umieœciæ dwóch kartonów obok siebie w jednym kartonie. 
Dla danego zbioru kartonów nale¿y znaleŸæ najlepsze upakowanie kartonów, 
tzn. takie, które zwalnia najwiêcej miejsca.

Mo¿liwe polecenia aktywacji programu:

./kartony -p  	//Wywo³anie programu, jeœli chcemy podawaæ wymiary kolejnych pude³ek z klawiatury lub innego, standardowego wejœcia.
Dobre rozwi¹zanie dla sprawdzania poprawnoœci dzia³ania algorytmu.

./kartony -p <file_name.txt>  //Wywo³anie programu z wczytaniem danych z pliku tekstowego. Plik powinien zawieraæ 
tylko i wy³¹cznie wymiary kolejnych kartonów rozdzielone enterem, z podwójnym enterem miêdzy kolejnymi kartonami.

./kartony -c <complexity>   //Wywo³anie programu z losowym problemem o wielkoœci <complexity> kartonów.

./kartony -t <portions_per_step> <step1> [step2] [step3] ... //Wywo³anie programu, który dla ka¿dej wielkoœci
problemu <step1>, <step2>... wykonuje <portions_per_step> losowych problemów i podaje czasy dla ka¿dego wykonania algorytmu.

./kartony -t -g [-n] <step1> [step2] [step3] ... //Wywo³anie programu, który dla ka¿dej wielkoœci
problemu <step1>, <step2>... wykonuje losowy problem i tworzy tabele ze zgodnosciami czasu wykonania 
z oszacowaniem teoretycznym problemu. Dodanie flagi -n powoduje, ¿e wymiary bêd¹ ca³kowicie losowe,
bez generowania trudnych przypadków.

Konwencja zwi¹zana z danymi wejœciowymi i wyjœciowymi.
Dane wejœciowe to trójki liczb zmiennoprzecinkowych oznaczaj¹cych wymiary pude³ek, np.:
123
152.2
124.5

12.2
14.42
12.75
oznacza dwa pude³ka o podanych wymiarach.
Dane wyjœciowe s¹ postaci:
5<-1<-3

2

4
co oznacza, ¿e pude³ko nr 3 powinniœmy umieœciæ w pude³ku nr 1, a to zaœ w pude³ku nr 5. Pude³ka 2 i 4 powinny
pozostaæ niezapakowane. Dodatkowo program podaje ca³kowit¹ objêtoœæ kartonów oraz objêtoœæ zaoszczêdzon¹ 
dziêki optymalnemu zapakowaniu. 

Krótki opis metody rozwi¹zania, zastosowanych algorytmów i struktur danych.
Zastosowa³em graf acykliczny skierowany wa¿ony. Wagi krawêdzi to objêtoœci pude³ek na które wskazuje krawêdŸ.
Wierzcho³ki odpowiadaj¹ kartonom. 
Algorytm dzia³a ze z³o¿onoœci¹ O(n^3) i polega na znajdowaniu roz³¹cznych œcie¿ek,
których suma daje ca³y graf i suma wag krawêdzi w œcie¿kach jest najwiêksza.

Informacje o funkcjonalnej dekompozycji programu na modu³y Ÿród³owe - nag³ówkowe i
implementacyjne ("przewodnik" po plikach Ÿród³owych).

main.cpp - w tej funkcji odczytywane jest wywo³anie programu oraz tworzone instancje problemu.
Graph.h - w tym pliku znajduje siê definicja klasy Graph, która jest realizacj¹struktury grafu skierowanego wa¿onego.
MPacking.h - w tym pliku znajduje siê definicje klasy MPacking, która rozszerza klasê Graph
wzbogacaj¹c j¹ o funkcje potrzebne do rozwi¹zania algorytmu oraz tworz¹ce graf z wejœcia.
EfficiencyTest.h - plik, w którym znajduje siê klasa testuj¹ca MPacking wydajnoœciowo.

Inne informacje dodatkowe o szczególnych decyzjach projektowych (np. ograniczenia dotycz¹ce
rozmiaru problemu, charakterystyki generatorów danych testowych, specjalne konwencje w
alokacji pamiêci dynamicznej, wymagania dotycz¹ce typów parametryzuj¹cych szablony,
konwencje zwi¹zane z obs³ug¹ sytuacji wyj¹tkowych, itp.).

Rozmiar problemu, z którym dobrze sobie radzi algorytm to 1-1200 (czas rozwi¹zania poni¿ej 5 sekund na 
laptopie Dell Inspiron 7570 Intel Core i7-8550U (4 rdzenie, od 1.80 GHz do 4.00 GHz), 8gb RAM). 
Dane testowe s¹ generowane wraz z trudnymi przypadkami, w których co pewn¹ iloœæ pude³ek generowane s¹
pude³ka o tych samych wymiarach w iloœci (wielkoœæ problemu / 100).



