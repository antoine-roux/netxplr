#ifndef NX_MODEL_MACADDRESS_H
#define NX_MODEL_MACADDRESS_H

#include <string>

#include "../primitives/macaddr.h"

using namespace std;

class MacAddress {
	public:
		MacAddress();
		MacAddress(macaddr_t primitive);
		~MacAddress();

		macaddr_t getPrimitive();

		unsigned long long toUNumeric();
		string toString();
		string toOIDSuffix();

	private:
		macaddr_t primitive;
};

#endif
