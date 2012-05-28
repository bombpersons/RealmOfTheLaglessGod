#ifndef ROTMG_PACKETDECRYPTOR
#define ROTMG_PACKETDECRYPTOR

#include <ROTMG/Packets/Packet.hpp>
#include <ROTMG/Encryption/Encryption.hpp>

namespace rotmg {
	class PacketDecryptor {
	public:
		static Packet DecryptInPacket(const Packet& _pac, Encryption& _enc);
		static Packet DecryptOutPacket(const Packet& _pac, Encryption& _enc);
		static Packet EncryptPacket(const Packet& _pac, Encryption& _enc);

	private:
		PacketDecryptor();
		PacketDecryptor(const PacketDecryptor& _copy);
	};
}

#endif