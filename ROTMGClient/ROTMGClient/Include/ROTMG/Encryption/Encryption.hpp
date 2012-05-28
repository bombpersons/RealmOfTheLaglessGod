#ifndef ROTMG_ENCRYPTION
#define ROTMG_ENCRYPTION

#include <string>

// RSA
#include <Botan/rsa.h>
#include <Botan/pubkey.h>
#include <Botan/auto_rng.h>

// ARC4
#include <ARC4/ARC4.hpp>

// Base64
#include <Base64/Base64.hpp>

namespace rotmg {
	class Encryption {
	public:
		// Constructors
		Encryption();
		Encryption(const std::string& _filename);
		virtual ~Encryption();

		// Load the encryption keys from a file.
		void LoadFrom(const std::string& _filename);

		// Encrypt using the RSA public key
		unsigned int EncryptRSA(unsigned char* _inBuffer, int _inBufSize, unsigned char* _outBuffer, int _outBufSize);

		// ARC4 encryption (for outgoing packets)
		void EncryptARC4(unsigned char* _inBuffer, unsigned char* _outBuffer, int _bufSize);

		// ARC4 decryption (for incoming packets)
		void DecryptARC4(unsigned char* _inBuffer, unsigned char* _outBuffer, int _bufSize);
		
	private:
		// The Decryption ARC4 Key (for incoming traffic)
		static unsigned char decryptionARC4[];
		ARC4 arc4Dec;

		// The Encryption ARC4 Key (for outgoing traffic)
		static unsigned char encryptionARC4[];
		ARC4 arc4Enc;

		// The public key (RSA). 
		Botan::X509_PublicKey* publickey;

		// The object used to encrypt rsa
		Botan::PK_Encryptor_EME* encryptor;
	};
}

#endif