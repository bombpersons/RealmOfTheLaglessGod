#include <ROTMG/Proxy/Proxy.hpp>
using namespace rotmg;

#include <iostream>

#include <ROTMG/Exception/Exception.hpp>

/// Constructor
Proxy::Proxy() {
	running = false;
}

Proxy::Proxy(const std::string& _serverIp) {
	running = false;
	Init(_serverIp);
}

/// Destructor
Proxy::~Proxy() {
}

/// Init
void Proxy::Init(const std::string& _serverIp) {
	// Connect.
	sf::Socket::Status stat;
	stat = listener.listen(ROTMG_PROXY_OTHERPORT);
	if (stat != sf::Socket::Status::Done) {
		char buffer[256];
		sprintf(buffer, "Couldn't listen on port %i", ROTMG_PROXY_OTHERPORT);
		throw Exception(buffer);
	}
	std::cout << "Listening on port " << ROTMG_PROXY_OTHERPORT << std::endl;
	
	stat = send.connect(sf::IpAddress(_serverIp.c_str()), ROTMG_PROXY_OTHERPORT);
	if (stat != sf::Socket::Status::Done) {
		char buffer[256];
		sprintf(buffer, (std::string("Couldn't connect to server ") + _serverIp + " on port %i").c_str(), ROTMG_PROXY_OTHERPORT);
		throw Exception(buffer);
	}
	std::cout << "Connected to " << _serverIp << ":" << ROTMG_PROXY_OTHERPORT << std::endl;

	// We should be connected now.
	// Ready to go!
}

/// Run
void Proxy::Run() {
	running = true;

	listener.accept(connection);

	// Run another thread for the server sending us stuff.
	sf::Thread serverOne(&Proxy::SendOne, this);
	serverOne.launch();

	while (running) {
		sf::Packet packet;
		sf::Socket::Status stat;

		char buf[1024 * 100]; memset(buf, 0, sizeof(buf));
		unsigned int size = 0;
		stat = connection.receive(buf, sizeof(buf), size);

		if (size > 0) {
			std::cout << connection.getLocalPort() << " Client to " << send.getRemotePort() << ": " << buf << std::endl;
			std::cout << "Size: " << size << std::endl;
			stat = send.send(buf, size);
		}
	}
}

void Proxy::Receive() {
	while (running) {
		sf::Packet packet;
		sf::Socket::Status stat;

		char buf[1024 * 100]; memset(buf, 0, sizeof(buf));
		unsigned int size = 0;
		stat = connectionOne.receive(buf, sizeof(buf), size);
		
		if (size > 0) {
			std::cout << connectionOne.getLocalPort() << " Client to " << othersend.getRemotePort() << ": " << buf << std::endl;
			std::cout << "Size: " << size << std::endl;
			stat = othersend.send(buf, size);
		}
	}
}

void Proxy::Send() {
	while (running) {
		sf::Socket::Status stat;
		char buf[1024 * 100]; memset(buf, 0, sizeof(buf));
		unsigned int size = 0;
		stat = othersend.receive(buf, sizeof(buf), size);

		if (size > 0) {
			std::cout << othersend.getRemotePort() << " Server to " << connectionOne.getLocalPort() << ": " << buf << std::endl;
			std::cout << "Size: " << size << std::endl;
			stat = connectionOne.send(buf, size);
		}
	}
}

void Proxy::SendOne() {
	sf::Thread server(&Proxy::Send, this);
	sf::Thread receive(&Proxy::Receive, this);
	while (running) {
		sf::Socket::Status stat;
		char buf[1024 * 100]; memset(buf, 0, sizeof(buf));
		unsigned int size = 0;
		stat = send.receive(buf, sizeof(buf), size);

		if (size > 0) {
			std::cout << send.getRemotePort() << " Server to " << connection.getLocalPort() << ": " << buf << std::endl;
			std::cout << "Size: " << size << std::endl;
			stat = connection.send(buf, size);
		}

		if (strstr(buf, "<") != 0) {
			stat = otherlistener.listen(ROTMG_PROXY_DATAPORT);
			if (stat != sf::Socket::Status::Done) {
				char buffer[256];
				sprintf(buffer, "Couldn't listen on port %i", ROTMG_PROXY_DATAPORT);
				throw Exception(buffer);
			}
			std::cout << "Listening on port " << ROTMG_PROXY_DATAPORT << std::endl;

			sf::IpAddress add = send.getRemoteAddress();
			stat = othersend.connect(add, ROTMG_PROXY_DATAPORT);
			if (stat != sf::Socket::Status::Done) {
				char buffer[256];
				sprintf(buffer, (std::string("Couldn't connect to server ") + add.toString() + " on port %i").c_str(), ROTMG_PROXY_DATAPORT);
				throw Exception(buffer);
			}
			std::cout << "Connected to " << add.toString() << ":" << ROTMG_PROXY_DATAPORT << std::endl;

			otherlistener.accept(connectionOne);
			server.launch();
			receive.launch();
		}
	}
}