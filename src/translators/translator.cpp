#include "translator.h"

#include <dlfcn.h>

const char* Translator::INIT_FUNCTION = "initialize";

Translator::Translator(const char* modulePath, const char* confPath) :
	confPath(confPath)
{
	this->moduleHandle = dlopen(modulePath, RTLD_LAZY);
	if (!this->moduleHandle) {
		//TODO: Declencher une erreur personalisee
		throw dlerror();
	}

	this->_initialize = (initialize_t*)dlsym(this->moduleHandle,
			Translator::INIT_FUNCTION);
	if (!this->_initialize)
		throw "Impossible de charger initialize";

	this->initialize();
}

Translator::~Translator() {
	if (this->moduleHandle)
		dlclose(this->moduleHandle);
}

void Translator::initialize() {
	this->_initialize(this->confPath);
}
