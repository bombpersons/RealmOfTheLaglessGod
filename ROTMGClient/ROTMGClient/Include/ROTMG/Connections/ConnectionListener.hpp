#ifndef ROTMG_CONNECTIONLISTENER
#define ROTMG_CONNECTIONLISTENER

#include <sfml/Network.hpp>
#include <Misc/Logger/Logger.hpp>

namespace rotmg {
	class ConnectionListener {
	public:
		ConnectionListener(unsigned short _port);
		ConnectionListener();
		virtual ~ConnectionListener();

		// Set which port to listen to.
		void Listen(unsigned short _port);

		// Start the connection listener.
		void Start();

		// Wait for the connection listener.
		void Wait();

		// Check if the connection listener is running
		bool IsRunning();

		// When a new connection is received.
		virtual bool OnNewConnection(sf::TcpSocket* _socket);

	protected:
		// The function that will run when the thread is run.
		void Run();

	private:
		// Whether or not the listener is running
		bool running;

		// The listener
		sf::TcpListener listener;

		// The listener thread.
		sf::Thread thread;
	};
}

#endif