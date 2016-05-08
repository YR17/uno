#include <states/ConnectionState.hpp>
#include <managers/VideoManager.hpp>
#include <managers/StateManager.hpp>
#include <managers/JsonManager.hpp>
#include <states/RoomState.hpp>
#include <json/json.h>
#include <iostream>
using namespace std;
using namespace Json;

ConnectionState::ConnectionState(string nickname){
	this->nickname = nickname;
	connectionManager = ConnectionManager::getInst();
	isSent = false;
}

void ConnectionState::draw(){

}

void ConnectionState::event(sf::Event){

}

void ConnectionState::tick(int elapsedTime){
	string msg;
	if(!connectionManager->isConnected()){
		msg = "Wait connection from server";
	}
	else if(connectionManager->isReceived()){
		string response = connectionManager->getLastMessage();
		// cout<<response<<endl;
		Reader reader;
		Value result;
		if(reader.parse(response, result)){
			result = result["id"];
			cout<<"id: "<<result.asString()<<endl;
			StateManager::getInst()->push(new RoomState(nickname, result.asString()));
			
		}
		else{
			cout<<"Wrong JSON: "<<response<<endl;
		}

	}
	else if(connectionManager->isConnected()){
		if(!isSent){
			isSent = true;
			connectionManager->send(JsonManager::getConnectionString(nickname));
		}
	}
	else{
		msg = "Wait response from server";
	}

	// if(connectionManager->isConnected()&&!connectionManager->isRecieved()){
	// 	connectionManager->send("hello\nYR17");
	// 	connectionManager->recieve();
	// }
	// if(connectionManager->isRecieved()){
	// 	string id = connectionManager->getMessage();
	// 	StateManager::getInst()->push(new RoomState(id));
	// }
	for(int c=0;c<elapsedTime%6;c++)msg+='.';
	VideoManager::getInst()->drawMessage(msg);
}