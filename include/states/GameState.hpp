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
		bool isCurentMover;
		std::string nickname;
	public:
		GameState(std::string, std::string);
		void addPlayer(std::string, int);
		void event(sf::Event);
		void draw();
		void tick(int);
	};
#endif