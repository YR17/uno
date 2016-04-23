#ifndef GAME_STATE_HPP
	#define GAME_STATE_HPP
	#include <states/State.hpp>
	#include <application/Card.hpp>
	#include <application/Ring.hpp>
	#include <vector>
	#include <utility>
	class GameState: public State{
		std::vector<std::pair<std::string, int> > players;
		std::vector<Card*> cards;
		Card *topCard;
		Card *backCard;
		Card *curentCard;
		void drawDeck();
		void drawPlayers();
		void update(std::string);
		bool isCurentMover;
		std::string nickname;
		std::string mover;
		Ring colorRing;
		Card *getCardByPosition(int, int);
	public:
		GameState(std::string, std::string);
		void event(sf::Event);
		void draw();
		void tick(int);
	};
#endif