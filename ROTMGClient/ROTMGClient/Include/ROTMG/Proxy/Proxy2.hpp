#ifndef ROTMG_PROXY
#define ROTMG_PROXY

#define SFML_STATIC
#include <SFML/Network.hpp>

#include <ROTMG/Encryption/Encryption.hpp>
#include <ROTMG/Packets/PacketBuffer.hpp>

#include <fstream>

namespace rotmg {
	class InReader;
	class OutReader;
	class Proxy {
	public:
		Proxy();
		virtual ~Proxy();

		// Intialize
		void SetServerIp(const std::string& _ip);

		// Start the proxy.
		void Start();
		
		// Stop the proxy.
		void Stop();

		// Wait for the proxy.
		void Wait();

		// Threads for different connections.		
		
		// The authorization port (843)
		void AuthConn();
		void AuthSend();

		// The data port (2050)
		void DataConn();
		void DataSend();		

		// Outgoing and incoming data..
		virtual void Incoming(Packet& _pac);
		virtual void Outgoing(Packet& _pac);

	private:
		// The threads.
		sf::Thread authconn, authsend;
		sf::Thread dataconn, datasend;

		// The connections
		sf::TcpListener authlistener;
		sf::TcpListener datalistener;
		sf::TcpSocket authsendsocket, authconnsocket;
		sf::TcpSocket datasendsocket, dataconnsocket;

		// The ip address of the server.
		std::string serverip;

		// Whether or not we are running
		bool running; 

		// An encryption object to use to decrypt packets.
		Encryption encryption;

		// Incoming and outgoing packet buffers.
		PacketBuffer incomingBuffer;
		PacketBuffer outgoingBuffer;

		// Logging file.
		std::ofstream outlog;
		std::ofstream inlog;
	};

	class InReader : public IPacketReader {
	public:
		// Constructor
		InReader(Proxy* _proxy) {
			proxy = _proxy;
		}
		virtual ~InReader() {
		}

		// Read the packet.
		virtual void RecievePacket(Packet& _packet) {
			proxy->Incoming(_packet);
		}

	private:
		Proxy* proxy;
	};

	class OutReader : public IPacketReader {
	public:
		// Constructor
		OutReader(Proxy* _proxy) {
			proxy = _proxy;
		}
		virtual ~OutReader() {
		}

		// Read the packet.
		virtual void RecievePacket(Packet& _packet) {
			proxy->Outgoing(_packet);
		}

	private:
		Proxy* proxy;
	};
}

#endif