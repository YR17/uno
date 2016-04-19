#include <managers/StateManager.hpp>
#include <cstddef>

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
	while(states.size()){
		delete states.top();
		states.pop();
	}
}

void StateManager::draw(){
	if(states.size())states.top()->draw();
}

void StateManager::event(sf::Event event){
	if(states.size())states.top()->event(event);
}

void StateManager::tick(int elapsedTime){
	if(states.size())states.top()->tick(elapsedTime);
}

bool StateManager::isExit(){
	return !states.size();
}