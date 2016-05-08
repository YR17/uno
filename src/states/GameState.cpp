#include <states/GameState.hpp>
#include <states/ConnectionState.hpp>
#include <states/EndState.hpp>
#include <managers/ConnectionManager.hpp>
#include <managers/StateManager.hpp>
#include <managers/VideoManager.hpp>
#include <managers/JsonManager.hpp>
#include <json/json.h>
#include <iostream>

#include <sstream>
#include <iomanip>

using namespace std;
using namespace sf;

Card *GameState::getCardByPosition(int x, int y){
	if(y>VideoManager::height - Card::height*Card::scale){
		int numberOfCards = cards.size();
		if(numberOfCards*Card::realWidth>VideoManager::width){
			int cardWidth = VideoManager::width / numberOfCards;
			if(x/cardWidth<=cards.size()-1&&x/cardWidth>=0)return cards[x/cardWidth];
		}
		else{
			int padding = (VideoManager::width - numberOfCards * Card::realWidth)/2;
			if(x>padding&&x<VideoManager::width-padding){
				if((x-padding)/Card::realWidth<=cards.size()-1&&(x-padding)/Card::realWidth>=0)return cards[(x-padding)/Card::realWidth];
			}
		}
	}
	else{
		return NULL;
	}
}

void GameState::update(std::string jsonString){
	// cout<<jsonString<<"accepted"<<endl;
	Json::Reader reader;
	Json::Value json;
	if(reader.parse(jsonString.c_str(), json)){
		if(json["state"].asString()=="endGame"){
			StateManager::getInst()->push(new EndState(json.toStyledString()));
		}
		else{	
			mover = json["mover"].asString();
			if(mover==nickname)isCurentMover=true;
			else isCurentMover = false;
			delete topCard;
			topCard = new Card(json["topCard"]["color"].asString(), json["topCard"]["value"].asInt());
			for(auto &card:cards)delete card;
			cards.clear();
			for(int c=0;c<json["cards"].size();c++){
				Card *card = new Card(json["cards"][c]["color"].asString(), json["cards"][c]["value"].asInt());
				if(card->getValue()>12)card->setColor(colorRing.getCurent());
				cards.push_back(card);
			}

			players.clear();
			for(int c=0;c<json["players"].size();c++){
				players.push_back(pair<string, int>(json["players"][c]["name"].asString(), json["players"][c]["cardsNumber"].asInt()));
			}
		}
	}
	else cout<<"error"<<endl;
}

void GameState::drawPlayers(){
	string playersString;
	ostringstream oss(playersString);
	for(auto &player:players){
		oss<<setw(20)<<left<<player.first<<setw(3)<<right<<player.second;
		if(player.first==mover)oss<<'<';
		oss<<endl;
	}
	VideoManager::getInst()->drawMessage(oss.str(), LEFT_TOP);
}

void GameState::drawDeck(){
	for(int c=0;c<cards.size();c++){
		Card *card = cards[c];
		int x = 0;
		int y = -10;
		
		if(curentCard==card)
			y-=30;

		int horizontalPadding;
		int verticalPadding = VideoManager::height - Card::realHeight;

		if(cards.size()*Card::realWidth>VideoManager::width){
			horizontalPadding = (VideoManager::width/(int)cards.size())*c;
		}
		else{
			horizontalPadding = (VideoManager::width - cards.size()*Card::realWidth)/2 + Card::realWidth*c;
		}
		x+=horizontalPadding;
		y+=verticalPadding;

		VideoManager::getInst()->drawCard(card, x, y);
	}

	const int padding = 5;
	const int verticalPadding = VideoManager::height/2 - Card::realHeight/2;
	const int horizontalPadding = (VideoManager::width - Card::realWidth*2 - padding)/2;

	VideoManager::getInst()->drawCard(backCard, horizontalPadding, verticalPadding);
	VideoManager::getInst()->drawCard(topCard, horizontalPadding + Card::realWidth + padding, verticalPadding);
}

GameState::GameState(string jsonString, string nickname){
	colorRing.add("yellow");
	colorRing.add("red");
	colorRing.add("blue");
	colorRing.add("green");
	backCard = new Card("back", 0);
	topCard = new Card("back", 0);
	curentCard = NULL;
	isCurentMover = false;
	this->nickname = nickname;
	update(jsonString);
	cout<<"GameState"<<endl;
}

void GameState::event(Event event){
	int x = 0;
	int y = 0;
	bool clicked = false;
	if(event.type==Event::MouseMoved){
		x = event.mouseMove.x;
		y = event.mouseMove.y;
	}
	else if(event.type==sf::Event::MouseButtonReleased){
		if(event.mouseButton.button == sf::Mouse::Left){
			x = event.mouseButton.x;
			y = event.mouseButton.y;
			clicked = true;
		}
	}
	else if(event.type==Event::MouseWheelScrolled){
		if(event.mouseWheelScroll.wheel==Mouse::VerticalWheel){
			if(event.mouseWheelScroll.delta>0){
				colorRing.getNext();
			}
			else {
				colorRing.getPrevious();
			}
			for(auto &card:cards){
				if(card->getValue()>12)card->setColor(colorRing.getCurent());
			}
		}
	}

	curentCard = getCardByPosition(x, y);

	if(clicked){
		if(curentCard!=NULL){
			// Card *card = cards[curentCard];
			// if(card->getValue()>12)card->setColor("red");
			ConnectionManager::getInst()->send(JsonManager::sendCard(curentCard));
		}
		else{
			const int verticalPadding = VideoManager::height/2 - Card::realHeight/2;
			const int horizontalPadding = (VideoManager::width - Card::realWidth*2)/2;
			if(y>verticalPadding&&y<=verticalPadding+Card::realHeight&&x>horizontalPadding&&x<=horizontalPadding+Card::realWidth){
				cout<<"getCard"<<endl;
				ConnectionManager::getInst()->send(JsonManager::getCard());
			}
		}
	}
}

void GameState::draw(){
	drawDeck();
	if(isCurentMover)VideoManager::getInst()->drawMessage("Your turn", TOP);
	drawPlayers();
}

void GameState::tick(int elapsedTime){
	if(!ConnectionManager::getInst()->isConnected()){
		StateManager::getInst()->clear();
		StateManager::getInst()->push(new ConnectionState(nickname));
	}
	if(ConnectionManager::getInst()->isReceived()){
		Json::Reader reader;
		Json::Value json;
		string response = ConnectionManager::getInst()->getLastMessage();
		// cout<<"Try parse:"<<endl;
		// cout<<response<<endl<<endl;
		if(reader.parse(response.c_str(), json)){
			json = json["response"];
			update(json.toStyledString());

		}
		// else cout<<reader.getFormattedErrorMessages()<<endl;
		// for(int c=0;c<14;c++){
		// 	player->addCard(new Card("yellow", c));
		// }
		// cout<<"inGame!!!!"<<endl;
	
	}
}