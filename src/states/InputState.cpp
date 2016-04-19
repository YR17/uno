#include <states/InputState.hpp>
#include <states/ConnectionState.hpp>
#include <managers/StateManager.hpp>
#include <managers/VideoManager.hpp>
#include <iostream>
using namespace std;
using namespace sf;

InputState::InputState(){}

void InputState::draw(){
	VideoManager::getInst()->drawMessage("Enter your nickname:\n" + nickname);
}

void InputState::tick(int){

}

void InputState::event(Event event){
	if(event.type==Event::TextEntered){
		if(event.text.unicode==8){
			if(nickname.size())nickname.pop_back();
		}
		else if(event.text.unicode==13){
			StateManager::getInst()->push(new ConnectionState(nickname));
		}
		else if(event.text.unicode==27){
			StateManager::getInst()->clear();
		}
		else{
			nickname.push_back((char)event.text.unicode);
		}
	}
}
