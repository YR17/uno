#ifndef STATE_HPP
	#define STATE_HPP
	#include <sfml/System.hpp>
	#include <sfml/Window.hpp>
	class State{
	public:
		virtual void draw() = 0;
		virtual void event(sf::Event) = 0;
		virtual void tick(sf::Time) = 0;
	};
#endif