#include "consumer.h"

//TODO: Remove
#include <iostream>

#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <queue>

#include "../model/macaddress.h"
#include "../model/ipaddress.h"
#include "../translators/ipaddress.h"
#include "../translators/macaddress.h"

Consumer::Consumer() :
	ipTranslator("lib/libip-mac_snmp.so", "etc/ip-mac"),
	macTranslator("lib/libmac-port_snmp.so", "etc/mac-port")
{	
	this->runner = thread(&Consumer::run, this);
}

Consumer::~Consumer() {
	this->poison_pill = true;
	this->signal.notify_all();
	this->runner.join();
}

void Consumer::run() {
	while (!this->poison_pill) {
		unique_lock<mutex> lk(this->signal_mutex);
		this->signal.wait(lk);

		while (!this->waitingList.empty()) {
			string ip;
			{
				lock_guard<mutex> list_guard(this->list_mutex);
				ip = this->waitingList.front();
				this->waitingList.pop();
			}

			this->process(ip);
		}

		lk.unlock();
	}
}

void Consumer::process(string ip) {
	stringstream out;
	out << ip << "\t";
	try {
		MacAddress mac = this->ipTranslator
			.translate(IpAddress(ip.c_str()));
		string strMac = mac.toString();
		out << strMac << "\t";

		try {
			long int port = this->macTranslator
				.translate(mac);

			switch (port) {
				case 49:
					out << "CERMO";
					break;
				case 50:
					out << "Stack RdC";
					break;
				default:
					out << port;
			}
		} catch(...) {
			out << "introuvable";
		}
	} catch(...) {
		out << "introuvable";
	}
	out << endl;
	cout << out.str();
}

void Consumer::push(string ip) {
	lock_guard<mutex> list_guard(this->list_mutex);
	this->waitingList.push(ip);
	this->signal.notify_all();
}

bool Consumer::empty() {
	return this->waitingList.empty();
}
