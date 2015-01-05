#ifndef NX_MODEL_PHYSICALPORT_H
#define NX_MODEL_PHYSICALPORT_H

#include <string>

using namespace std;

class PhysicalPort {
	public:
		PhysicalPort();
		~PhysicalPort();

		string getPort();
		string toString();

	private:
		string value;
};

#endif
