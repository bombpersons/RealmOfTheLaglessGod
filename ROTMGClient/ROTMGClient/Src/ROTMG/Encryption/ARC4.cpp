#include <ROTMG/Encryption/ARC4.hpp>
using namespace rotmg;

// Static variables
unsigned char Arc4::encryptionkey[] = {0x72, 0xC5, 0x58, 0x3C, 0xaf, 0xb6, 0x81, 0x89, 0x95, 0xCB, 0xD7, 0x4B, 0x80};
unsigned char Arc4::decryptionkey[] = {0x31, 0x1F, 0x80, 0x69, 0x14, 0x51, 0xC7, 0x1B, 0x09, 0xA1, 0x3A, 0x2A, 0x6E}; 

// Encryption Key
const unsigned char* Arc4::GetEncryptionKey() {
	return encryptionkey;
}
unsigned int Arc4::GetEncryptionKeySize() {
	return sizeof(encryptionkey);
}

// Decryption Key
const unsigned char* Arc4::GetDecryptionKey() {
	return decryptionkey;
}
unsigned int Arc4::GetDecryptionKeySize() {
	return sizeof(decryptionkey);
}

// Constructor
Arc4::Arc4() {
}
Arc4::Arc4(const unsigned char* _key, unsigned int _size) {
	SetKey(_key, _size);
}

// Destructor
Arc4::~Arc4() {
}

// Set the key
void Arc4::SetKey(const unsigned char* _key, unsigned int _size) {
	arc4.set_key((Botan::byte*)_key, _size);
}

// Encrypt stuff
void Arc4::Encrypt(unsigned char* _inBuf, unsigned char* _outBuf, unsigned int _size) {
	arc4.cipher((Botan::byte*)_inBuf, (Botan::byte*)_outBuf, _size);
}

