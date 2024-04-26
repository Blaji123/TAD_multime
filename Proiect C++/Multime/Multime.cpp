#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

//complexity : Theta(1)
Multime::Multime() {
	maxCapacity = cap;
    head = NULL_TELEM;
    nodes = new Node[cap];
    for(int i=0;i<cap-1;i++){
        nodes[i].next = i + 1;
    }
    nodes[cap-1].next = NULL_TELEM;
    freeHead = 0;
    length = 0;
}

//complexity : Theta(1)
int Multime::allocate() {
    int newElem = freeHead;
    if (newElem!=NULL_TELEM){
        freeHead = nodes[freeHead].next;
        nodes[newElem].next = NULL_TELEM;
    }
    return newElem;
}

//complexity : Theta(1)
void Multime::free(int position){
    nodes[position].next = freeHead;
    freeHead = position;
}

//complexity : Theta(maxCapacity)
void Multime::resize() {
    Node* newElems = new Node[maxCapacity * 2];
    for(int i=0;i<maxCapacity;i++) {
        newElems[i] = nodes[i];
    }
    for(int i=maxCapacity;i<2 * maxCapacity - 1;i++)
        newElems[i].next = i + 1;
    newElems[2 * maxCapacity - 1].next = NULL_TELEM;
    freeHead = maxCapacity;
    maxCapacity*=2;
    delete[] nodes;
    nodes = newElems;
}

//complexity : data de metoda cauta
//Overall : O(n)
bool Multime::adauga(TElem elem) {
    if(cauta(elem))
        return false;
    int new_elem = allocate();
    if(new_elem == NULL_TELEM){
        resize();
        new_elem = allocate();
    }
    nodes[new_elem].data = elem;
    if(length==0){
            head = new_elem;
            length++;
            return true;
    }
    else{
        nodes[new_elem].next = head;
        head = new_elem;
        length++;
        return true;
    }
}

//complexity : Best case : Theta(1)
// Worst case : Theta(n)
// Average case : Theta(n)
// Overall : O(n)
bool Multime::sterge(TElem elem) {
	if(!cauta(elem))
        return false;
    int currentNode = head;
    int previousNode = NULL_TELEM;
    while(currentNode!=NULL_TELEM && nodes[currentNode].data!=elem){
        previousNode = currentNode;
        currentNode = nodes[currentNode].next;
    }
    if(currentNode!=NULL_TELEM){
        if(currentNode == head){
            head = nodes[currentNode].next;
        }else {
            nodes[previousNode].next = nodes[currentNode].next;
        }
        free(currentNode);
        length--;
        return true;
    }else{
        return false;
    }
}

//complexity : Best case : Theta(1)
// Worst case : Theta(n)
// Average case : Theta(n)
// Overall: O(n)
bool Multime::cauta(TElem elem) const {
    int currentNode = head;
    while (currentNode!=NULL_TELEM){
        if(nodes[currentNode].data == elem)
            return true;
        currentNode = nodes[currentNode].next;
    }
    return false;
}

//complexity : Theta(1)
int Multime::dim() const {
	return length;
}

//complexity : Theta(1)
bool Multime::vida() const {
	return length==0;
}

/*
 *Functia diferenta(Multime& m)
 * curerentNode : IteratorMultime <- m.iterator()
 * cnt <- 0
 * cat timp currentNode.valid() executa
 *     int elem <- currentNode.element()
 *     daca cauta(elem) executa
 *           cnt <- cnt + 1
 *           sterge(elem)
 *     sfDaca
 *     currentNode.urmamtor()
 * sfCatTimp
 * difernta <- cnt
 * sfFunctie
 * complexitate : Best Case : Theta(m)
 * Worst case : Theta(m*n)
 * Average case : Theta(m*N)
 * Overall : O(m*n), m - dim m, n - dim this.dictionar
  */
int Multime::diferenta(Multime &m) {
    IteratorMultime currentNode = m.iterator();
    int cnt = 0;
    while(currentNode.valid()){
        int elem = currentNode.element();
        if(cauta(elem)){
            cnt++;
            sterge(elem);
        }
        currentNode.urmator();
    }
    return cnt;
}

//complexity : Theta(1)
Multime::~Multime(){
    delete[] nodes;
}

//complexity : Theta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

