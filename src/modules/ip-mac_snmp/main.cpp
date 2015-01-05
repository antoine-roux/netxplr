#include "main.h"

#include <string.h>

#include "../common/snmp.h"
#include "../common/primitives/macaddr.h"
#include "../common/primitives/ipaddr.h"

using namespace std;

void append_oid_ip(ipaddr_t ip, oid* oid_out, size_t* oid_len) {
	for (unsigned char byte : ip.address) {
		oid_out[(*oid_len)++] = byte;
	}
}

extern "C" {
	void load() {
	}

	void unload() {
	}

	void snmp_initialize(ipaddr_t snmp_server, const char* snmp_community) {
		SNMP& snmpSession = SNMP::getInstance();
		snmpSession.init(ipaddr_cstr(snmp_server), snmp_community);
		initialized = true;
	}

	macaddr_t lookup_ip(ipaddr_t ip) {
		if (!initialized)
			throw "Non initialisé";
		
		SNMP& snmpSession = SNMP::getInstance();

		oid oid_arp[MAX_OID_LEN];
		size_t len_arp = len_arp_table;

		// Forge l'OID ARP
		// - OID racine
		memcpy(oid_arp, oid_arp_table, sizeof(oid_arp_table));
		// - Index de l'interface
		//   Quelque soit l'interface la réponse est la même
		//   Selectionne l'interface 1
		int if_byte = len_arp++;
		oid_arp[if_byte] = 1;
		// - IP
		append_oid_ip(ip, oid_arp, &len_arp);

		return snmpSession.getFirstMac(oid_arp, len_arp);
	}
}
