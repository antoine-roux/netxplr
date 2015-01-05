#ifndef NX_TRANSLATOR_H
#define NX_TRANSLATOR_H

class Translator {
	public:
		Translator(const char* modulePath);
		~Translator();

	protected:
		void* moduleHandle;
};

#endif
