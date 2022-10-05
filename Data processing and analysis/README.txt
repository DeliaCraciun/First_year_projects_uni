	Prelucrarea si analizarea datelor secventiale

1.Formatul datelor
-Se citesc numarul de perechi, dupa care perechile efective cu timestamp si value.
2.1. Eliminare de exceptii folosind metode statistice
	Parcurgerea listei cu ferestre de 5 cate 5
-Acest lucru s-a realizat prin retinerea nodului de la care vreau sa incep sa trec
prin cele 5 noduri.Astfel, intr-un nod auxiliar am retinut initial adresa inceputului
listei, parcurgeam fereastra de cele 5 noduri si realizam calculul sumelor necesare,
dupa care nodul meu auxiliar trecea la urmatorul nod, acela devenind inceputul nou 
al ferestrei mele.
	Calculul sumelor si verificarea intervalelor
-Parcugeream fereastra deja creeata, faceam suma elementelor, dupa care calculam
media aritmetica.Pentru deviatie, in mod similar, faceam intai suma,apoi aplicam
formula.Daca nodul se afla in interval,il inseram intr-o lista auxiliara.
-In final,returnam noua lista.  
2.2.1.Filtrarea mediana
-Similar ca anterior,parcurg fereastra de cate 5 noduri.Intr-o variabila auxiliara retin 
timestamp-ul nodului din mijloc.Sortez fereastra, ca mai apoi sa inserez intr-o lista 
auxiliara un nod cu timestamp-ul retinut si valoarea din mijloc a ferestrei sortate.
-In final, returnez lista noua.
2.2.2.Filtrare folosind media aritmetica
-Parcurg fereastra de 5 elemente, fac suma acestora, dupa care calculez media aritmetica
si o retin intr-o lista auxiliara.
2.3.Uniformizarea datelor
-Verific daca diferenta dintre timestamp urile a doua noduri consectuive se afla intre 100
si 1000 de milisecunde.Daca da, atunci fac media aritmetica intre cele doua timestamp-uri
si intre valorile nodurilor respective,punandu-le in nodul la care ma aflu.
2.4.Copletarea datelor
-Calculez prima oara cele trei W-uri dupa formula data.
-Apoi parcurg lista, verificand daca diferenta a doua timestamp-uri consecutive este mai mare
de 1000 de milisecunde, retinandu-l pe cel mai mare.Daca da, cat timp diferenta dintre acel 
timestamp-ul si cel anterior, la care adaug 200 de milisecunde, este mai mare de 200, va trebui
sa adaug noi noduri. Imi fac sumele cu elementele din stanga si din dreapta retinute
anterior, inmultindu-le cu W-urile deja calculate.Caclulez C, ul si f date in problema,
pentru sume,apoi inserez in lista mea nodurile cu timestampul nou si f.Retin intr,un contor
mereu pozitia la care ma aflu pentru a stii unde introduc nodul nou.
2.5.Statistici
-Sortez lista intr-o lista auxiliara.Caclulez capatul stang al primului interval, acesta
fiind cel mai mic multiplu de delta mai mare decat primul element din lista.Capatul drept
 va fii capatul stang plus delta.Capatul drept al ultimului interval este cel mai mic 
multpilu de delta mai mare ca cel mai mare element din lista.Apoi,cat timp nu ajung cu 
capatul stang al intervalului la acest maxim retin intr-un contor cate elemente se afla
in intervalele respective si le afisez daca contorul e diferit de 0.
3.Main
-Intr-un vector de cuvinte retin argumentele din linia de comanda si verific cu strcmp
sau strstr ce comenzi am primit,apeland functiile necesare.
-Afisez rezultatul.
TIMP DE IMPLEMENTARE
-Aproximativ 10 ore in total.