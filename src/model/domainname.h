#ifndef NX_MODEL_DOMAINNAME_H
#define NX_MODEL_DOMAINNAME_H

#include <string>

using namespace std;

class DomainName {
	public:
		DomainName();
		~DomainName();

		string getDomainName();

	private:
		string value;
};

#endif
