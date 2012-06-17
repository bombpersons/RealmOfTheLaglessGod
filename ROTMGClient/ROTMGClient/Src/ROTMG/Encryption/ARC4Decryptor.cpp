#include <ROTMG/Encryption/ARC4Decryptor.hpp>
using namespace rotmg;

// Constructor
Arc4Decryptor::Arc4Decryptor() 
	: Arc4(Arc4::GetDecryptionKey(), Arc4::GetDecryptionKeySize()) {
}

// Destructor
Arc4Decryptor::~Arc4Decryptor() {
}