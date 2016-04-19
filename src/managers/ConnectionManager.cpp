#include <managers/ConnectionManager.hpp>
#include <iostream>
using namespace std;
using namespace sf;

ConnectionManager *ConnectionManager::pInstance = 0;

ConnectionManager *ConnectionManager::getInst(){
	if(pInstance==NULL)pInstance = new ConnectionManager();
	return pInstance;
}

ConnectionManager::ConnectionManager():sendThread(&ConnectionManager::sendData, this){
	isSending = false;
	socket.setBlocking(false);
}

TcpSocket::Status ConnectionManager::connect(){
	socket.connect("188.231.133.15", 10060);
	//188.231.133.15
}

void ConnectionManager::sendData(){
	socket.setBlocking(true);
	while(socket.send(message.c_str(), sizeof(char)*message.size())!=Socket::Done){};
	isSending = false;
	socket.setBlocking(false);
}

bool ConnectionManager::isConnected(){
	return connect()==Socket::Done;
}

bool ConnectionManager::isReceived(){
	return messages.size()!=0;
}

void ConnectionManager::send(string msg){
	if(isSending)return;
	isSending = true;
	this->message = msg + "\r\n";
	sendThread.launch();
}

void ConnectionManager::receive(){
	char msg[4096];
	size_t s = 0;
	if(socket.receive(msg, 4096, s)==Socket::Done){
		string message(msg);
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
				messages.push(string(first, last));
			}
			i++;
		}
	}
}

string ConnectionManager::getLastMessage(){
	if(messages.size()>0){
		string result = messages.front();
		// cout<<"lastMessage: "<<result<<"stack size: "<<messages.size()<<endl;
		// for(auto &ch:result){
		// 	cout<<ch<<'\t'<<(int)ch<<endl;
		// }
		messages.pop();
		cout<<result<<endl;
		return result;
	}
	// return ")))))000)))(((";
}