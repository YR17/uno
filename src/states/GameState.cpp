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

}

void GameState::draw(){
	for(int c=0;c<curentPlayer->getCards().size();c++){
		VideoManager::getInst()->drawCard(curentPlayer->getCards()[c]);
	}
	// for(auto &card: curentPlayer->getCards())
	// VideoManager::getInst()->drawCard(card);
}

void GameState::tick(int elapsedTime){

}