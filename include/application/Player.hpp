#ifndef PLAYER_HPP
	#define PLAYER_HPP
	#include <application/Card.hpp>
	#include <vector>
	#include <string>
	class Player{
		std::vector<Card*> cards;
		std::string name;
		int curentCard;
	public:
		Player(std::string);
		void addCard(Card*);
		void removeCard(Card*);
		std::vector<Card*> getCards();
		void setCurentCard(int);
		int getCurentCard();
	};
#endif