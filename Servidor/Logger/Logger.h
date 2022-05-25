#ifndef _LOGGER_H_
#define _LOGGER_H_

class Logger {
	public:
		static logTxt(const char* tag, const char* mensaje);
		static logConsola(const char* tag, const char* mensaje);
};

#endif