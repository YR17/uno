#include <application/Card.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const float Card::scale = 0.3;
const int Card::realWidth = Card::width * Card::scale;
const int Card::realHeight = Card::height * Card::scale;
	
Card::Card(string color, int value){
	this->color = color;
	this->value = value;
}

string Card::getColor(){
	return color;
}

int Card::getValue(){
	return value;
}

void Card::setColor(string color){
	this->color = color;
}