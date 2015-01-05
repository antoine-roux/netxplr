#ifndef NX_TRANSLATOR_MACADDRESS_H
#define NX_TRANSLATOR_MACADDRESS_H

#include "translatorsnmp.h"

#include "../primitives/macaddr.h"
#include "../primitives/ipaddr.h"
#include "../model/macaddress.h"
#include "../model/ipaddress.h"

typedef long int lookup_mac_t(macaddr_t mac);

class MacAddressTranslator : TranslatorSnmp {
	public:
		MacAddressTranslator(const char* modulePath, IpAddress snmpServer, const char* snmpCommunity);

		long int translate(MacAddress mac);

	private:
		static const char* LOOKUP_FUNCTION;
		lookup_mac_t* _lookupMac;
};

#endif
