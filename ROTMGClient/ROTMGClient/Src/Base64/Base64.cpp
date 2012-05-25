#include <Base64/Base64.hpp>
#include <Misc/binary.hpp>
#include <iostream>

unsigned char Base64::decode[128] =  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
									 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63, 52, 53, 54, 55,
									 56, 57, 58, 59, 60, 61, 0, 0, 255, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
									 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0, 0,
									 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
									 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0}; // 255 represents =
unsigned char Base64::encode[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
									'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
									'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
									'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
									'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

unsigned int Base64::Decode(const std::string& _data, unsigned char* _buffer, int _bufSize) {
	// Okay so we need to change every character in the data string
	// Into 6 bits.
	// We also need to put this into a contigous buffer. 

	// Also if we find a "=" character in a 4 character block means that there is only 2 bytes in that block.
	// If we find a "==" then there is only 1 byte in that 4 character block.
	
	// Check the length of the string. If it's not a multiple of 4 then it's not valid.
	if (_data.size() % 4 != 0)
		return 0; // Not valid data.

	// Okay now we loop through each 4 characters and construct the buffer
	int j = 0;
	for (int i = 0; i < _data.size() && j < _bufSize; i += 4) {
		unsigned char one = decode[_data[i]];
		unsigned char two = decode[_data[i + 1]];
		unsigned char three = decode[_data[i + 2]];
		unsigned char four = decode[_data[i + 3]];

		// There will be at least one byte.
		_buffer[j++] = (BYTE(0011, 1111) & one) << 2 | ((BYTE(0011, 0000) & two) >> 4); // The first byte.
		if (three != 255) // The next byte if it exists.
			_buffer[j++] = ((BYTE(0000, 1111) & two) << 4) | ((BYTE(0011, 1100) & three) >> 2); 
		if (four != 255)
			_buffer[j++] = ((BYTE(0000, 0011) & three) << 6) | ((BYTE(0011, 1111) & four));
	}

	// Return how many bytes we wrote.
	return j;
}

bool Base64::Encode(unsigned char* _inBuffer, int _inBufSize, unsigned char* _outBuffer, int _outBufSize) {
	// This function will take arbritary binary data and encode into base64.

	// Loop through the input buffer.
	for (int i = 0, j = 0; i < _inBufSize; j += 4) {
		// Take 3 bytes and encode them into 4 decimals.
		// If don't have enough bytes, put down padding characters.
		if (j + 4 >= _outBufSize)
			return false; // We have no space to encode.

		// Get the first 6 bits from the buffer
		_outBuffer[j] = encode[(_inBuffer[i++] & BYTE(1111, 1100)) >> 2];
		if (i < _inBufSize) // There are more bytes?
			_outBuffer[j + 1] = encode[((_inBuffer[i-1] & BYTE(0000, 0011)) << 4) | ((_inBuffer[i++] & BYTE(1111, 0000)) >> 4)];
 		else {
			_outBuffer[j + 1] = encode[((_inBuffer[i-1] & BYTE(0000, 0011)) << 4)];

			// No more bytes add padding characters
			_outBuffer[j + 2] = '=';
			_outBuffer[j + 3] = '=';
			break;
		}
		if (i < _inBufSize) // More bytes?
			_outBuffer[j + 2] = encode[((_inBuffer[i-1] & BYTE(0000, 1111)) << 2) | ((_inBuffer[i++] & BYTE(1100, 0000)) >> 6)];
		else {
			_outBuffer[j + 2] = encode[((_inBuffer[i-1] & BYTE(0000, 1111)) << 2)];

			// No more bytes add padding character
			_outBuffer[j + 3] = '=';
			break;
		}
		// Get the last character.
		_outBuffer[j + 3] = encode[(_inBuffer[i-1] & BYTE(0011, 1111))];
	}

	return true;
}