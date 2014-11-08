/* Despa Diana-Alexandra 311CA */

#ifndef __TRIE__H
#define __TRIE__H

struct Trie {
	Trie *node[8];
	Treap<Key> *info;
	
	/* Constructor - seteaza la 0 toate nodurile fii*/
	Trie()
	{
		memset(node, 0, sizeof(node));
		info = NULL;
	}
	
	/* Destructor - sterge recursiv toata structura, incepand cu nodul pentru 
	   care este apelat, eliberand memoria pentru treap-urile din noduri*/
	~Trie()
	{
		for (int i = 0; i < 8; i++) {
			if (node[i]) {
				delete node[i];
			}
		}
		
		if (info != NULL)
			delete info;
	}
	
	/* Adauga un nou element la structura, avand calea din trie data de nr, 
	   valoarea compusa din sirul value si numarul prio, cu optiunea de 
	   insertie option. Optiunea determina daca insertia va actualiza numarul 
	   de aparitii ale unui cuvant (orice caracter inafara de '0') sau pur si 
	   simplu va adauga un nou sir de caractere la treap-ul de la calea nr din 
	   structura trie.*/
	void insert(const char *nr, const std::string &value, const int &prio, 
				const char &option)
	{
		if (*nr == '\0') {
			Key k;
			k.s = value;
			k.prio = prio;
			
			if (info == NULL) {
				info = new Treap<Key>();
			} else if (option != '0') {
				Treap<Key> *p = info->find(k);
				if (p != NULL) {
					k.prio++;
					
					/* Daca este actualizat numarul de aparitii, atunci cheia
					   este stearsa din treap, urmand ca apoi sa fie adaugata
					   din nou, cu noul numar de aparitii si cu o noua 
					   prioritate.*/
					info->erase(info, p->key);
				}
			}
			
			int pr = rand() % 1000;
			info->insert(info, k, pr);
			return;
		}
		
		if (node[*nr - '2'] == 0)
			node[*nr - '2'] = new Trie;
			
		node[*nr - '2']->insert(nr + 1, value, prio, option);
	}
	
	/* Cauta nodul din treap care se afla la calea indicata de sirul nr*/
	Treap<Key> * find(const char *nr)
	{
		if (*nr == '\0')
			return info;
		
		if (node[*nr - '2'])
			return node[*nr - '2']->find(nr + 1);
		
		return NULL;
	}
};

#endif
