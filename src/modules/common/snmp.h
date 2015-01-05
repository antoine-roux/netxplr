#ifndef NX_SNMP_H
#define NX_SNMP_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include "primitives/macaddr.h"

class SNMP {
	public:
		static SNMP& getInstance();
		void init(const char* server, const char* community);
		
		macaddr_t getFirstMac(const oid* objid, size_t objid_len);
		long int getFirstInteger(const oid* objid, size_t objid_len);
		void getNextOID(const oid* objid, size_t objid_len);

	private:
		SNMP& operator=(const SNMP&){}
		SNMP(const SNMP&){}
		SNMP();
		~SNMP();

		static SNMP instance;

		struct snmp_session *ss;
};


#endif
