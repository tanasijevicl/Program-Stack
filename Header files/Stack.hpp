// STACK realized as an abstract data structure (temlate class)
// Note: When creating a template class the entire code must be in one file

#ifndef STACK_HPP
#define STACK_HPP

#include "ElemType.hpp"
#include "Exceptions.hpp"


// Declaration: 

template <typename Type>
class Stack {
public:
	Stack();
	~Stack();

	void push(Type t);
	Type pop();
	Type readTop();
	bool empty();

private:
	Elem<Type>* top_ = nullptr;
};

// Implementation:

template <typename Type>
Stack<Type>::Stack() {
	top_ = nullptr;
}

template <typename Type>
Stack<Type>::~Stack() {
	while (top_) {
		Elem<Type>* old = top_;
		top_ = top_->next;
		delete old;
	}
}

template <typename Type>
void Stack<Type>::push(Type t) {
	Elem<Type>* elem = new Elem<Type>();
	elem->next = top_;
	elem->t = t;
	top_ = elem;
}

template <typename Type>
Type Stack<Type>::pop() {
	if (top_) {
		Elem<Type>* elem = top_;
		Type t = top_->t;
		top_ = top_->next;
		delete elem;
		return t;
	}
	else throw Underflow();
}

template <typename Type>
Type Stack<Type>::readTop() {
	if (top_) return top_->t;
	else throw Underflow();
}

template <typename Type>
bool Stack<Type>::empty() {
	if (top_ == nullptr) return true;
	else return false;
}

#endif
