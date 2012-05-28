#include <ROTMG/Packets/Packet.hpp>
using namespace rotmg;

#include <iostream>
#include <cstring>
#include <Misc/Endian.hpp>

/// Constructor
Packet::Packet() {
	memset(this, 0, sizeof(Packet));
}
Packet::Packet(char* _buf, unsigned int _size) {
	Fill(_buf, _size);
}

/// Fill
void Packet::Fill(char* _buf, unsigned int _size) {
	// Get the size of the packet.
	size = *(int*)_buf;
	Endian::EndianSwap(*(unsigned int*)&size);
	_buf += sizeof(int);

	// Get the id.
	id = *_buf; _buf++;

	// Fill the rest
	memcpy(data, _buf, size - 5);
}