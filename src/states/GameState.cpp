#include <states/GameState.hpp>
#include <iostream>
using namespace std;
using namespace sf;

GameState::GameState(){
	cout<<"GameState"<<endl;
}

void GameState::addPlayer(string name, int cardsNumber){
	players[name] = cardsNumber;
}

void GameState::onEvent(int x, int y, bool clicked){

}

void GameState::onDraw(){

}

void GameState::onTick(int elapsedTime){

}