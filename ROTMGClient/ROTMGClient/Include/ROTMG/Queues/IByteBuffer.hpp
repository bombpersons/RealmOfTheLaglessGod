#ifndef ROTMG_IBYTEBUFFER
#define ROTMG_IBYTEBUFFER

namespace rotmg {
	class IByteBuffer {
	public:
		IByteBuffer() {}
		virtual ~IByteBuffer() {};

		// Receive data.
		virtual void Fill(char* _buffer, unsigned int _size) = 0;

		// Get the data.
		virtual char* GetBufferData() = 0;
		virtual unsigned int GetBufferSize() = 0;
	};
}

#endif