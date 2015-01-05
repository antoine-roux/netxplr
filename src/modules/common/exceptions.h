#ifndef NX_EXCEPTION_H
#define NX_EXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

class SNMPNotFound : public exception {
	virtual const char* what() const throw() {
		return "Element introuvable";
	}
};

#endif
