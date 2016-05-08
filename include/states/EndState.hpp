#ifndef END_STATE_HPP
	#define END_STATE_HPP
	#include <states/State.hpp>
	#include <string>
	class EndState:public State{
		std::string winner;
		std::string curentPlayerName;
	public:
		EndState(std::string);
		void draw();
		void event(sf::Event);
		void tick(int){};
	};
#endif