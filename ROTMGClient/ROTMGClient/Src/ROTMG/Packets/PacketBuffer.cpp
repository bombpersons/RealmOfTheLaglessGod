#include <ROTMG/Packets/PacketBuffer.hpp>
using namespace rotmg;

#include <cstring>

#include <Misc/Endian.hpp>

/// Constructors
PacketBuffer::PacketBuffer(unsigned int _bufsize, IPacketReader* _reader) {
	// Allocate the buffer.
	buffer = new char[_bufsize];
	bufSize = _bufsize;

	// Set default values.
	lastPacketOffset = 0;
	bufferPointer = 0;
	packetSize = 0;

	// Set the packetreader
	reader = _reader;
}

/// Destructor
PacketBuffer::~PacketBuffer() {
	delete [] buffer;
}

/// Read
void PacketBuffer::Read(char* _buf, unsigned int _size) {
	// If the packet size is 0 then this is the start of a new packet.
	if (packetSize == 0) {
		packetSize = *(unsigned int*)_buf;
		Endian::EndianSwap(packetSize);
	}

	// See how much of this we should write..
	if (bufferPointer + _size > packetSize) { // There is too much to write.
		// Write that much and then we can form a packet.
		memcpy(buffer + bufferPointer, _buf, packetSize - bufferPointer);

		// Now create a packet using that.
		Packet pac(buffer, packetSize);
		if (reader) reader->RecievePacket(pac);

		// Okay now we can dispose of that.
		bufferPointer = 0;
		packetSize = 0;
	}
}