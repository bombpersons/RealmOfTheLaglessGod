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
		void EncryptRSA(char* _inBuffer, int _inBufSize, char* _outBuffer, int _outBufSize);

		// ARC4 encryption (for outgoing packets)
		void EncryptARC4(char* _inBuffer, int _inBufSize, char* _outBuffer, int _outBufSize);

		// ARC4 decryption (for incoming packets)
		void DecryptARC4(char* _inBuffer, int _inBufSize, char* _outBuffer, int _outBufSize);
		
	private:
		// The Decryption ARC4 Key (for incoming traffic)
		unsigned char decryptionARC4[256];
		unsigned int decryptionARC4size;

		// The Encryption ARC4 Key (for outgoing traffic)
		unsigned char encryptionARC4[256];
		unsigned int encryptionARC4size;

		// The public key (RSA). 
		Botan::RSA_PublicKey publickey;
	};
}

#endif