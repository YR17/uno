#ifndef CONNECTION_STATE_HPP
	#define CONNECTION_STATE_HPP
	#include <states/State.hpp>
	#include <managers/ConnectionManager.hpp>
	#include <string>
	class ConnectionState: public State{
	ConnectionManager *connectionManager;
	bool isSent;
	std::string nickname;
	public:
		ConnectionState(std::string);
		void draw();
		void event(sf::Event);
		void tick(int);
	};
#endif