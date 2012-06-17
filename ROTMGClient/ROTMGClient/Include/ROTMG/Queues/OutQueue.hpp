#ifndef ROTMG_OUTQUEUE
#define ROTMG_OUTQUEUE

#include <SFML/Network.hpp>
#include <Misc/Logger/Logger.hpp>
#include <concurrent_queue.h>
#include <ROTMG/Queues/ByteBuffer.hpp>

namespace rotmg {
	// A queue of packets to be sent via a socket.
	class OutQueue {
	public:
		// Constructors
		OutQueue()
			: thread(&OutQueue::Run, this) {
			Init();
		}
		OutQueue(const std::string& _ip, unsigned short _port) 
			: thread(&OutQueue::Run, this) {
			Init();
			Connect(_ip, _port);
		}
		virtual ~OutQueue() {
		}

		// Init
		void Init() {
			running = false;
		}

		// Connect to a server.
		void Connect(const std::string& _ip, unsigned short _port) {
			socket.connect(sf::IpAddress(_ip), _port);
		}

		// Start the queue.
		void Start() {
			running = true;
			thread.launch();
		}

		// Wait for the queue
		void Wait() {
			thread.wait();
		}

		// Push something onto the queue.
		void Push(const ByteBuffer& _t) {
			queue.push(_t);
		}

		// Get whether or not we are running
		bool IsRunning() {
			return running;
		}

		// Called when a packet is about to be sent. Override this method to do something interesting if you want.
		virtual bool OnSendPacket(ByteBuffer& _t) {
			return true; // Return false if you don't want to send the packet.
		}

	protected:
		// Pop something of the queue
		bool Pop(ByteBuffer& _t) {
			return queue.try_pop(_t);
		}

		// The function the thread runs.
		void Run() {
			while (running) {
				// Try wait for something to be put onto the queue.
				ByteBuffer t;
				if (Pop(t)) {
					if (OnSendPacket(t)) {
						sf::Socket::Status stat = socket.send(t.GetBufferData(), t.GetBufferSize());
						if (stat != sf::Socket::Status::Done) {
							Logger::Trace("Couldn't send packet to %s:%i", socket.getRemoteAddress(), socket.getLocalPort());
							socket.disconnect();
							running = false;
						}
					} else {
						Logger::Trace("Packet was rejected before being sent to %s:%i", socket.getRemoteAddress(), socket.getLocalPort());
					}
				}
			}
		}

	private:
		// The concurrent queue.
		Concurrency::concurrent_queue<ByteBuffer> queue;

		// The socket we are connected to.
		sf::TcpSocket socket;

		// The thread.
		sf::Thread thread;

		// Whether or not we are running
		bool running;
	};
}

#endif