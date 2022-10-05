!!!Pe vmchecker task4 imi da 0 puncte,iar in checker-ul local imi da maxim de 
punctaj.
Durata tema: doua saptamani.
Task1
-Citirea a durat cel mai mult de implementat,aproximativ o saptamana.
-Am deschis fisierul master.txt si am citit linie cu linie,retinand intr-o 
structura numele fiecarui site,alocand memorie structurii cand era cazul si
am retinut numarul lor.
-Dupa care intram in fiecare site si retineam pe rand datele din fiecare fisier .html.
Citesc prima linie si iau pe rand datele.Apoi citesc caracter cu caracter pana la numarul 
de octeti ati si retin intreg codul HTML.Inchid fiecare fisier
-Dupa ce am citit,parsez codul si titlul si aflarea pozitiei tagurilor,retinandu-i intr-un
pointer,dupa ce i-am gasit cu strstr si ii retin.Apoi salevz caracter cu caracter continutul
parsat.
Task2
-A durat cam 3 zile.
-Contine Task1
-Citesc de la tastatura acel string pe care il despart in cuvinte cu strtok si il pun intr-un dublu
pointer alocat dinamic.Practic fiecare "linie" contine cat un cuvant.Apoi ii pun cate un spatiu
in stanga cuvantului si in dreapta cuvantului,urmat de terminator de sir la dreapta,dupa spatiu.
-In functia in care parsez continutul,creez o copie a paragrafului in care
adaug acestuia la stanga si la dreapta cate un spatiu si inclocuiesc '\n' cu spatiu.
-Apoi caut cuvintele cheie cu strstr,iar daca le gasesc le voi sorta lexicografic.
Daca sunt egale dpdv lexicgrafic,le sortez in functie de nr de accesari.
Task3
-Aprox 3 zile
-Contine Task1,Task2
-Daca intalnesc ghilimele,consider ca am inceput o secventa si salvez urmatoarele cuvinte pe aceeasi
"linie" in acel dublu pointer, pana cand intalnesc iarasi ghilimelele, ceea ce semnifica un final de 
secventa.
-Singurele diferente sunt ca in momentul in care intalnesc o secventa,transform ghilimelele in spatiu
si apoi salvez secventa in acel dublu pointer.
-Daca am un cuvant de genul "-rau", atunci voi pune spatiul dupa "-",caracterul ramanand pe pozitia sa
in acel dublu pointer, si inca in spatiu la final ca la toate cuvintele.
-Site-urile care vor avea cuvinte "nepermise", vor avea intr-un vector de frecventa un numar diferit de 0.
Celelalte 0.
-Daca gasesc cu strstr cuvintele cheie in paragraful dintr-un anumit site si vectorul de frecventa corespunzator
este 0,se retine.
-La final se afiseaza ce se cerea.
Task4
-O zi.
-Am doua functii : una transforma din decimal in binar;alta din binar in zecimal;
-Am doua functii rotr si rotl:prima roteste bitii unui caracter transmis(dupa ce a fost transformat
in binar cu dec_to_bin) spre dreapta si returneaza valorea decimal cu bin_to_dec.Analog la cealalta functie 
doar ca spre stanga. 
-Iau caracter cu caracter din codul HTML si il transmit la rotr si rotl in functie de paritatea pozitiei 
caracterului,facand XOR la valori si salvand-ule pt fiecare site.
-Compar cu cheia oficiala data in datele de intrare si afisez daca este sigur sau nu site-ul, in functie de
cheie.
Browser
-Primul subpunct-2 zile
-Pentru cautarea avansata,cautare simpla,citire din master.txt si parsare pentru fiecare site am realizat librarii
pentru a le folosit in codul pentru browser.
-Am facut prima fereastra care contine legenda si care iti permite sa scrii un text daca apesi C,realizandu-se un search
bar.Se salveaza string-ul respectiv si apoi se mai poate apasa o tasta fie pt cautare avansata,fie pt cea simpla.
Apoi se sterge fereastra veche,se deschide alta cu rezulttul cautarii.
Se poate apasa tasta Q pentru a iesi din program.