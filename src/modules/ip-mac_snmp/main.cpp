#include "main.h"

#include <string.h>
#include <string>
#include <fstream>

#include "../common/snmp.h"
#include "../common/primitives/macaddr.h"
#include "../common/primitives/ipaddr.h"

void append_oid_ip(ipaddr_t ip, oid* oid_out, size_t* oid_len) {
	for (unsigned char byte : ip.address) {
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
