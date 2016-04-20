#ifndef CARD_HPP
	#define CARD_HPP
	#include <sfml/Graphics.hpp>
	#include <string>
	class Card{
		int value;
		std::string color;
	public:
		static const int width = 240;
		static const int height = 360;
		static const int realWidth;
		static const int realHeight;
		static const float scale;
		Card(std::string, int);
		std::string getColor();
		int getValue();
		void setColor(std::string);
	};
#endif