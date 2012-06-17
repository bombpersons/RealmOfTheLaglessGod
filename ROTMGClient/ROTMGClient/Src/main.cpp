#include <iostream>

#include <ROTMG/Encryption/Encryption.hpp>
#include <ROTMG/Proxy/Proxy2.hpp>
#include <ROTMG/Queues/InQueue.hpp>
#include <ROTMG/Connections/ConnectionListener.hpp>
#include <ROTMG/Queues/ByteBuffer.hpp>
#include <ROTMG/Queues/OutQueue.hpp>
#include <ROTMG/Queues/EncryptorOutQueue.hpp>
#include <ROTMG/Queues/DecryptorInQueue.hpp>
#include <concurrent_vector.h>

class Listener : public rotmg::ConnectionListener {
public:
	Listener() {}
	virtual ~Listener() {}

	// What to do when we get a new connection
	virtual bool OnNewConnection(sf::TcpSocket* _socket) {
		rotmg::InQueue* queue = new rotmg::DecryptorInQueue(1024, _socket);
		queue->Start();
		queues.push_back(queue);
		return true;
	}

	// A method that will print all of the information from all clients to the console.
	void PrintStuff() {
		while (IsRunning()) {
			for (VectorType::iterator it = queues.begin(); it != queues.end(); ++it) {
				rotmg::ByteBuffer packet;
				if ((*it)->PopBack(packet)) {
					Logger::Trace("Queue size: %u Data: ", (*it)->GetQueueLength());
					Logger::TraceBuffer(packet.buffer, packet.bufSize);
					Logger::Trace("\n");
				}
			}
		}
	}

private:
	// A list of connections to update from.
	typedef Concurrency::concurrent_vector<rotmg::InQueue* > VectorType;
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

	// Create an out queue
	/*rotmg::EncryptorOutQueue out;
	out.Connect("127.0.0.1", 800);
	out.Start();
	rotmg::ByteBuffer test("Testing\n", strlen("Testing\n"));
	while (out.IsRunning()) {
		out.Push(test);
	}*/

	int i;
	std::cin >> i;
}