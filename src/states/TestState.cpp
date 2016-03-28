#include <states/TestState.hpp>
#include <managers/VideoManager.hpp>
#include <managers/StateManager.hpp>
#include <states/RoomState.hpp>
#include <json/json.h>
#include <iostream>
using namespace std;

TestState::TestState(){
	connectionManager = ConnectionManager::getInst();
	isSent = false;
}

void TestState::draw(){

}

void TestState::event(sf::Event event){

}

void TestState::tick(sf::Time time){
	string msg;
	if(!connectionManager->isConnected()){
		msg = "Wait connection from server";
	}
	else if(connectionManager->isReceived()){
		string response = connectionManager->getLastMessage();
		// cout<<response<<endl;
		Json::Reader reader;
		Json::Value result;
		if(reader.parse(response, result)){
			result = result["id"];
			cout<<"id: "<<result.asString()<<endl;
			StateManager::getInst()->push(new RoomState(result.asString()));
			
		}
		else{
			cout<<"Wrong JSON"<<endl;
		}

	}
	else if(connectionManager->isConnected()){
		if(!isSent){
			isSent = true;
			connectionManager->send("{\"request\":\"newConnection\", \"name\":\"testPlayer\"}");
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
	for(int c=0;c<(int)time.asSeconds()%6;c++)msg+='.';
	VideoManager::getInst()->drawMessage(msg);
}