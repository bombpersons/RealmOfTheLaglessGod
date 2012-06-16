#ifndef MISC_LOGGER
#define MISC_LOGGER

#include <cstdarg>
#include <cstdio>
#include <string>

class Logger {
public:
	// Log to the logger.
	static void Trace(const char* _string, ...);
	static void TraceText(const char* _string);
	static void TraceBuffer(const char* _string, unsigned int _size);

private:
	Logger();
	Logger(const Logger& _cpy);
	~Logger();
};

#endif