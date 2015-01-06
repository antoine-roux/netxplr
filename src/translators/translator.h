#ifndef NX_TRANSLATOR_H
#define NX_TRANSLATOR_H

typedef void initialize_t(const char* conf_file);

class Translator {
	public:
		Translator(const char* modulePath, const char* confPath);
		~Translator();

	protected:
		void* moduleHandle;

		static const char* INIT_FUNCTION;
		const char* confPath;
		initialize_t* _initialize;
		void initialize();
};

#endif
