```
	Pixelii fiecarei poze sunt salvati intr-un vector bidimensional, cu
elemente de tip "pixel". Un element de tip pixel contine trei valori de tip
int: r, g, b.

"Alcoare"	
	Functia "alocare" returneaza adresa de inceput pentru o noua matrice de 
pixeli.

"Afisare"
	Functia "afisare" afiseaza la STDOUT matricea de pixeli actuala.

"Eliberare"	
	Functia "eliberare" elibereaza memoria alocata pentru o matricea de pixeli.

"Citire"
	Functia "citire" citeste de la STDIN o matrice de pixeli.
	
"Main"
->	Functia "main" rezolva cerintele temei.
->	"While"-ul din "main" se executa cat timp codul specific unei operatii 
este diferit 0.
->	Pentru fiecare cod de la 1 la 8 se verifica conditiile pentru iesire cu
eroare. In acest caz, se elibereaza memoria alocata dinamic, dimensiunile
matricei de pixeli devin 0, se va afisa la iesire codul specific erorii si 
programul va iesi cu exit(EXIT_FAILURE). Daca toti parametrii sunt bine 
definiti si alocarea a avut loc cu succes, atunci programul va functiona 
corect.

->	COD 1
	->	Se elibereaza memoria pentru poza curenta (daca exista)
	->	Se citesc valorile pentru lungimea si inaltimea unei noi poze (nl, nc)
	->	Se aloca memorie pentru noua poza
	->	Se citesc 3 * nl * nc valori, care alcatuiesc pixelii pozei (r, g, b)

->	COD 2
	->	Se citesc valorile pentru doua coordonate de tip (x,y), care reprezinta 
	coordonatele viitoarei poze
	->	Se calculeaza dimensiunile viitoarei poze (nlb, ncb)
	->	Se aloca dinamic memorie pentru o matrice auxiliara "b", de dimensiune
	nlb * ncb, in care se vor copia datele corespunzatoare pentru crop, din 
	matricea initiala "a".
	->	Se elibereaza spatiul alocat pentru matricea "a"
	->	Se aloca memorie pentru noua poza, in matricea "a"
	->	Datele din matricea auxiliara "b" se copiaza in matricea "a"
	->	Se elibereaza spatiul alocat matricei auxiliare "b"

->	COD 3
	->	Se citesc dimensiunile pentru viitoarea poza (nlb, ncb)
	->	Se aloca memorie pentru o matrice auxiliara "b", de dimensiune
	nlb * ncb
	->	Toate valorile din matricea auxiliara "b" sunt inlocuite cu valoarea
	255 (deoarece (255, 255, 255) este echivalentul culorii alb)
	->	Se copiaza toate valorile din matricea "a" in "b", de la (0,0) la 
	(nl-1,nc-1)
	->	Se elibereaza memoria alocata pentru matricea "a"
	->	Se aloca memorie pentru noua poza, in matricea "a" (nlb * ncb)
	->	Se copiaza toate valorile din "b" in "a"
	->	Se elibereaza memoria alocata pentru matricea "b"

->	COD 4
	->	Se citesc doua coordonate de tip (x,y) si trei valori pentru r, g, b
	->	Se parcurge matricea "a" de la (start_line, start_col) la
	(end_line, end_col) si se modifica cele 3 valori corespunzatoare fiecarui
	pixel cu cele 3 valori citite initial: r, g si b

->	COD 5
	->	Se citeste in variabila "nr_iter", de cate ori se va blura poza
	->	Intr-o instructiune de tip "for", se vor realiza urmatoarele 
	instructiuni, de "nr_iter" ori:
		->	Se va aloca memorie pentru o matrice auxiliara "b", de dimensiune 
		egala cu "a"
		-> Elementele din "b" se vor calcula astfel:
			->	Daca este unul dintre colturile matricei, acesta va fi media
			elementelor din "a", de pe pozitiile apropiate, pe orizontala
			si verticala, deci doi vecini
			->	Daca se afla pe prima sau ultima linie sau pe prima sau ultima
			coloana, dar nu in colt, acesta va avea 3 vecini, deci va fi
			media acestora
			->	Restul elementelor vor avea cate 4 vecini, deci va fi media
			acestora
			->	Media se realizeaza pentru fiecare culoare: r, g si b
		->	Se copiaza elementele din "b" in "a"
		->	Se elibereaza memoria alocata pentru matricea "b"

->	COD 6
	->	Se citeste in variabila "num_rot" de cate ori se va roti poza
	->	Se repeta de "num_rot" urmatorii pasi:
	    ->	Se aloca memorie pentru o matrice auxiliara "b", de dimensiuni:
	    nlb = numarul de coloane al matricei "a" si ncb = numarul de linii al
	    matricei "a"
	    ->	Prima linie a lui "a" devine ultima coloana a lui "b"
	    ->	A n-a linie a lui "a" devine a n-a coloana a lui "b"
	    ->	Ultima linie a lui "a" devine prima coloana a lui "b"
	    ->	Se elibereaza memoria alocata pentru "a"
	    ->	Se aloca memorie pentru "a" (nlb, ncb)
	    ->	Se copiaza elementele din "b" in "a"
	    ->	nl = nlb si nc = ncb
	    ->	Se elibereaza memoria pentru "b"

->	COD 7
	->	Se citeste un set de coordonate de tip (x,y) in variabilele start_line
	si start_col si trei numere in r, g si b
	->	In variabilele r2, g2 si b2 se retin valorile corespunzatoare pixelului
	din pozitia (start_line, start_col)
	->	Se aloca memorie dinamic pentru doi vectori unidimensionali vi si vj, 
	in care se salveaza coordonatele vecinilor pixelului curent, care au 
	aceeasi culoare, urmand sa se actualizeze vecinii pentru fiecare nou 
	adaugat in aceasta coada, utilizandu-se metoda FIFO (first in, first out)
	->	Fiecare pixel din coada va fi modificat cu valorile citite initial
	r, g si b
	->	Cand s-a ajuns la sfarsitul cozii, se va elibera memoria alocata
	pentru cei doi vectori vi si vj

->	COD 8
	-> Daca exista o poza, aceasta se va afisa, apelandu-se functia "afisare"
```
