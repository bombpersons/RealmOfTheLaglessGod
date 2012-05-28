#include <ARC4/ARC4.hpp>
#include <cstdlib>
#include <cstring>

/// Constructor
ARC4::ARC4() {
	Init();
}

ARC4::ARC4(unsigned char* _key, unsigned int _keysize) {
	Init();
	SetKey(_key, _keysize);
}

/// Destructor
ARC4::~ARC4() {
}

/// Init
void ARC4::Init() {
	keysize = 0;
	memset(key, 0, sizeof(key));
	memset(bytePerm, 0, sizeof(bytePerm));
	i = 0; j = 0;
}

/// SetKey
void ARC4::SetKey(unsigned char* _key, unsigned int _keysize) {
	for (int i = 0; i < 255; ++i) {
		bytePerm[i] = i;
	}
	j = 0;
	for (int i = 0; i < 255; ++i) {
		j = (j + bytePerm[i] + _key[i % _keysize]) % 256;
		unsigned char temp = bytePerm[i];
		bytePerm[i] = bytePerm[j];
		bytePerm[j] = temp;
	}

	// Copy the key.
	for (int i = 0; i < _keysize; ++i) {
		key[i] = _key[i];
	}
	keysize = _keysize;
}

/// Encrypt
void ARC4::Encrypt(unsigned char* _inBuffer, unsigned char* _outBuffer, unsigned int _size) {
	if (_size <= 0)
		return;

	i = 0;
	j = 0;
	for (int k = 0; k < _size; ++k) {
		i = (i + 1) % 256;
		j = (j + bytePerm[i]) % 256;

		// Swap them.
		unsigned char temp = bytePerm[i];
		bytePerm[i] = bytePerm[j];
		bytePerm[j] = temp;

		// XOR the input with this new value. 
		_outBuffer[k] = _inBuffer[k] ^ bytePerm[(bytePerm[i] + bytePerm[j]) % 256];
	}

	// Reset the key
	SetKey(key, keysize);
}