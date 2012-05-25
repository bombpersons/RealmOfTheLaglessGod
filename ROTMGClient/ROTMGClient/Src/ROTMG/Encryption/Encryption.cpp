#include <ROTMG/Encryption/Encryption.hpp>
using namespace rotmg;

/// Constructor
Encryption::Encryption()
	: publickey(Botan::BigInt(), Botan::BigInt()) {
}

// Load from a file.
Encryption::Encryption(const std::string& _name)
	: publickey(Botan::BigInt(), Botan::BigInt()) {
	LoadFrom(_name);
}

// Load from a file
void Encryption::LoadFrom(const std::string& _filename) {
	// Open the file.

}

// Encrypt RSA
void Encryption::EncryptRSA(char* _inBuffer, int _inBufSize, char* _outBuffer, int _outBufSize) {

}