#include <ROTMG/Proxy/Proxy2.hpp>
using namespace rotmg;

#include <ROTMG/Encryption/PacketDecryptor.hpp>

#include <iostream>
#include <iomanip>

/// Constructors
Proxy::Proxy()
	: authconn(&Proxy::AuthConn, this),
	  authsend(&Proxy::AuthSend, this),
	  dataconn(&Proxy::DataConn, this),
	  datasend(&Proxy::DataSend, this) {
		  running = false;
		  encryption.LoadFrom("Config/publickey.der");
}

/// Destructor
Proxy::~Proxy() {
}

/// Init
void Proxy::SetServerIp(const std::string& _ip) {
	serverip = _ip;
}

/// Start
void Proxy::Start() {
	// Connect to the auth
	sf::Socket::Status stat;
	stat = authsendsocket.connect(sf::IpAddress(serverip.c_str()), 843);
	if (stat != sf::Socket::Status::Done)
		std::cout << "Couldn't connect to " << serverip << ":843..." << std::endl;
	else
		std::cout << "Connected to " << serverip << ":843..." << std::endl;
	stat = authlistener.listen(843);
	if (stat != sf::Socket::Status::Done)
		std::cout << "Could't listen to port 843!" << std::endl;
	else
		std::cout << "Listening to port 843..." << std::endl;
	stat = authlistener.accept(authconnsocket);
	if (stat != sf::Socket::Status::Done)
		std::cout << "Couldn't accept a socket on port 843!" << std::endl;
	else
		std::cout << "Accepted socket on port 843..." << std::endl;

	// Start running
	running = true;

	// Start the auth threads
	authconn.launch();
	authsend.launch();
}

/// Stop
void Proxy::Stop() {
	running = false;
}

/// Wait
void Proxy::Wait() {
	authconn.wait();
	authsend.wait();
	dataconn.wait();
	datasend.wait();
}

// The authorization port (843)
void Proxy::AuthConn() {
	while (running) {
		// Get the data from the connection.
		char buf[100 * 1024]; memset(buf, 0, sizeof(buf));
		unsigned int size;
		authconnsocket.receive(buf, sizeof(buf), size);

		// Print the data.
		if (size > 0) {
			std::cout << "Client Auth(834): Packet Size: " << size << std::endl;
			std::cout << "Client Auth(834): " << buf << std::endl;

			// Send this data to the server.
			authsendsocket.send(buf, size);
		}
	}
}
void Proxy::AuthSend() {
	while (running) {
		// Get the data from the server.
		char buf[100 * 1024]; memset(buf, 0, sizeof(buf));
		unsigned int size;
		authsendsocket.receive(buf, sizeof(buf), size);

		// Print the data.
		if (size > 0) {
			std::cout << "Server Auth(834: Packet Size: " << size << std::endl;
			std::cout << "Server Auth(834): " << buf << std::endl;

			// Send this to the client.
			authconnsocket.send(buf, size);

			// We need to take a peek at this packet to determine whether or not we should
			// start the other threads yet.
			if (strstr(buf, "<") != 0) {
				// This is the reply from the connection policy thing.
				// Connect to the data server.	
				sf::Socket::Status stat;
				stat = datasendsocket.connect(sf::IpAddress(serverip.c_str()), 2050);
				if (stat != sf::Socket::Status::Done)
					std::cout << "Couldn't connect to " << serverip << ":2050..." << std::endl;
				else
					std::cout << "Connected to " << serverip << ":2050..." << std::endl;
				stat = datalistener.listen(2050);
				if (stat != sf::Socket::Status::Done)
					std::cout << "Coulnd't listen to port 2050!" << std::endl;
				else
					std::cout << "Listening to port 2050..." << std::endl;
				stat = datalistener.accept(dataconnsocket);
				if (stat != sf::Socket::Status::Done)
					std::cout << "Couldn't accept a socket on port 2050!" << std::endl;	
				else
					std::cout << "Accepted socket on port 2050" << std::endl;

				// Start the threads.
				datasend.launch();
				dataconn.launch();
			}
		}
	}
}

// The data port (2050)
void Proxy::DataConn() {
	while (running) {
		// Get the data from the connection.
		char buf[100 * 1024]; memset(buf, 0, sizeof(buf));
		unsigned int size;
		dataconnsocket.receive(buf, sizeof(buf), size);

		// Print the data.
		if (size > 0) {
			//std::cout << "Client Data(2050): Packet Size: " << size << std::endl;
			//std::cout << "Client Data(2050): " << buf << std::endl;

			// Outgoing
			Outgoing(buf, size);

			// Send this data to the server.
			datasendsocket.send(buf, size);
		}
	}
}
void Proxy::DataSend() {
	while (running) {
		// Get the data from the server.
		char buf[100 * 1024]; memset(buf, 0, sizeof(buf));
		unsigned int size;
		datasendsocket.receive(buf, sizeof(buf), size);

		// Print the data.
		if (size > 0) {
			//std::cout << "Server Data(2050): Packet Size: " << size << std::endl;
			//std::cout << "Server Data(2050): " << buf << std::endl;

			// Incoming data..
			Incoming(buf, size);

			// Send this to the client.
			dataconnsocket.send(buf, size);
		}
	}
}

// Outgoing and incoming data..
void Proxy::Incoming(char* _buf, unsigned int _size) {
	// Create a packet.
	Packet packet(_buf, _size);

	// Decrypt it.
	Packet dec = PacketDecryptor::DecryptInPacket(packet, encryption);

	// Print this out.
	std::cout << "Decrypted Incoming Data ----------------------" << std::endl;
	std::cout << "Packet Size: " << dec.size << std::endl;
	std::cout << "Packet ID: " << (unsigned int)dec.id << std::endl;
	std::cout << "Packet Data: ";
	for (int i = 0; i < dec.size -5 ; ++i) {
		printf("%c", dec.data[i]);
	}
	printf("\n");
}
void Proxy::Outgoing(char* _buf, unsigned int _size) {
	// Create a packet.
	Packet packet(_buf, _size);

	// Decrypt it.
	Packet dec = PacketDecryptor::DecryptOutPacket(packet, encryption);
	
	// Print this out.
	std::cout << "Decrypted Outgoing Data ----------------------" << std::endl;
	std::cout << "Packet Size: " << dec.size << std::endl;
	std::cout << "Packet ID: " << (unsigned int)dec.id << std::endl;
	std::cout << "Packet Data: ";
	for (int i = 0; i < dec.size -5 ; ++i) {
		printf("%c", dec.data[i]);
	}
	printf("\n");
}