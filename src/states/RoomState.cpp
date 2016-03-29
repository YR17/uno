#include <states/RoomState.hpp>
#include <managers/VideoManager.hpp>
#include <managers/ConnectionManager.hpp>
using namespace std;

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

void RoomState::tick(sf::Time time){
	if(ConnectionManager::getInst()->isReceived()){
		Json::Value json;
		string response = ConnectionManager::getInst()->getLastMessage();
		cout<<response<<endl;
		if(reader.parse(response, json)){
			json = json["response"];
			if(playersToGo!=json["playersToGo"].asInt()){
				playersToGo = json["playersToGo"].asInt();
				players.clear();
				for(int c=0;c<json["players"].size();c++){
					players.push_back(json["players"][c].asString());
				}
			}
		}
		else{
			cout<<reader.getFormattedErrorMessages()<<endl;
		}
	}
}

void RoomState::event(sf::Event event){
	
}