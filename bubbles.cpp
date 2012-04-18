#include "bubbles.h"

Bubbles::Bubbles() {
}

Bubbles::~Bubbles() {
}

void Bubbles::Add(Bubble bub) {
  all_bubbles_.push_back(bub);
}

void Bubbles::Erase(Bubbles::iterator& it) {
  //delete current element and get iterator to the next
  std::list<Bubble>::iterator list_it;
  list_it = all_bubbles_.erase(it.GetListIterator());
  it.SetListIterator(list_it);
}

void Bubbles::Erase(Bubbles::reverse_iterator& it) {
  //get next reverse iterator before we delete current
  Bubbles::reverse_iterator rev_it_next(it);
  ++rev_it_next;
  all_bubbles_.erase(--(it.GetListReverseIterator().base()));
  it = rev_it_next;
}
