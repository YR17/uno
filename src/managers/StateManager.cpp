#include <managers/StateManager.hpp>
#include <cstddef>

#include <iostream>
using namespace std;


StateManager *StateManager::pInstance = 0;

StateManager *StateManager::getInst(){
	if(pInstance==nullptr)pInstance = new StateManager();
	return pInstance;
}

void StateManager::push(State *state){
	states.push(state);
}

void StateManager::pop(){
	if(!states.size())return;
	delete states.top();
	states.pop();
}

void StateManager::clear(){
	while(!states.empty()){
		delete states.top();
		states.pop();
	}
}

void StateManager::draw(){
	if(!states.empty())states.top()->draw();
}

void StateManager::event(sf::Event event){
	if(!states.empty())states.top()->event(event);
}

void StateManager::tick(int elapsedTime){
	if(!states.empty())states.top()->tick(elapsedTime);
}

bool StateManager::isExit(){
	return states.empty();
}