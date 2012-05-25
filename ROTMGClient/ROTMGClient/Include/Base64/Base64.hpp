#ifndef BASE64_BASE64
#define BASE64_BASE64

#include <string>

class Base64 {
public:
	// Decodes a string and puts the decoded data into _buffer. 
	static unsigned int Decode(const std::string& _data, unsigned char* _buffer, int _bufSize);

	// Encodes the buffer and returns the data as a string.
	static bool Encode(unsigned char* _inBuffer, int _inBufSize, unsigned char* _outBuffer, int _outBufSize);

	// A static array to help decoding.
	static unsigned char decode[128];
	// A static array to help encoding.
	static unsigned char encode[64];

private:
	// This is a pure static class.
	Base64() {}
	Base64(const Base64& _base) {}
};

#endif