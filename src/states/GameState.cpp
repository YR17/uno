#include <states/GameState.hpp>
#include <managers/VideoManager.hpp>
#include <iostream>
using namespace std;
using namespace sf;

GameState::GameState(Player *curentPlayer){
	this->curentPlayer = curentPlayer;
	cout<<"GameState"<<endl;
}

Player *GameState::getCurentPlayer(){
	return curentPlayer;
}

void GameState::addPlayer(string name, int cardsNumber){
	players[name] = cardsNumber;
}

void GameState::event(int x, int y, bool clicked){
	if(y>VideoManager::height - Card::height*Card::scale){
		int numberOfCards = curentPlayer->getCards().size();
		if(numberOfCards*Card::scale*Card::width>VideoManager::width){
			int cardWidth = VideoManager::width / numberOfCards;
			curentPlayer->setCurentCard(x/cardWidth);
		}
		else{
			int padding = (VideoManager::width - numberOfCards * Card::width * Card::scale)/2;
			if(x>padding&&x<VideoManager::width-padding){
				curentPlayer->setCurentCard((x-padding)/(Card::width*Card::scale));
			}
		}
	}
	else{
		curentPlayer->setCurentCard(-1);
		cout<<"-1"<<endl;
	}
	// cout<<x<<'\t'<<y<<'\t'<<curentPlayer->getCurentCard()<<endl;
}

void GameState::draw(){
	for(int c=0;c<curentPlayer->getCards().size();c++){
		VideoManager::getInst()->drawCard(curentPlayer->getCards()[c], c==curentPlayer->getCurentCard());
	}
}

void GameState::tick(int elapsedTime){

}