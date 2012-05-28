#ifndef ENDIAN
#define ENDIAN

class Endian {
public:
	// Swap an unsigned int.
	static inline void EndianSwap(unsigned int& x)
	{
		x = (x>>24) | 
			((x<<8) & 0x00FF0000) |
			((x>>8) & 0x0000FF00) |
			(x<<24);
	}

private:
	Endian();
	Endian(const Endian& _endian);
};

#endif