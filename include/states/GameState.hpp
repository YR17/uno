#ifndef GAME_STATE_HPP
	#define GAME_STATE_HPP
	#include <states/State.hpp>
	#include <application/Player.hpp>
	#include <vector>
	class GameState: State{
		std::vector<Player*> players;
	public:
		GameState();
		void onEvent(sf::Event);
		void onDraw();
		void onTick(sf::Clock);
	};
#endif