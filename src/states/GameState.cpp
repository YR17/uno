#include <states/GameState.hpp>
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

}

void GameState::tick(int elapsedTime){

}