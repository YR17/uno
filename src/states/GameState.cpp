#include <states/GameState.hpp>
#include <managers/ConnectionManager.hpp>
#include <managers/VideoManager.hpp>
#include <json/json.h>
#include <iostream>
using namespace std;
using namespace sf;

GameState::GameState(Player *curentPlayer){
	this->curentPlayer = curentPlayer;
	cout<<"GameState"<<endl;
}

Player *GameState::getCurentPlayer(){
	return curentPlayer;
}

void GameState::addPlayer(string name, int cardsNumber){
	players[name] = cardsNumber;
}

void GameState::event(int x, int y, bool clicked){
	if(y>VideoManager::height - Card::height*Card::scale){
		int numberOfCards = curentPlayer->getCards().size();
		if(numberOfCards*Card::scale*Card::width>VideoManager::width){
			int cardWidth = VideoManager::width / numberOfCards;
			curentPlayer->setCurentCard(x/cardWidth);
		}
		else{
			int padding = (VideoManager::width - numberOfCards * Card::width * Card::scale)/2;
			if(x>padding&&x<VideoManager::width-padding){
				curentPlayer->setCurentCard((x-padding)/(Card::width*Card::scale));
			}
		}
	}
	else{
		curentPlayer->setCurentCard(-1);
		// cout<<"-1"<<endl;
	}
	// if(clicked){
	// 	cout<<"clicked"<<endl;
	// }
	// cout<<x<<'\t'<<y<<'\t'<<curentPlayer->getCurentCard()<<endl;
	if(clicked&&curentPlayer->getCurentCard()!=-1){
		Card *card = curentPlayer->getCards()[curentPlayer->getCurentCard()];
		cout<<"{\"request\":\"move\", \"card\":{\"color\":\"" + card->getColor() + "\", \"value\":" + std::to_string(card->getValue()) + "}}"<<endl;
		ConnectionManager::getInst()->send("{\"request\":\"move\", \"card\":{\"color\":\"" + card->getColor() + "\", \"value\":" + std::to_string(card->getValue()) + "}}");
	}
}

void GameState::draw(){
	VideoManager::getInst()->drawCards(curentPlayer->getCards(), curentPlayer->getCurentCard());
	VideoManager::getInst()->drawDeck(1, new Card("red", 3));
}

void GameState::tick(int elapsedTime){
	if(ConnectionManager::getInst()->isReceived()){
		Json::Reader reader;
		Json::Value json;
		string response = ConnectionManager::getInst()->getLastMessage();
		cout<<"Try parse:"<<endl;
		cout<<response<<endl<<endl;
		if(reader.parse(response.c_str(), json)){
			Player *player = new Player("testPlayer");
			json = json["response"];
			for(int c=0;c<json["cards"].size();c++){
				player->addCard(new Card(json["cards"][c]["color"].asString(), json["cards"][c]["value"].asInt()));
			}

			players.clear();
			for(int c=0;c<json["players"].size();c++){
				addPlayer(json["players"][c]["name"].asString(), json["players"][c]["cardsNumber"].asInt());
			}
			delete curentPlayer;
			curentPlayer = player;
		}
		else cout<<reader.getFormattedErrorMessages()<<endl;
		// for(int c=0;c<14;c++){
		// 	player->addCard(new Card("yellow", c));
		// }
		// cout<<"inGame!!!!"<<endl;
	
	}
}