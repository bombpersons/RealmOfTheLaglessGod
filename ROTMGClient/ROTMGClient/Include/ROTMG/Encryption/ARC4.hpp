#ifndef ROTMG_ARC4
#define ROTMG_ARC4

#include <Botan/arc4.h>

namespace rotmg {
	class Arc4 {
	public:
		Arc4();
		Arc4(const unsigned char* _key, unsigned int _size);
		virtual ~Arc4();

		// Set the key.
		void SetKey(const unsigned char* _key, unsigned int _size);

		// Encrypt
		void Encrypt(unsigned char* _inBuf, unsigned char* _outBuf, unsigned int _size);
		
		// Static keys
		static unsigned char encryptionkey[];
		static const unsigned char* GetEncryptionKey();
		static unsigned int GetEncryptionKeySize();

		static unsigned char decryptionkey[];
		static const unsigned char* GetDecryptionKey();
		static unsigned int GetDecryptionKeySize();

	private:
		Botan::ARC4 arc4;
	};
}

#endif