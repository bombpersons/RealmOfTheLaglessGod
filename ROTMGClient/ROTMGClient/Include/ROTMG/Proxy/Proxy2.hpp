#ifndef ROTMG_PROXY
#define ROTMG_PROXY

#define SFML_STATIC
#include <SFML/Network.hpp>

#include <ROTMG/Encryption/Encryption.hpp>

namespace rotmg {
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
		virtual void Incoming(char* _buf, unsigned int _size);
		virtual void Outgoing(char* _buf, unsigned int _size);

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
	};
}

#endif