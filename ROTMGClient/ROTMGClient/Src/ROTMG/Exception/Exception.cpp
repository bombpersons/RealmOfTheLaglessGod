#include <ROTMG/Exception/Exception.hpp>
using namespace rotmg;


// If we are on windows...
#ifdef _WIN32
#include <Windows.h>
#endif

/// Exception
Exception::Exception(const std::string& _msg) {
#ifdef _WIN32
	MessageBoxA(NULL, _msg.c_str(), "Exception!", 0);
#endif
}

/// Destructor
Exception::~Exception() {
}