#ifndef ARC4_ARC4
#define ARC4_ARC4

class ARC4 {
public:
	ARC4();
	ARC4(unsigned char* _key, unsigned int _keysize);
	~ARC4();

	// Init
	void Init();

	// Set the key.
	void SetKey(unsigned char* _key, unsigned int _keysize);

	// Encrypte method.
	void Encrypt(unsigned char* _inBuffer, unsigned char* _outBuffer, unsigned int _size);

private:
	// All permutations of 8 bits.
	unsigned char bytePerm[256];

	// 2 index pointers.
	unsigned char i, j;

	// The key
	unsigned char key[256];
	unsigned int keysize;
};

#endif