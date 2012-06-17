#ifndef ROTMG_ARC4ENCRYPTOR
#define ROTMG_ARC4ENCRYPTOR

#include <ROTMG/Encryption/ARC4.hpp>

namespace rotmg {
	class Arc4Encryptor : public Arc4 {
	public:
		Arc4Encryptor();
		virtual ~Arc4Encryptor();
	};
}

#endif