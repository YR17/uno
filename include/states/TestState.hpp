#ifndef TEST_STATE_HPP
	#define TEST_STATE_HPP
	#include <states/State.hpp>
#include <managers/ConnectionManager.hpp>
	class TestState: public State{
	ConnectionManager *connectionManager;
	public:
		TestState();
		void draw();
		void event(sf::Event);
		void tick(sf::Time);
	};
#endif