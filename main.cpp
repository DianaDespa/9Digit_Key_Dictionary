/* Despa Diana-Alexandra 311CA */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "key.h"
#include "treap.h"
#include "trie.h"

int main()
{
	freopen("date.in", "r", stdin);
	freopen("date.out", "w", stdout);
	
	srand(time(0));
	
	int N, M, i, ap, x;
	unsigned int j;
	
	/* Vectorul cifre retine pe fiecare pozitie i cifra corespunzatoare literei
	   cu indicele i din alfabetul englez.*/
	int cifre[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 
						8, 8, 8, 9, 9, 9, 9};
	char number[21], word[31], *p;
	
	Trie trie;
	
	scanf("%d", &N);
	for (i = 0; i < N; i++) {	
		scanf("%s %d", word, &ap);
		
		/* Sirul de caractere number retine reprezentarea cu cifre a cuvantului
		   citit word.*/
		for (j = 0; j < strlen(word); j++) {
			number[j] = cifre[word[j] - 'a'] + '0';
		}
		
		number[j] = '\0';
		
		/* Inserez in trie cuvantul si numarul de apartii corespunzator citite 
		   de la tastatura, cu optiunea '0', adica fara actualizarea numarului 
		   de aparitii.*/
		trie.insert(number, word, ap, '0');
	}
	
	Treap<Key> *found_treap;
	Key found;
	
	scanf("%d", &M);
	for (i = 0; i < M; i++) {
		scanf("%s", word);
		
		x = 0;
		p = strchr(word, '*');
		
		/* In caz ca apare caracterul '*' in sirul citit, se extrage numarul 
		   de dupa el in variabila x.*/
		if (p != NULL) {
			/* Se extrage sirul de cifre pana la caracterul '*'.*/
			strncpy(number, word, p - word);
			x = atoi(p + 1);
			number[p - word] = '\0';
		} else {
			strcpy(number, word);
			number[strlen(word)] = '\0';
		}
		
		/* Variabila found_treap retine un pointer la structura de tip treap 
		   care se afla in trie la calea data de sirul de cifre number.*/
		found_treap = trie.find(number);
		
		/* x va fi argumentul metodei findK, cu care se va gasi al x-lea nod 
		   in ordine crescatoare. Dar se doreste nodul cu indicele x + 1 in 
		   ordine descrescatoare, astfel ca x devine diferenta dintre numarul 
		   total de noduri si restul impartirii lui x la numarul total de 
		   noduri (pentru parcurgere circulara).*/
		x = found_treap->nr_nodes - x % found_treap->nr_nodes;
		found = found_treap->findK(x);
		
		printf("%s\n", found.s.c_str());
		
		/* Se reinsereaza nodul gasit, cu actualizarea numarului de aparitii.*/
		trie.insert(number, found.s, found.prio, '1');
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
