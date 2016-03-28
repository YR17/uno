#ifndef CONNECTION_MANAGER_HPP
	#define CONNECTION_MANAGER_HPP
	#include <sfml/Network.hpp>
	#include <iostream>
	#include <queue>
	class ConnectionManager{
		static ConnectionManager *pInstance;
		sf::TcpSocket socket;
		std::queue<std::string> messages;
		ConnectionManager();
		sf::Thread sendThread;
		void sendData();
		sf::TcpSocket::Status connect();
		std::string message;
		bool isSending;
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