#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "macaddr.h"

using namespace std;

macaddr_t macaddr_fsstr(unsigned char* data, size_t length) {
	if (length != MACADDR_LEN)
		throw "Unexpected data length";

	macaddr_t ret;
	memcpy(ret.address, data, length);
	return ret;
}

const char* macaddr_cstr(macaddr_t mac) {
	char* buff = new char[18];
	sprintf(buff, "%02x:%02x:%02x:%02x:%02x:%02x",
			mac.address[0], mac.address[1], mac.address[2],
			mac.address[3], mac.address[4], mac.address[5]);

	return (const char*)buff;
}

const char* macaddr_coid(macaddr_t mac) {
	char* buff = new char[24];
	sprintf(buff, "%d.%d.%d.%d.%d.%d",
			mac.address[0], mac.address[1], mac.address[2],
			mac.address[3], mac.address[4], mac.address[5]);

	return (const char*)buff;
}
