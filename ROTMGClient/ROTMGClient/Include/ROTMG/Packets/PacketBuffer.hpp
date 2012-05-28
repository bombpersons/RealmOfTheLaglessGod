#ifndef ROTMG_PACKETBUFFER
#define ROTMG_PACKETBUFFER

#include <ROTMG/Packets/Packet.hpp>

namespace rotmg {
	// Interface for reading packets.
	class IPacketReader {
	public:
		IPacketReader() {}
		virtual ~IPacketReader() {}

		// Recieve a packet
		virtual void RecievePacket(Packet& _packet) = 0;
	};

	// The packet buffer will buffer data until a full packet is available.
	class PacketBuffer {
	public:
		// Constructors
		PacketBuffer(unsigned int _bufSize, IPacketReader* _reader);
		virtual ~PacketBuffer();

		// Read in some data.
		void Read(char* _data, unsigned int _size);
		
	private:
		// The packetreader to use.
		IPacketReader* reader;

		// The buffer to store stuffs in.
		char* buffer;
		unsigned int bufSize;

		// The pointer in the buffer.
		unsigned int bufferPointer;

		// The start of the last packet..
		unsigned int lastPacketOffset;

		// The size of the current packet.
		unsigned int packetSize;
	};
}

#endif