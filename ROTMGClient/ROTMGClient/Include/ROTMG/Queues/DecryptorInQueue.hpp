#ifndef ROTMG_DECRYPTORINQUEUE
#define ROTMG_DECRYPTORINQUEUE

#include <ROTMG/Encryption/ARC4Decryptor.hpp>
#include <ROTMG/Encryption/ARC4Encryptor.hpp>
#include <ROTMG/Queues/InQueue.hpp>

namespace rotmg {
	class DecryptorInQueue : public InQueue {
	public:
		DecryptorInQueue(unsigned int _bufSize) : InQueue(_bufSize) {}
		DecryptorInQueue(unsigned int _bufSize, sf::TcpSocket* _socket) : InQueue(_bufSize, _socket) {}
		virtual ~DecryptorInQueue() {}

		// Decrypt packets when they are received.
		virtual void OnReceive(ByteBuffer& _t) {
			ByteBuffer t = _t;
			arc4.Encrypt((unsigned char*)t.GetBufferData(), (unsigned char*)_t.GetBufferData(), t.GetBufferSize());
		}

	private:
		Arc4Decryptor arc4;
	};
}

#endif