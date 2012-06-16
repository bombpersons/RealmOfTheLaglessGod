#include <iostream>

#include <ROTMG/Encryption/Encryption.hpp>
#include <ROTMG/Proxy/Proxy2.hpp>
#include <ROTMG/Queues/InQueue.hpp>

class TempPacket {
public:
	// Vars
	char* buffer;
	unsigned int bufSize;

	// Constructor
	TempPacket() {
		buffer = 0;
		bufSize = 0;
	}
	TempPacket(const char* _buffer, unsigned int _bufSize) {
		buffer = new char[_bufSize];
		bufSize = _bufSize;
		memcpy(buffer, _buffer, _bufSize);
	}
	~TempPacket() {
		if (buffer) delete [] buffer;
	}

	void Copy(const TempPacket& _cpy) {
		buffer = new char[_cpy.bufSize];
		bufSize = _cpy.bufSize;
		memcpy(buffer, _cpy.buffer, _cpy.bufSize);
	}
	TempPacket(const TempPacket& _cpy) {
		Copy(_cpy);
	}
	TempPacket& operator = (const TempPacket& _cpy) {
		Copy(_cpy);
		return *this;
	}
};

int main(int _argc, char** _argv) {
	
	// Start the proxy
	//rotmg::Proxy proxy;
	//proxy.SetServerIp("176.34.240.11");
	//proxy.Start();
	//proxy.Wait();

	sf::TcpListener listener;
	sf::TcpSocket* socket = new sf::TcpSocket();
	listener.listen(800);
	Logger::Trace("Listening to port 800\n");
	listener.accept(*socket);
	Logger::Trace("Connection established!\n");

	rotmg::InQueue<TempPacket> q(1024 * 1024);
	q.Connect(socket);
	q.Start();
	while (q.IsRunning()) {
		TempPacket packet;
		if (q.PopBack(packet)) {
			Logger::TraceBuffer(packet.buffer, packet.bufSize);
		}
	}

	int i;
	std::cin >> i;
}