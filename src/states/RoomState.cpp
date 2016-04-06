#include <states/RoomState.hpp>
#include <states/GameState.hpp>
#include <managers/StateManager.hpp>
#include <application/Player.hpp>
#include <iostream>
using namespace std;
using namespace Json;

RoomState::RoomState(string id){
	playersToGo = 0;
	this->id = id;
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
				Player *player = new Player("testPlayer");
				for(int c=0;c<json["cards"].size();c++){
					player->addCard(new Card(json["cards"][c]["color"].asString(), json["cards"][c]["value"].asInt()));
				}
				// for(int c=0;c<14;c++){
				// 	player->addCard(new Card("yellow", c));
				// }
				cout<<"inGame!!!!"<<endl;
				GameState *gameState = new GameState(player);
				for(int c=0;c<json["players"].size();c++){
					gameState->addPlayer(json["players"][c]["name"].asString(), json["players"][c]["cardsNumber"].asInt());
				}
				StateManager::getInst()->push(gameState);
			}
			else cout<<"Wrong State: "<<response<<endl;

		}
		else{
			// cout<<reader.getFormattedErrorMessages()<<"\t"<<response<<endl;
		}
	}
}

void RoomState::event(int x, int y, bool clicked){
	
}