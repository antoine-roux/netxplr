#ifndef NX_MODEL_USER_H
#define NX_MODEL_USER_H

#include <string>

using namespace std;

class User {
	public:
		User();
		~User();

		string getName();

	private:
		string value;
};

#endif
