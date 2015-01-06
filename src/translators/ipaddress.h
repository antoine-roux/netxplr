#ifndef NX_TRANSLATOR_IPADDRESS_H
#define NX_TRANSLATOR_IPADDRESS_H

#include "translator.h"

#include "../primitives/macaddr.h"
#include "../primitives/ipaddr.h"
#include "../model/macaddress.h"
#include "../model/ipaddress.h"

typedef macaddr_t lookup_ip_t(ipaddr_t ip);

class IpAddressTranslator : public Translator {
	public:
		IpAddressTranslator(const char* modulePath, const char* confPath);

		MacAddress translate(IpAddress ip);

	private:
		static const char* LOOKUP_FUNCTION;
		lookup_ip_t* lookupIp;
};

#endif
