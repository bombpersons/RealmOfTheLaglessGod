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
	// Loop through the data until we have written all of it.
	/*unsigned int written = 0;
	while (written < _size) {
		// If we are at the start of a packet, the get the packet size.
		packetSize = *(int*)(_buf + written);
		Endian::EndianSwap(*(unsigned int*)&packetSize);

		// Write this.
		Packet pac(_buf + written, packetSize);
		if (reader) reader->RecievePacket(pac);

		// Inc written
		written += packetSize;
	}*/
	
	// See how much of this we should write..
	unsigned int written = 0;
	while (written < _size) {
		// If we are at the start of a packet.
		if (packetSize == 0) {
			packetSize = *(int*)(_buf + written);
			Endian::EndianSwap(*(unsigned int*)&packetSize);
		}

		// Write enough for a packet.
		if (bufferPointer + _size >= packetSize) { // There is too much to write.
			// Write that much and then we can form a packet.
			memcpy(buffer + bufferPointer, _buf + written, packetSize - bufferPointer);

			// Now create a packet using that.
			Packet pac(buffer, packetSize);
			if (reader) reader->RecievePacket(pac);

			// Increment written.
			written += packetSize - bufferPointer;

			// Okay now we can dispose of that.
			bufferPointer = 0;
			packetSize = 0;
		} else {
			// Not enough for a full packet.
			memcpy(buffer + bufferPointer, _buf + written, _size - written);
			bufferPointer += _size - written;

			written = _size;
		}
	}
}