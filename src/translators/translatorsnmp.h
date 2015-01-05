#ifndef NX_TRANSLATORSNMP_H
#define NX_TRANSLATORSNMP_H

#include "translator.h"

#include "../primitives/ipaddr.h"
#include "../model/ipaddress.h"

typedef void snmp_initialize_t(ipaddr_t snmp_server, const char* snmp_community);

class TranslatorSnmp : public Translator {
	public:
		TranslatorSnmp(const char* modulePath, IpAddress snmpServer, const char* snmpCommunity);

		IpAddress getSnmpServer();
		const char* getSnmpCommunity();

	private:
		static const char* INIT_FUNCTION;
		snmp_initialize_t* _initialize;
		void initialize();

		IpAddress snmpServer;
		const char* snmpCommunity;
};

#endif
