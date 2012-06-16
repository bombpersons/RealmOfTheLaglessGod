#ifndef ROTMG_PACKET
#define ROTMG_PACKET

namespace rotmg {
	struct Packet {
		Packet();
		Packet(char* _buf, unsigned int _size);

		// Fill the packet using a buffer.
		void Fill(char* _buf, unsigned int _size);

		// THIS IS THE HEADER FOR THE PACKET.
		int size; // The size of the whole packet, in bytes.
		unsigned char id; // The identifier for the packet.

		char data[100 * 1024]; // This is the data for the packet.
							   // It is encoded using ARC4.
							   // Use the packet decryptor to decrypt packets.

	};
}

#endif