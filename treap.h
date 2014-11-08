/* Despa Diana-Alexandra 311CA */

#ifndef __TREAP__H
#define __TREAP__H

template <typename T> struct Treap {
	T key;
	int priority;
	Treap<T> *left, *right;
	bool nil;
	int nr_nodes;

	/* Constructor - creaza un nod nil*/
	Treap() : priority(-1), left(NULL), right(NULL), nil(true), nr_nodes(0) {}
	
	/* Destructor - sterge recursiv tot subarborele a carui radacina este nodul
	   pentru care este apelat*/
	~Treap()
	{
		delData();
	}
	
	/* Adauga date, transformand un nod nil intr-un nod obisnuit*/
	void addData(const T &key, const int &priority) 
	{
		this->nil = false;
		this->key = key;
		this->priority = priority;
		this->nr_nodes = 1;
		this->left = new Treap();
		this->right = new Treap();
	}

	/* Sterge un nod obisnuit, transformandu-l intr-unul nil, determinand si 
	   stergerea tuturor descendentilor*/
	void delData()
	{
		this->nil = true;
		this->priority = -1;
		delete this->left;
		this->left = NULL;
		delete this->right;
		this->right = NULL;
		this->nr_nodes = 0;
	}

	/* Verifica daca un nod este nil*/
	bool isNil()
	{
		return this->nil;
	}

	/* Cauta un nod cu cheia key*/
	Treap<T> * find(T key)
	{
		if (isNil())
			return NULL;
		
		if (this->key == key) 
			return this;

		if (key < this->key) {
			if(!left->isNil())
				return left->find(key);
		} else {
			if (!right->isNil())
				return right->find(key); 
		}
		return NULL;
	}
	
	/* Realizeaza o rotire spre dreapta*/
	void rotateRight(Treap<T> *&nod)
	{
		Treap<T> *aux;
		aux = nod->left;
		nod->left = aux->right;
		aux->right = nod;
		
		nod->nr_nodes = nod->left->nr_nodes + nod->right->nr_nodes + 1;
		nod = aux;
		nod->nr_nodes = nod->left->nr_nodes + nod->right->nr_nodes + 1;
	}

	/* Realizeaza o rotire spre stanga*/
	void rotateLeft(Treap<T> *&nod)
	{
		Treap<T> *aux;
		aux = nod->right;
		nod->right = aux->left;
		aux->left = nod;

		nod->nr_nodes = nod->left->nr_nodes + nod->right->nr_nodes + 1;
		nod = aux;
		nod->nr_nodes = nod->left->nr_nodes + nod->right->nr_nodes + 1;
	}
	
	/* Insereaza un nod cu cheia == key si prioritatea == priority in treap*/
	void insert(Treap<T> *&fatherPointer, T key, const int &priority)
	{
		if (isNil()) {
			addData(key, priority);
			return;
		}

		if (key < this->key) {
			left->insert(left, key, priority);
		} else {
			right->insert(right, key, priority);
		}

		nr_nodes++;
		
		if (left->priority > this->priority) {
			rotateRight(fatherPointer);
		} else {
			if (right->priority > this->priority)
				rotateLeft(fatherPointer);	
		}
	}
	
	/* Sterge nodul cu cheia == key din treap*/
	void erase(Treap<T> *&fatherPointer, T key)
	{
		if (isNil())
			return;

		nr_nodes--;
    
		if (key < this->key) {
			left->erase(left, key);
		} else {
			if (key > this->key) {
				right->erase(right, key);
			} else {
				if (left->isNil() && right->isNil()) {
					delData();
				} else {
					if (left->priority > right->priority) {
						rotateRight(fatherPointer);
						fatherPointer->erase(fatherPointer, key);
					} else {
						rotateLeft(fatherPointer);
						fatherPointer->erase(fatherPointer, key);
					}
				}
			}
		}
	}
	
	/* Cauta cel de-al k-lea nod in ordine crescatoare, in functie de cheie*/
	T findK(const int &k)
	{
		/* Daca nodul cautat are gradul mai mic sau egal decat numarul de 
		   noduri ale subarborelui stang, el va fi cautat acolo.*/
		if (k <= left->nr_nodes)
			return left->findK(k);
		
		/* Daca nodul cautat are gradul cu 1 mai mare fata de numarul de noduri
		   ale subarborelui stang, inseamna ca radacina acelui subarbore este 
		   nodul cautat.*/
		if (k == left->nr_nodes + 1) 
			return this->key;
		
		/* Daca nodul cautat are gradul 1, inseamna ca el este fiul stang al 
		   nodului curent.*/
		if (k == 1)
			return left->key;
		
		/* In orice alt caz, se cauta nodul in subarborele drept, si se 
		   actualizeaza gradul lui.*/
		return right->findK(k - nr_nodes + right->nr_nodes);
	}
};

#endif
