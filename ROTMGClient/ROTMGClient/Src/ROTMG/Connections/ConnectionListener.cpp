#include <ROTMG/Connections/ConnectionListener.hpp>
using namespace rotmg;

// Constructors
ConnectionListener::ConnectionListener(unsigned short _port)
	: thread(&ConnectionListener::Run, this) {
	Listen(_port);
}
ConnectionListener::ConnectionListener()
	: thread(&ConnectionListener::Run, this) {
}

// Destructor
ConnectionListener::~ConnectionListener() {
}

// Listen
void ConnectionListener::Listen(unsigned short _port) {
	listener.listen(_port);
}

// Start
void ConnectionListener::Start() {
	running = true;
	thread.launch();
}

// Wait
void ConnectionListener::Wait() {
	thread.wait();
}

// Check if the listener is running
bool ConnectionListener::IsRunning() {
	return running;
}

// This function is called when a new connection is received.
bool ConnectionListener::OnNewConnection(sf::TcpSocket* _socket) {
	// Returning false here means that we are rejecting this connection.
	return false;
}

// Run
void ConnectionListener::Run() {
	// Run for as long as the running flag lets us.
	while (running) {
		// Try to accept a socket from the listener.
		sf::TcpSocket* socket = new sf::TcpSocket();
		sf::Socket::Status stat = listener.accept(*socket);
		if (stat != sf::Socket::Status::Done) {
			Logger::Trace("An error occurred when accepting a connection on port %u.\n", listener.getLocalPort());
			
			// Delete the socket.
			delete socket;
		} else {
			// Send this as a new connection
			if (!OnNewConnection(socket)) {
				Logger::Trace("Connection on port %u was rejected.\n", listener.getLocalPort());
				delete socket;
			} else {
				Logger::Trace("Connection on port %u was accepted.\n", listener.getLocalPort());
			}
		}
	}
}