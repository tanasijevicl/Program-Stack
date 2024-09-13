// QUEUE realized as an abstract data structure (temlate class)
// Note: When creating a template class the entire code must be in one file

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "ElemType.hpp"
#include "Exceptions.hpp"

// Declaration: 

template <typename Type>
class Queue {
public:
	Queue();
	~Queue();

	void insert(Type t);
	Type remove();
	Type readNext();
	bool empty();

private:
	Elem<Type>* front_ = nullptr;
	Elem<Type>* rear_ = nullptr;
};

// Implementation:

template <typename Type>
Queue<Type>::Queue() {
	front_ = nullptr;
	rear_ = nullptr;
}

template <typename Type>
Queue<Type>::~Queue() {
	while (front_) {
		Elem<Type>* old = front_;
		front_ = front_->next;
		delete old;
	}
}

template <typename Type>
void Queue<Type>::insert(Type t) {
	Elem<Type>* newElem = new Elem<Type>();
	newElem->t = t;

	if (rear_) {
		rear_->next = newElem;
		rear_ = rear_->next;
	}
	else {
		front_ = rear_ = newElem;
	}
}

template <typename Type>
Type Queue<Type>::remove() {
	if (front_) {
		Elem<Type>* elem = front_;
		Type t = elem->t;
		front_ = front_->next;
		delete elem;
		if (front_ == nullptr) rear_ = nullptr;
		return t;
	}
	else throw Underflow();
}

template <typename Type>
Type Queue<Type>::readNext() {
	if (front_) return front_->t;
	else throw Underflow();
}

template <typename Type>
bool Queue<Type>::empty() {
	return front_ == nullptr;
}

#endif

