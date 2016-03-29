#ifndef CARD_HPP
	#define CARD_HPP
	#include <sfml/Graphics.hpp>
	#include <iostream>
	class Card{
		int value;
		sf::Color sfColor;
		std::string stringColor;
	public:
		Card(std::string, int);
		Card(sf::Color, int);
		sf::Color getSfColor();
		std::string getStringColor();
		int getValue();
	};
#endif