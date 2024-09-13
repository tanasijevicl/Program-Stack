// Element (struct) for singly linked list, with "universal" data

#ifndef ELEM_TYPE_HPP
#define ELEM_TYPE_HPP

template <typename Type>
struct Elem {
	Type t;
	Elem* next = nullptr;
};

#endif
