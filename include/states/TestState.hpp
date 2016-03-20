#ifndef TEST_STATE_HPP
	#define TEST_STATE_HPP
	#include <states/State.hpp>
	class TestState: public State{
	public:
		TestState();
		void draw();
		void event(sf::Event);
		void tick(sf::Time);
	};
#endif