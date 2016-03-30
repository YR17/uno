#include <application/Card.hpp>
#include <iostream>
using namespace std;
using namespace sf;

Card::Card(string color, int value){
	stringColor = color;
	this->value = value;
	if(color=="black")sfColor = Color::Black;
	else if(color=="red")sfColor = Color::Red;
	else if(color=="green")sfColor = Color::Green;
	else if(color=="blue")sfColor = Color::Blue;
	else if(color=="yellow")sfColor = Color::Yellow;
	else{
		cout<<"WrongColor"<<color<<endl;
	}
}

Card::Card(Color color, int value){
	sfColor = color;
	this->value = value;
	if(color==Color::Black)stringColor = "black";
	else if(color==Color::Red)stringColor = "red";
	else if(color==Color::Green)stringColor = "green";
	else if(color==Color::Blue)stringColor = "blue";
	else if(color==Color::Yellow)stringColor = "yellow";
	else{
		cout<<"WrongColor"<<endl;
	}
}

Color Card::getSfColor(){
	return sfColor;
}

string Card::getStringColor(){
	return stringColor;
}

int Card::getValue(){
	return value;
}