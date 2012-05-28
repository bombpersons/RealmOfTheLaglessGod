#include <ROTMG/Encryption/PacketDecryptor.hpp>
using namespace rotmg;

/// Decrypt a packet.
Packet PacketDecryptor::DecryptInPacket(const Packet& _pac, Encryption& _enc) {
	// Copy the packet.
	Packet pac = _pac;

	// Decrypt the data.
	_enc.DecryptARC4((unsigned char*)_pac.data, (unsigned char*)pac.data, pac.size - 5);

	// Return that packet.
	return pac;
}
Packet PacketDecryptor::DecryptOutPacket(const Packet& _pac, Encryption& _enc) {
	// Copy the packet.
	Packet pac = _pac;

	// Decrypt the data.
	_enc.EncryptARC4((unsigned char*)_pac.data, (unsigned char*)pac.data, pac.size - 5);

	// Return that packet.
	return pac;
}
Packet PacketDecryptor::EncryptPacket(const Packet& _pac, Encryption& _enc) {
	return Packet();
}