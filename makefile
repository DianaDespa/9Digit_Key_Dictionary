.PHONY: clean

build: tema4

tema4: main.cpp key.h treap.h trie.h
	g++ -o tema4 main.cpp -Wall
	
clean: 
	rm -f tema4
