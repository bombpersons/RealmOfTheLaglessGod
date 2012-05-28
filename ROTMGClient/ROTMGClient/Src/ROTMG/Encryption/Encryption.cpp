#include <ROTMG/Encryption/Encryption.hpp>
using namespace rotmg;

#include <Botan/pkcs8.h>
#include <Botan/x509_key.h>

#include <fstream>

// The ARC4 keys
unsigned char Encryption::decryptionARC4[] = {0x72, 0xC5, 0x58, 0x3C, 0xaf, 0xb6, 0x81, 0x89, 0x95, 0xCB, 0xD7, 0x4B, 0x80};
unsigned char Encryption::encryptionARC4[] = {0x31, 0x1F, 0x80, 0x69, 0x14, 0x51, 0xC7, 0x1B, 0x09, 0xA1, 0x3A, 0x2A, 0x6E}; 

/// Constructor
Encryption::Encryption() {
	publickey = 0;
	encryptor = 0;
}

// Load from a file.
Encryption::Encryption(const std::string& _name) {
	publickey = 0;
	encryptor = 0;
	LoadFrom(_name);
}

// Destructor
Encryption::~Encryption() {
	if (publickey) delete publickey;
	if (encryptor) delete encryptor;
}

// Load from a file
void Encryption::LoadFrom(const std::string& _filename) {
	// Delete the old certificate if it still exists.
	if (publickey) delete publickey;
	
	// Load the rsa certifcate.
	Botan::AutoSeeded_RNG rnd;
	//publickey = (Botan::RSA_PublicKey*)Botan::PKCS8::load_key(_filename, rnd);
	publickey = Botan::X509::load_key(_filename);

	// Create encryptors to use this key.
	if (publickey) {
		if (encryptor) delete encryptor;
		encryptor = new Botan::PK_Encryptor_EME(*publickey, "EME1(SHA-1)");
	}

	// Create the ARC4 encoders
	arc4Dec.SetKey(decryptionARC4, sizeof(decryptionARC4));
	arc4Enc.SetKey(encryptionARC4, sizeof(encryptionARC4));
}

// Encrypt RSA
unsigned int Encryption::EncryptRSA(unsigned char* _inBuffer, int _inBufSize, unsigned char* _outBuffer, int _outBufSize) {
	Botan::AutoSeeded_RNG rnd;
	Botan::SecureVector<Botan::byte> bytes = encryptor->encrypt((Botan::byte*)_inBuffer, _inBufSize, rnd);
	for (int i = 0; i < std::min<unsigned int>(_outBufSize, bytes.size()); ++i) {
		_outBuffer[i] = bytes[i];
	}
	return bytes.size();
}

// ARC4 encryption (for outgoing packets)
void Encryption::EncryptARC4(unsigned char* _inBuffer, unsigned char* _outBuffer, int _bufSize) {
	arc4Enc.Encrypt(_inBuffer, _outBuffer, _bufSize);
}

// ARC4 decryption (for incoming packets)
void Encryption::DecryptARC4(unsigned char* _inBuffer, unsigned char* _outBuffer, int _bufSize) {
	arc4Dec.Encrypt(_inBuffer, _outBuffer, _bufSize);
}