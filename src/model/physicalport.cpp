#include "physicalport.h"

#include <string>

PhysicalPort::PhysicalPort() {
}

PhysicalPort::~PhysicalPort() {
}

string PhysicalPort::getPort() {
	return this->value;
}

string PhysicalPort::toString() {
	return this->value;
}
