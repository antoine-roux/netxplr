#include "user.h"

#include <string>

User::User() {
	this->value = "Furr";
}

User::~User() {
}

string User::getName() {
	return this->value;
}
