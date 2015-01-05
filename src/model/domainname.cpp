#include "domainname.h"

#include <string>

DomainName::DomainName() {
	this->value = "antoine-roux.fr";
}

DomainName::~DomainName() {
}

string DomainName::getDomainName() {
	return this->value;
}
