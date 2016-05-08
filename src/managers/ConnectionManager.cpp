#include <managers/ConnectionManager.hpp>
// #include <managers/StateManager.hpp>
// #include <states/InputState.hpp>
#include <iostream>
using namespace std;
using namespace sf;

ConnectionManager *ConnectionManager::pInstance = 0;

ConnectionManager *ConnectionManager::getInst(){
	if(pInstance==NULL)pInstance = new ConnectionManager();
	return pInstance;
}

ConnectionManager::ConnectionManager():sendThread(&ConnectionManager::sendData, this){
	socket.setBlocking(false);
}

TcpSocket::Status ConnectionManager::connect(){
	return socket.connect("188.231.133.15", 10060);
	//188.231.133.15 Trach
	//109.86.69.207 YR17
}

void ConnectionManager::disconnect(){
	socket.disconnect();
	connect();
	// StateManager::getInst()->clear();
	// StateManager::getInst()->push(new InputState());
}

void ConnectionManager::sendData(){
	socket.setBlocking(true);
	string message = messagesToSend.front();
	message+="\r\n";
	messagesToSend.pop();
	auto result = socket.send(message.c_str(), sizeof(char)*message.size());
	socket.setBlocking(false);
	if(result==Socket::Disconnected){
		disconnect();
	}
	else if(result==Socket::Partial||result==Socket::Error){
		messagesToSend.push(message);
		sendThread.launch();
	}
}

bool ConnectionManager::isConnected(){
	return connect()==Socket::Done;
}

bool ConnectionManager::isReceived(){
	return receivedMessages.size()!=0;
}

void ConnectionManager::send(string msg){
	messagesToSend.push(msg);
	sendThread.launch();
}

void ConnectionManager::receive(){
	char msg[4096];
	size_t s = 0;
	auto status = socket.receive(msg, 4096, s);
	if(status==Socket::Done){
		string message(msg);
		cout<<"Received: "<<msg<<endl;
		string::iterator first;
		string::iterator last;
		int bracketCounter = 0;
		auto i = message.begin();
		while(i!=message.end()){
			if(*i=='{'&&!bracketCounter)first = i;
			if(*i=='{')bracketCounter++;
			if(*i=='}')bracketCounter--;
			if(*i=='}'&&!bracketCounter){
				last = i+1;
				receivedMessages.push(string(first, last));
			}
			i++;
		}
	}
	else if(status==Socket::Disconnected)disconnect();
}

string ConnectionManager::getLastMessage(){
	if(receivedMessages.size()>0){
		string result = receivedMessages.front();
		// cout<<"lastMessage: "<<result<<"stack size: "<<messages.size()<<endl;
		// for(auto &ch:result){
		// 	cout<<ch<<'\t'<<(int)ch<<endl;
		// }
		receivedMessages.pop();
		cout<<result<<endl;
		return result;
	}
	else return string();
	// return ")))))000)))(((";
}