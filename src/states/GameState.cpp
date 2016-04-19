#include <states/GameState.hpp>
#include <managers/ConnectionManager.hpp>
#include <managers/VideoManager.hpp>
#include <managers/JsonManager.hpp>
#include <json/json.h>
#include <iostream>
using namespace std;
using namespace sf;

void GameState::update(std::string jsonString){
	// cout<<jsonString<<"accepted"<<endl;
	Json::Reader reader;
	Json::Value json;
	if(reader.parse(jsonString.c_str(), json)){
		if(json["mover"].asString()==nickname)isCurentMover=true;
		else isCurentMover = false;
		delete topCard;
		topCard = new Card(json["topCard"]["color"].asString(), json["topCard"]["value"].asInt());
		for(auto &card:cards)delete card;
		cards.clear();
		for(int c=0;c<json["cards"].size();c++){
			cards.push_back(new Card(json["cards"][c]["color"].asString(), json["cards"][c]["value"].asInt()));
		}

		// players.clear();
		// for(int c=0;c<json["players"].size();c++){
		// 	players[json["players"][c]["name"].asString()] = json["players"][c]["cardsNumber"].asInt();
		// }
	}
	else cout<<"error"<<endl;
}

void GameState::drawDeck(){
	for(int c=0;c<cards.size();c++){
		Card *card = cards[c];
		//Create sprite for each card in deck
		int x = 0;
		int y = -10;
		
		if(curentCard==c)
			y-=30;
		//Draw generated sprite

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
	backCard = new Card("back", 0);
	topCard = new Card("back", 0);
	curentCard = -1;
	isCurentMover = false;
	this->nickname = nickname;
	update(jsonString);
	cout<<"GameState"<<endl;
}

void GameState::addPlayer(string name, int cardsNumber){
	players[name] = cardsNumber;
}

void GameState::event(sf::Event event){
	int x = 0;
	int y = 0;
	bool clicked = false;
	if(event.type==sf::Event::MouseMoved){
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

	if(y>VideoManager::height - Card::height*Card::scale){
		int numberOfCards = cards.size();
		if(numberOfCards*Card::scale*Card::width>VideoManager::width){
			int cardWidth = VideoManager::width / numberOfCards;
			curentCard = x/cardWidth;
		}
		else{
			int padding = (VideoManager::width - numberOfCards * Card::width * Card::scale)/2;
			if(x>padding&&x<VideoManager::width-padding){
				curentCard = (x-padding)/(Card::width*Card::scale);
			}
		}
	}
	else{
		curentCard = -1;
	}
	if(clicked&&curentCard!=-1){
		Card *card = cards[curentCard];
		ConnectionManager::getInst()->send(JsonManager::sendCard(card));
	}
}

void GameState::draw(){
	drawDeck();
	if(isCurentMover)VideoManager::getInst()->drawMessage("Your turn");
}

void GameState::tick(int elapsedTime){
	if(ConnectionManager::getInst()->isReceived()){
		Json::Reader reader;
		Json::Value json;
		string response = ConnectionManager::getInst()->getLastMessage();
		cout<<"Try parse:"<<endl;
		cout<<response<<endl<<endl;
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