#include "main.h"

#include <string.h>

#include "../common/snmp.h"
#include "../common/primitives/macaddr.h"
#include "../common/primitives/ipaddr.h"

using namespace std;

void append_oid_mac(macaddr_t mac, oid* oid_out, size_t* oid_len) {
	for (unsigned char byte : mac.address) {
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
	
	long int lookup_mac(macaddr_t mac) {
		if (!initialized)
			throw "Non initialisé";

		SNMP& snmpSession = SNMP::getInstance();

		// Forge l'OID PortFwd
		oid oid_port[MAX_OID_LEN];
		size_t len_port = len_port_table;

		memcpy(oid_port, oid_port_table, sizeof(oid_port_table));
		append_oid_mac(mac, oid_port, &len_port);
		long int port = snmpSession.getFirstInteger(oid_port, len_port);

		// Forge l'OID Interface Index
		oid oid_ifidx[MAX_OID_LEN];
		size_t len_ifidx = len_ifindex_table;

		memcpy(oid_ifidx, oid_ifindex_table, sizeof(oid_ifindex_table));
		oid_ifidx[len_ifidx++] = port;

		return snmpSession.getFirstInteger(oid_ifidx, len_ifidx);
	}
}
