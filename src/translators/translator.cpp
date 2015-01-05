#include "translator.h"

#include <dlfcn.h>

Translator::Translator(const char* modulePath) {
	this->moduleHandle = dlopen(modulePath, RTLD_LAZY);
	if (!this->moduleHandle) {
		//TODO: Declencher une erreur personalisee
		throw dlerror();
	}
}

Translator::~Translator() {
	if (this->moduleHandle)
		dlclose(this->moduleHandle);
}
