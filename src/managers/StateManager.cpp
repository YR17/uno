#include <managers/StateManager.hpp>

StateManager *StateManager::pInstance = 0;

StateManager *StateManager::getInst(){
	if(pInstance==NULL)pInstance = new StateManager();
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

void StateManager::draw(){
	if(states.size())states.top()->draw();
}

void StateManager::event(sf::Event event){
	if(states.size())states.top()->event(event);
}

void StateManager::tick(sf::Time time){
	if(states.size())states.top()->tick(time);
}

bool StateManager::isExit(){
	return !states.size();
}