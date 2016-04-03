#include <application/Card.hpp>
#include <iostream>
using namespace std;
using namespace sf;

const float Card::scale = 0.3;

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