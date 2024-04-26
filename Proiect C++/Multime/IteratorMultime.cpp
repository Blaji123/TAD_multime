#include <exception>
#include "IteratorMultime.h"
#include "Multime.h"

//complexity : Theta(1)
IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	currentElem = multime.head;
}

//complexity : Theta(1)
void IteratorMultime::prim() {
	currentElem = multime.head;
}

//complexity : Theta(1)
void IteratorMultime::urmator() {
	if(valid()){
        currentElem = multime.nodes[currentElem].next;
    }else{
        throw std::exception();
    }
}

//complexity : Theta(1)
TElem IteratorMultime::element() const {
	if(valid()){
        return multime.nodes[currentElem].data;
    }else{
        throw std::exception();
    }
}

bool IteratorMultime::valid() const {
	if(currentElem != NULL_TELEM)
        return true;
    return false;
}
