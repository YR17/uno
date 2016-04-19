
#ifndef STATE_HPP
	#define STATE_HPP
	#include <sfml/Window.hpp>
	class State{
	public:
		virtual void draw() = 0;
		virtual void event(sf::Event) = 0;
		virtual void tick(int) = 0;
	};
#endif