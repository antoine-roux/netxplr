#ifndef NX_IPMAC_H
#define NX_IPMAC_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include "../common/primitives/macaddr.h"
#include "../common/primitives/ipaddr.h"

const oid oid_if_table[]	= {1, 3, 6, 1, 2, 1, 2, 2, 1, 1};
const oid oid_arp_table[]	= {1, 3, 6, 1, 2, 1, 4, 22, 1 ,2};

const size_t len_if_table	= sizeof(oid_if_table)	/ sizeof(oid);
const size_t len_arp_table	= sizeof(oid_arp_table)	/ sizeof(oid);

bool initialized = false;
void append_oid_ip(ipaddr_t ip, oid* oid_out, size_t* oid_len);

extern "C" {
	void __attribute__ ((constructor)) load(void);
	void __attribute__ ((destructor)) unload(void);

	void snmp_initialize(ipaddr_t snmp_server, const char* snmp_community);
	macaddr_t lookup_ip(ipaddr_t ip);
}

#endif
