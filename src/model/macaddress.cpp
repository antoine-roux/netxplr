#include "macaddress.h"

#include <string>
#include <sstream>
#include <iomanip>

#include "../primitives/macaddr.h"

MacAddress::MacAddress() {
	//TODO: Supprimer
	this->primitive.address[0] = 0x00;
	this->primitive.address[1] = 0x02;
	this->primitive.address[2] = 0x0F;
	this->primitive.address[3] = 0x00;
	this->primitive.address[4] = 0x05;
	this->primitive.address[5] = 0x08;
}

MacAddress::MacAddress(macaddr_t primitive) {
	this->primitive = primitive;
}

MacAddress::~MacAddress() {
}

macaddr_t MacAddress::getPrimitive() {
	return this->primitive;
}

unsigned long long MacAddress::toUNumeric() {
	unsigned long long ret = 0;
	for (unsigned char byte : this->primitive.address) {
		ret = (ret << 8) + byte;
	}

	return ret;
}

string MacAddress::toString() {
	stringstream ret;
	for (unsigned char& byte : this->primitive.address) {
		// Marque des : sauf pour le premier
		if (&byte != &(this->primitive.address[0]))
			ret << ":";

		ret << hex << setfill('0') << setw(2);
		ret << (int)byte;
	}

	return ret.str();
}

string MacAddress::toOIDSuffix() {
	stringstream ret;
	for (unsigned char byte : this->primitive.address) {
		ret << "." << (int)byte;
	}

	return ret.str();
}
