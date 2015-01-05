#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

#include "main.h"
#include "requests/consumer.h"

using namespace std;

int main() {
	Consumer consumer;

	// Servers
	for (int i = 129; i < 191; i++) {
		stringstream ip;
		ip << "152.77.130." << i;
		consumer.push(ip.str());
	}

	// Clients
	for (int i = 1; i < 255; i++) {
		stringstream ip;
		ip << "152.77.131." << i;
		consumer.push(ip.str());
	}

	// CERMO
	for (int i = 1; i < 255; i++) {
		stringstream ip;
		ip << "152.77.132." << i;
		consumer.push(ip.str());
	}

	// VLAN104
	for (int i = 1; i < 255; i++) {
		stringstream ip;
		ip << "192.168.104." << i;
		consumer.push(ip.str());
	}

	return 0;
}
