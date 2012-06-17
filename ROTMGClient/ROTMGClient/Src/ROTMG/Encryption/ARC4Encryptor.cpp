#include <ROTMG/Encryption/ARC4Encryptor.hpp>
using namespace rotmg;

// Constructor
Arc4Encryptor::Arc4Encryptor() 
	: Arc4(Arc4::GetEncryptionKey(), Arc4::GetEncryptionKeySize()) {
}

// Destructor
Arc4Encryptor::~Arc4Encryptor() {
}