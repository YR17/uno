#ifndef CONNECTION_MANAGER_HPP
	#define CONNECTION_MANAGER_HPP
	#include <sfml/Network.hpp>
	#include <string>
	#include <queue>
	class ConnectionManager{
		static ConnectionManager *pInstance;
		sf::TcpSocket socket;
		std::queue<std::string> receivedMessages;
		std::queue<std::string> messagesToSend;
		ConnectionManager();
		sf::Thread sendThread;
		void sendData();
		sf::TcpSocket::Status connect();
		void disconnect();
	public:
		static ConnectionManager *getInst();
		void send(std::string);
		void receive();
		// bool isError();
		bool isConnected();
		bool isReceived();
		std::string getLastMessage();
	};
#endif