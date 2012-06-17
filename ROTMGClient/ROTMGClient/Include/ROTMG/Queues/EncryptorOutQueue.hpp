#ifndef ROTMG_ENCRYPTOROUTQUEUE
#define ROTMG_ENCRYPTOROUTQUEUE

#include <ROTMG/Queues/OutQueue.hpp>
#include <ROTMG/Encryption/ARC4Encryptor.hpp>

namespace rotmg {
	class EncryptorOutQueue : public OutQueue {
	public:
		EncryptorOutQueue() {}
		EncryptorOutQueue(const std::string& _ip, unsigned short _port) : OutQueue(_ip, _port) {}
		virtual ~EncryptorOutQueue() {}

		// Encrypt the packets as they get sent.
		virtual bool OnSendPacket(ByteBuffer& _t) {
			// Encrypt the packet.
			ByteBuffer t = _t;
			arc4.Encrypt((unsigned char*)t.GetBufferData(), (unsigned char*)_t.GetBufferData(), _t.GetBufferSize());
			return true;
		}

	private:
		// An arc4 encryptor
		Arc4Encryptor arc4;
	};
}

#endif