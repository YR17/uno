#include <application/Player.hpp>
using namespace std;

Player::Player(string name){
	this->name = name;
	curentCard = -1;
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

vector<Card*> Player::getCards(){
	return cards;
}

void Player::setCurentCard(int num){
	curentCard = num;
}

int Player::getCurentCard(){
	return curentCard;
}