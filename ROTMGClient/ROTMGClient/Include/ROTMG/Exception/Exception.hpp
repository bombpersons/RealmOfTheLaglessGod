#ifndef ROTMG_EXCEPTION
#define ROTMG_EXCEPTION

#include <string>

namespace rotmg {
	class Exception {
	public:
		Exception(const std::string& _msg = "An unhandled exception occurred!");
		virtual ~Exception();
	private:

	};
}

#endif