#ifndef GAME_STATE_HPP
	#define GAME_STATE_HPP
	#include <states/State.hpp>
	#include <application/Player.hpp>
	#include <map>
	class GameState: State{
		std::map<std::string, int> players;
	public:
		GameState();
		void addPlayer(std::string, int);
		void onEvent(int, int, bool);
		void onDraw();
		void onTick(int);
	};
#endif