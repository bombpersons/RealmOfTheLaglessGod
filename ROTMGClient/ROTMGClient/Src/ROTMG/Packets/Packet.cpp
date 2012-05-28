#include <ROTMG/Packets/Packet.hpp>
using namespace rotmg;

#include <iostream>
#include <cstring>

/// Constructor
Packet::Packet() {
	memset(this, 0, sizeof(Packet));
}
Packet::Packet(char* _buf, unsigned int _size) {
	Fill(_buf, _size);
}

inline void endian_swap(unsigned int& x)
{
    x = (x>>24) | 
        ((x<<8) & 0x00FF0000) |
        ((x>>8) & 0x0000FF00) |
        (x<<24);
}

/// Fill
void Packet::Fill(char* _buf, unsigned int _size) {
	FILE* file = fopen("test", "w");
	fwrite(_buf, 1, _size, file);
	fclose(file);

	// Get the size of the packet.
	size = *(int*)_buf;
	endian_swap(*(unsigned int*)&size);
	//size = _size;

	_buf += sizeof(int);

	// Get the id.
	id = *_buf; _buf++;

	// Fill the rest
	memcpy(data, _buf, size - 5);
}