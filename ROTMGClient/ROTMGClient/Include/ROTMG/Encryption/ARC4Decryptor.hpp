#ifndef ROTMG_ARC4DECRYPTOR
#define ROTMG_ARC4DECRYPTOR

#include <ROTMG/Encryption/ARC4.hpp>

namespace rotmg {
	class Arc4Decryptor : public Arc4 {
	public:
		Arc4Decryptor();
		virtual ~Arc4Decryptor();
	};
}

#endif