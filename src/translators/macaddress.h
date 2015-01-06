#ifndef NX_TRANSLATOR_MACADDRESS_H
#define NX_TRANSLATOR_MACADDRESS_H

#include "translator.h"

#include "../primitives/macaddr.h"
#include "../primitives/ipaddr.h"
#include "../model/macaddress.h"
#include "../model/ipaddress.h"

typedef long int lookup_mac_t(macaddr_t mac);

class MacAddressTranslator : public Translator {
	public:
		MacAddressTranslator(const char* modulePath, const char* confPath);

		long int translate(MacAddress mac);

	private:
		static const char* LOOKUP_FUNCTION;
		lookup_mac_t* _lookupMac;
};

#endif
