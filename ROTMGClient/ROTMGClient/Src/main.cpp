#include <iostream>

#include <ROTMG/Encryption/Encryption.hpp>
#include <ROTMG/Proxy/Proxy2.hpp>
#include <ROTMG/Queues/InQueue.hpp>
#include <ROTMG/Connections/ConnectionListener.hpp>
#include <concurrent_vector.h>

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

class Listener : public rotmg::ConnectionListener {
public:
	Listener() {}
	virtual ~Listener() {}

	// What to do when we get a new connection
	virtual bool OnNewConnection(sf::TcpSocket* _socket) {
		rotmg::InQueue<TempPacket>* queue = new rotmg::InQueue<TempPacket>(1024 * 1024, _socket);
		queue->Start();
		queues.push_back(queue);
		return true;
	}

	// A method that will print all of the information from all clients to the console.
	void PrintStuff() {
		while (IsRunning()) {
			for (VectorType::iterator it = queues.begin(); it != queues.end(); ++it) {
				TempPacket packet;
				if ((*it)->PopBack(packet)) {
					Logger::TraceBuffer(packet.buffer, packet.bufSize);
				}
			}
		}
	}

private:
	// A list of connections to update from.
	typedef Concurrency::concurrent_vector<rotmg::InQueue<TempPacket>* > VectorType;
	VectorType queues;
};

int main(int _argc, char** _argv) {
	
	// Start the proxy
	//rotmg::Proxy proxy;
	//proxy.SetServerIp("176.34.240.11");
	//proxy.Start();
	//proxy.Wait();

	Listener listener;
	listener.Listen(800);
	listener.Start();
	listener.PrintStuff();

	int i;
	std::cin >> i;
}