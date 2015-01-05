#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "ipaddr.h"

using namespace std;

ipaddr_t ipaddr_fsstr(unsigned char* data, size_t length) {
	if (length != IPADDR_LEN)
		throw "Unexpected data length";

	ipaddr_t ret;
	memcpy(ret.address, data, length);
	return ret;
}

const char* ipaddr_cstr(ipaddr_t ip) {
	char* buff = new char[16];
	sprintf(buff, "%d.%d.%d.%d",
			ip.address[0], ip.address[1],
			ip.address[2], ip.address[3]);

	return (const char*)buff;
}

const char* ipaddr_coid(ipaddr_t ip) {
	return ipaddr_cstr(ip);
}
