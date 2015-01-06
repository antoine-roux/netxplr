#include "main.h"

#include <string.h>
#include <string>
#include <fstream>

#include "../common/snmp.h"
#include "../common/primitives/macaddr.h"
#include "../common/primitives/ipaddr.h"

void append_oid_mac(macaddr_t mac, oid* oid_out, size_t* oid_len) {
	for (unsigned char byte : mac.address) {
		oid_out[(*oid_len)++] = byte;
	}
}

void read_conf(const char* file) {
	ifstream conf(file);

	string line;
	while (conf >> line) {
		if (! line.length()) continue;

		if (line[0] == '#') continue;
		if (line[0] == ';') continue;

		int posEqual = line.find('=');
		string name, value;
		name  = line.substr(0, posEqual);
		value = line.substr(posEqual + 1);

		confMap[name] = value;
	}

	string snmp_server, snmp_community;
	snmp_server = confMap["server"];
	snmp_community = confMap["community"];

	SNMP& snmpSession = SNMP::getInstance();
	snmpSession.init(snmp_server.c_str(), snmp_community.c_str());
}

extern "C" {
	void load() {
	}

	void unload() {
	}

	void initialize(const char* conf_file) {
		read_conf(conf_file);
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
