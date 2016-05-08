#include <states/EndState.hpp>
#include <states/ConnectionState.hpp>
#include <managers/StateManager.hpp>
#include <managers/VideoManager.hpp>
#include <json/json.h>
using namespace std;
using namespace sf;
using namespace Json;

EndState::EndState(string json){
	Reader reader;
	Value value;
	reader.parse(json.c_str(), value);
	curentPlayerName = value["curentPlayerName"].asString();
	value = value["players"];
	int minIndex = 1000;
	for(int c=0;c<value.size();c++){
		if(value[c]["score"].asInt()<value[minIndex]["score"].asInt())minIndex = c;
	}
	winner = value[minIndex]["name"].asString();
}

void EndState::draw(){
	if(winner!=curentPlayerName)
		VideoManager::getInst()->drawMessage(winner + " win!");
	else 
		VideoManager::getInst()->drawMessage("You win!");
}

void EndState::event(Event event){
	if(event.type==Event::KeyReleased){
		if(event.key.code==sf::Keyboard::Return){
			StateManager::getInst()->clear();
			StateManager::getInst()->push(new ConnectionState(curentPlayerName));
		}
	}
}