#include <managers/EventManager.hpp>
#include <managers/StateManager.hpp>
#include <managers/VideoManager.hpp>

#include <iostream>

EventManager *EventManager::pInst = 0;

EventManager *EventManager::getInst(){
	if(pInst==0)pInst = new EventManager();
	return pInst;
}

void EventManager::eventHandle(){
	// std::cout<<"EventHandlle"<<std::endl;
	sf::Event event;
	while(VideoManager::getInst()->getWindow()->pollEvent(event)){
		switch(event.type){
			case sf::Event::Closed:{
				StateManager::getInst()->clear();
				return;
			}break;
			default:
				StateManager::getInst()->event(event);
			
		}
	}
}