#include "ipaddress.h"

#include <dlfcn.h>

#include "../model/macaddress.h"
#include "../model/ipaddress.h"

const char* IpAddressTranslator::LOOKUP_FUNCTION = "lookup_ip";

IpAddressTranslator::IpAddressTranslator(const char* modulePath, const char* confPath) :
	Translator(modulePath, confPath)
{
	this->lookupIp = (lookup_ip_t*)dlsym(this->moduleHandle,
			IpAddressTranslator::LOOKUP_FUNCTION);
}

MacAddress IpAddressTranslator::translate(IpAddress ip) {
	//TODO: Gestion de l'erreur
	return MacAddress(this->lookupIp(ip.getPrimitive()));
}
