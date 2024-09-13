// Exception classes

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
using namespace std;

class InvalidUserInput : public exception {
public:
	InvalidUserInput(const char* error) : exception(error) {}
};

class InvalidStackFormat : public exception {
public:
	InvalidStackFormat(const char* error) : exception(error) {}
};

class Underflow : public exception {
public:
	Underflow() : exception() {}
};

#endif