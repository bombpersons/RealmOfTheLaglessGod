#ifndef ROTMG_BYTEBUFFER
#define ROTMG_BYTEBUFFER

#include <ROTMG/Queues/IByteBuffer.hpp>
#include <cstring>

namespace rotmg {
	class ByteBuffer : public IByteBuffer {
	public:
		// Vars
		char* buffer;
		unsigned int bufSize;

		// Constructor
		ByteBuffer() {
			buffer = 0;
			bufSize = 0;
		}
		ByteBuffer(char* _buffer, unsigned int _bufSize) {
			Fill(_buffer, _bufSize);
		}
		~ByteBuffer() {
			if (buffer) delete [] buffer;
		}

		// Fill the buffer.
		virtual void Fill(char* _buffer, unsigned int _bufSize) {
			buffer = new char[_bufSize];
			bufSize = _bufSize;
			memcpy(buffer, _buffer, _bufSize);
		}

		// Get the buffer pointer.
		virtual char* GetBufferData() {
			return buffer;
		}

		// Get the buffer size;
		virtual unsigned int GetBufferSize() {
			return bufSize;
		}

		void Copy(const ByteBuffer& _cpy) {
			buffer = new char[_cpy.bufSize];
			bufSize = _cpy.bufSize;
			memcpy(buffer, _cpy.buffer, _cpy.bufSize);
		}
		ByteBuffer(const ByteBuffer& _cpy) {
			Copy(_cpy);
		}
		ByteBuffer& operator = (const ByteBuffer& _cpy) {
			Copy(_cpy);
			return *this;
		}
	};
}

#endif