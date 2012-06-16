#include <Misc/Logger/Logger.hpp>

// Construtor
Logger::Logger() {}
Logger::Logger(const Logger& _cpy) {}

// Destructor
Logger::~Logger() {}

// Trace
void Logger::Trace(const char* _string, ...) {
	// A character buffer
	char buffer[256];
	
	// Start the va list and do the dealy majigs.
	va_list va;
	va_start(va, _string);
	vsnprintf(buffer,sizeof(buffer), _string, va);
	va_end(va);

	// Trace this.
	TraceText(buffer);
}

// Trace
void Logger::TraceText(const char* _string) {
	printf(_string);
}

// Trace Buffer
void Logger::TraceBuffer(const char* _string, unsigned int _size) {
	fwrite(_string, 1, _size, stdout);
}