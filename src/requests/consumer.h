#ifndef NX_CONSUMER_H
#define NX_CONSUMER_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>

#include "../translators/ipaddress.h"
#include "../translators/macaddress.h"

using namespace std;

class Consumer {
	public:
		Consumer();
		~Consumer();
		void push(string ip);
		bool empty();

	private:
		thread runner;
		bool poison_pill = false;

		queue<string> waitingList;
		mutex list_mutex;
		condition_variable signal;
		mutex signal_mutex;

		IpAddressTranslator ipTranslator;
		MacAddressTranslator macTranslator;

		void run();
		void process(string ip);
};

#endif
