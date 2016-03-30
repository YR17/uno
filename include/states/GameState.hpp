#ifndef GAME_STATE_HPP
	#define GAME_STATE_HPP
	#include <states/State.hpp>
	#include <application/Player.hpp>
	#include <map>
	class GameState: public State{
		std::map<std::string, int> players;
		Player *curentPlayer;
	public:
		GameState(Player*);
		Player *getCurentPlayer();
		void addPlayer(std::string, int);
		void event(int, int, bool);
		void draw();
		void tick(int);
	};
#endif