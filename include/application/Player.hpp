#ifndef PLAYER_HPP
	#define PLAYER_HPP
	#include <application/Card.hpp>
	#include <list>
	#include <string>
	class Player{
		std::list<Card*> cards;
		std::string name;
	public:
		Player(std::string);
		void addCard(Card*);
		void removeCard(Card*);
	};
#endif