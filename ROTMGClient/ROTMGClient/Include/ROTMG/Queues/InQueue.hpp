#ifndef ROTMG_INQUEUE
#define ROTMG_INQUEUE

#include <string>
#include <concurrent_queue.h>
#include <SFML/Network.hpp>
#include <Misc/Logger/Logger.hpp>
#include <ROTMG/Queues/ByteBuffer.hpp>

namespace rotmg {
	/// This queue will listen to socket and fill up a queue with the resultant packets.
	class InQueue {
	private:
		// Vars
		Concurrency::concurrent_queue<ByteBuffer> queue;

		// A listener and a socket to listen on.
		sf::TcpSocket* socket;

		// A buffer to put the data from the socket into.
		unsigned char* buffer;
		unsigned int bufferSize;

		// Whether or not the inqueue is running
		bool running;

		// The thread running the socket receiving.
		sf::Thread thread;
	public:
		// Constructors
		InQueue(unsigned int _bufSize, sf::TcpSocket* _socket) 
			: thread(&InQueue::Run, this) {
			Init();
			SetBufferSize(_bufSize);
			Connect(_socket);
		}
		InQueue(unsigned int _bufSize)
			: thread(&InQueue::Run, this) {
			Init();
			SetBufferSize(_bufSize);
		}
		// Destructor
		virtual ~InQueue() {
			if (buffer) delete [] buffer;
		}

		// Init
		void Init() {
			buffer = 0;
			socket = 0;
			running = false;
		}

		// Set the current buffer size.
		void SetBufferSize(unsigned int _bufSize) {
			if (buffer) delete [] buffer;
			buffer = new unsigned char[_bufSize];
			bufferSize = _bufSize;
		}

		// Listen
		void Connect(sf::TcpSocket* _socket) {
			if (socket) {
				socket->disconnect();
				if (!running)
					delete socket;
			}
			socket = _socket;
		}

		// Pop a packet off the queue.
		bool PopBack(ByteBuffer& _t) {
			return queue.try_pop(_t);
		}

		// Push a packet onto the queue.
		void PushFront(const ByteBuffer& _packet) {
			queue.push(_packet);
		}

		// Start the thread.
		void Start() {
			running = true;
			thread.launch();
		}

		// Wait for the queue to finish.
		void Wait() {
			thread.wait();
		}

		// Return whether or not this queue is running
		bool IsRunning() {
			return running;
		}

		// Get the size of the queue (unsafe)
		unsigned int GetQueueLength() {
			return queue.unsafe_size();
		}

		// Called when a packet is popped from the queue.
		virtual void OnReceive(ByteBuffer& _t) {
			// Decrypt the packet or something here.
		}

	protected:
		// Let the queue run and listen to the connection.
		void Run() {
			while (running) {
				// Receive a packet.
				unsigned int size;
				sf::Socket::Status stat;
				stat = socket->receive(buffer, bufferSize, size);
				if (stat != sf::Socket::Status::Done) {
					// ERROR
					Logger::Trace("Error receiving packet on %s:%u.\n", socket->getRemoteAddress().toString().c_str(), socket->getLocalPort());

					// Error! Disconnect!
					if (stat != sf::Socket::Status::Disconnected) {
						socket->disconnect();
						Logger::Trace("Connection was disconnected on %s:%u.\n", socket->getRemoteAddress().toString().c_str(), socket->getLocalPort());
					}
					
					// Delete the socket
					delete socket;

					// Stop this thread.
					running = false;
					return;
				}

				// Make a ByteBuffer with this data.
				ByteBuffer t;
				t.Fill((char*)buffer, size);
				OnReceive(t);
				PushFront(t);
			}
		}
	};
}

#endif