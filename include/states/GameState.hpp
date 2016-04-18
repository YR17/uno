#ifndef GAME_STATE_HPP
	#define GAME_STATE_HPP
	#include <states/State.hpp>
	#include <application/Card.hpp>
	#include <map>
	#include <vector>
	class GameState: public State{
		std::map<std::string, int> players;
		std::vector<Card*> cards;
		Card *topCard;
		Card *backCard;
		int curentCard;
		void drawDeck();
		void update(std::string);
	public:
		GameState(std::string);
		void addPlayer(std::string, int);
		void event(int, int, bool);
		void draw();
		void tick(int);
	};
#endif