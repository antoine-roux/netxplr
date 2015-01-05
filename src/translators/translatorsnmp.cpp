#include "translatorsnmp.h"

#include <dlfcn.h>

#include "../model/ipaddress.h"

const char* TranslatorSnmp::INIT_FUNCTION = "snmp_initialize";

TranslatorSnmp::TranslatorSnmp(const char* modulePath, IpAddress snmpServer, const char* snmpCommunity) :
	Translator(modulePath),
	snmpServer(snmpServer),
	snmpCommunity(snmpCommunity)
{

	this->_initialize = (snmp_initialize_t*)dlsym(this->moduleHandle,
			TranslatorSnmp::INIT_FUNCTION);
	if (!this->_initialize)
		throw "Impossible de charger snmp_initialize";

	this->initialize();
}

void TranslatorSnmp::initialize() {
	this->_initialize(this->snmpServer.getPrimitive(), this->snmpCommunity);
}

IpAddress TranslatorSnmp::getSnmpServer() {
	return this->snmpServer;
}

const char* TranslatorSnmp::getSnmpCommunity() {
	return this->snmpCommunity;
}
