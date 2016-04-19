#include <managers/VideoManager.hpp>
#include <iostream>
using namespace std;
using namespace sf;


VideoManager *VideoManager::pInstance = 0;

VideoManager *VideoManager::getInst(){

	if(pInstance==NULL)pInstance = new VideoManager();
	return pInstance;
}

VideoManager::VideoManager(){
	window.create(sf::VideoMode(width, height), "Uno");
	if(!backgroundTexture.loadFromFile("data/background.png")){
		cout<<"error"<<endl;
	}
	if(!cardDeckTexture.loadFromFile("data/deck.png")){
		cout<<"error"<<endl;
	}
	if(!cardBackTexture.loadFromFile("data/back.png")){
		cout<<"error"<<endl;
	}
	if(!font.loadFromFile("open-sans.light.ttf")){
		cout<<"error"<<endl;
	}
	backgroundTexture.setSmooth(true);
	background.setTexture(backgroundTexture);
	float scaleX = (float)window.getSize().x / backgroundTexture.getSize().x;
	float scaleY = (float)window.getSize().y / backgroundTexture.getSize().y;
	// cout<<scaleX<<'\t'<<scaleY<<endl;
	background.setScale(scaleX, scaleY);
}

Sprite VideoManager::getCardSprite(Card *card){
	Sprite cardSprite;
	if(card==NULL){
		cout<<"NULL card!!!"<<endl;
		return cardSprite;
	}
		
	if(card->getColor()=="back"){
		cardSprite.setTexture(cardBackTexture);
		float verticalScale = (float)Card::realHeight/cardSprite.getTextureRect().height;
		float horizontalScale = (float)Card::realWidth/cardSprite.getTextureRect().width;
		cardSprite.setScale(horizontalScale, verticalScale);
		return cardSprite;
	}

	int horizontalMargin;
	int verticalMargin = 0;

	if(card->getColor()=="yellow"){
		verticalMargin = Card::height;
	}
	else if(card->getColor()=="green"){
		verticalMargin = 2*Card::height;
	}
	else if(card->getColor()=="blue"){
		verticalMargin = 3*Card::height;
	}

	if(card->getValue()<15){
		horizontalMargin = Card::width*card->getValue();
	}

	cardSprite.setTexture(cardDeckTexture);
	cardSprite.setTextureRect(Rect<int>(horizontalMargin, verticalMargin, Card::width, Card::height));
	cardSprite.setScale(Card::scale, Card::scale);
	return cardSprite;
}

sf::RenderWindow *VideoManager::getWindow(){
	return &window;
}

void VideoManager::drawMessage(string msg){
	Text text;
	text.setFont(font);
	text.setColor(sf::Color::Blue);
	text.setString(msg);
	text.setCharacterSize(40);
	int x = window.getSize().x;
	int y = window.getSize().y;
	text.setPosition(x/2, y/2);
	text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
	window.draw(text);
}

void VideoManager::drawCard(Card* card, int x, int y){
	if(card==NULL){
		cout<<"NULL card!!!"<<endl;
		return;
	}
	Sprite cardSprite = getCardSprite(card);
	cardSprite.setPosition(x, y);		
	window.draw(cardSprite);
}



	// if(deck.size()*Card::width*Card::scale>width){
	// 	for(int c=0;c<deck.size();c++){
	// 		int horizontalPadding = width/(int)deck.size();
	// 		int verticalPadding = height - Card::height*Card::scale;
	// 		cardsToDraw[c].move(horizontalPadding*c, verticalPadding);
	// 		window.draw(cardsToDraw[c]);
	// 	}
	// }
	// else{
	// 	for(int c=0;c<deck.size();c++){
	// 		int horizontalPadding = (width - deck.size()*Card::width*Card::scale)/2;
	// 		int verticalPadding = height - Card::height*Card::scale;
	// 		// cout<<height<<'\t'<<cardHeight<<'\t'<<verticalPadding<<endl;
	// 		cardsToDraw[c].move(horizontalPadding+Card::width*c*Card::scale, verticalPadding);
	// 		// cardsToDraw[c].setOrigin(0, 0);
	// 		window.draw(cardsToDraw[c]);
	// 	}
	// }
	// cardSprite.setPosition(Vector2f(0, 0));

void VideoManager::drawBackground(){
	window.draw(background);
}

void VideoManager::clear(){
	window.clear();
}

void VideoManager::display(){
	window.display();
}