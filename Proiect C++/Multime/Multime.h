#pragma once

#define NULL_TELEM -1
#define cap 10
typedef int TElem;

class IteratorMultime;

class Node{
public:
    TElem data;
    int next;
    Node() = default;
    Node(TElem data, int next): data{data}, next{next} {};
    ~Node() = default;
};

class Multime {
	friend class IteratorMultime;

    private:
		int maxCapacity;
        Node* nodes;
        int head;
        int freeHead;
        int length;
        int allocate();
        void free(int position);
        void resize();

    public:
 		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;


		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

        int diferenta(Multime& m);

		// destructorul multimii
		~Multime();
};




