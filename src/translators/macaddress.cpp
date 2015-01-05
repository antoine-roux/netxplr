#include "macaddress.h"

#include <dlfcn.h>

#include "../model/ipaddress.h"

const char* MacAddressTranslator::LOOKUP_FUNCTION = "lookup_mac";

MacAddressTranslator::MacAddressTranslator(const char* modulePath, IpAddress snmpServer, const char* snmpCommunity) :
	TranslatorSnmp(modulePath, snmpServer, snmpCommunity)
{
	this->_lookupMac = (lookup_mac_t*)dlsym(this->moduleHandle,
			MacAddressTranslator::LOOKUP_FUNCTION);
}

long int MacAddressTranslator::translate(MacAddress mac) {
	//TODO: Gestion de l'erreur
	return this->_lookupMac(mac.getPrimitive());
}
