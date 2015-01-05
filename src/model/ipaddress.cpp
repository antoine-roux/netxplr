#include "ipaddress.h"

#include <string>
#include <sstream>
#include <arpa/inet.h>

#include "../primitives/ipaddr.h"

IpAddress::IpAddress(const char* str) {
	if (!inet_pton(AF_INET, str, this->primitive.address))
		throw "Impossible de traiter l'IP";
}

IpAddress::IpAddress(ipaddr_t primitive) {
	this->primitive = primitive;
}

IpAddress::~IpAddress() {
}

ipaddr_t IpAddress::getPrimitive() {
	return this->primitive;
}

unsigned long IpAddress::toUNumeric() {
	unsigned long ret = 0;
	for (unsigned char byte : this->primitive.address) {
		ret = (ret << 8) + byte;
	}

	return ret;
}

string IpAddress::toString() {
	stringstream ret;
	for (unsigned char& byte : this->primitive.address) {
		// Marque des . sauf pour le premier
		if (&byte != &(this->primitive.address[0]))
			ret << ".";

		ret << (int)byte;
	}

	return ret.str();
}

string IpAddress::toOIDSuffix() {
	stringstream ret;
	for (unsigned char byte : this->primitive.address) {
		ret << "." << (int)byte;
	}

	return ret.str();
}
