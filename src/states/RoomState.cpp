#include <states/RoomState.hpp>
#include <states/GameState.hpp>
#include <states/ConnectionState.hpp>
#include <managers/StateManager.hpp>
#include <iostream>
using namespace std;
using namespace Json;

RoomState::RoomState(string nickname, string id){
	playersToGo = 0;
	this->id = id;
	this->nickname = nickname;
	connectionManager = ConnectionManager::getInst();
	videoManager = VideoManager::getInst();
	// ConnectionManager::getInst()->send("{\"request\":\"room\"}");
}

void RoomState::draw(){
	string msg = "Waiting " + to_string(playersToGo) + " players\n";
	for(auto i = players.begin();i!=players.end();i++){
		msg+=*i+"\n";
	}
	videoManager->drawMessage(msg);
}

void RoomState::tick(int elapsedTime){
	if(!ConnectionManager::getInst()->isConnected()){
		StateManager::getInst()->clear();
		StateManager::getInst()->push(new ConnectionState(nickname));
	}
	if(ConnectionManager::getInst()->isReceived()){
		Value json;
		string response = ConnectionManager::getInst()->getLastMessage();
		// cout<<response<<endl;
		if(reader.parse(response, json)){
			json = json["response"];

			if(json["state"].asString()=="inRoom"){
				if(playersToGo!=json["playersToGo"].asInt()){
					playersToGo = json["playersToGo"].asInt();
					players.clear();
					for(int c=0;c<json["players"].size();c++){
						players.push_back(json["players"][c].asString());
					}
				}
			}
			else if(json["state"].asString()=="inGame"){
				StateManager::getInst()->push(new GameState(json.toStyledString(), nickname));
			}
			else cout<<"Wrong State: "<<response<<endl;

		}
		else{
			// cout<<reader.getFormattedErrorMessages()<<"\t"<<response<<endl;
		}
	}
}

void RoomState::event(sf::Event){
	
}