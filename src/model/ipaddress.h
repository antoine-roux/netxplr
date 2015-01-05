#ifndef NX_MODEL_IPADDRESS_H
#define NX_MODEL_IPADDRESS_H

#include <string>

#include "../primitives/ipaddr.h"

using namespace std;

class IpAddress {
	public:
		IpAddress(const char* str);
		IpAddress(ipaddr_t primitive);
		~IpAddress();

		ipaddr_t getPrimitive();

		unsigned long toUNumeric();
		string toString();
		string toOIDSuffix();

	private:
		ipaddr_t primitive;
};

#endif
