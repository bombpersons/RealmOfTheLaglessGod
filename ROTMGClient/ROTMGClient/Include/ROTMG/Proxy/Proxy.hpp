#ifndef ROTMG_PROXY
#define ROTGM_PROXY

#include <string>

#define SFML_STATIC
#include <SFML/Network.hpp>

#define ROTMG_PROXY_DATAPORT 2050
#define ROTMG_PROXY_OTHERPORT 843

namespace rotmg {
	class Proxy {
	public:
		Proxy();
		Proxy(const std::string& _serverIp);
		virtual ~Proxy();

		// Init
		void Init(const std::string& _serverIp);

		// Run the proxy
		void Run();

		// Run the data port
		void ListenOne();

		void Send();
		void SendOne();
		void Receive();

	private:
		// The connections.
		sf::TcpListener listener;
		sf::TcpListener otherlistener;
		sf::TcpSocket send;
		sf::TcpSocket othersend;
		sf::TcpSocket connection;
		sf::TcpSocket connectionOne;

		// Whether or not we are running.
		bool running;
	};
}

#endif