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
		// cout<<"Connection manager received: "<<msg<<endl<<endl;
		// cout<<"begin message"<<endl;
		// for(int c=0;c<s;c++){
		// 	cout<<msg[c]<<'\t'<<(int)msg[c]<<endl;
		// }
		// cout<<"end message"<<endl;
		string test(msg);
		int lastPos = 0;
		for(int c=0;c<test.size();c++){
			if((int)test[c]==10){
				messages.push(test.substr(lastPos, c-lastPos-1));
				cout<<test.substr(lastPos, c-lastPos-1)<<endl<<endl;
				string str = test.substr(lastPos, c-lastPos-1);
				// for(auto &ch:str){
				// 	cout<<ch<<'\t'<<(int)ch<<endl;
				// }
				lastPos = c+1;
				c++;
			}
		}
		if(test.length()-lastPos>4)
		messages.push(test.substr(lastPos, test.length()));
		// exit(0);
		// messages.push(string(msg));
	}
	// 	int lastPos = 0;
	// 	for(int c=0;c<s;c++){
	// 		if(msg[c]=='\n'){
	// 			messages.push(string(msg+lastPos, c-lastPos));
	// 			lastPos = c;
	// 		}
	// 	}
	// 	messages.push(string(msg+lastPos, s-lastPos));
	// }
	// cout<<"Messages size: "<<messages.size()<<endl;
}

string ConnectionManager::getLastMessage(){
	if(messages.size()>0){
		string result = messages.front();
		// cout<<"lastMessage: "<<result<<"stack size: "<<messages.size()<<endl;
		// for(auto &ch:result){
		// 	cout<<ch<<'\t'<<(int)ch<<endl;
		// }
		messages.pop();
		return result;
	}
	// return ")))))000)))(((";
}