#include <application/Player.hpp>
using namespace std;

Player::Player(string name){
	this->name = name;
}

void Player::addCard(Card *card){
	cards.push_back(card);
}

void Player::removeCard(Card *card){
	for(auto i = cards.begin();i!=cards.end();i++){
		if(*i==card){
			delete card;
			cards.erase(i);
			return;
		}
	}
}