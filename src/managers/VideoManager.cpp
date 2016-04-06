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

void VideoManager::drawCard(Card *card, bool isActive){

	Sprite cardSprite;
	// cardSprite.setPosition(Vector2f(0, 0));
	int horizontalPadding;
	int verticalPadding = 0;

	if(card->getColor()=="yellow"){
		verticalPadding = Card::height;
	}
	else if(card->getColor()=="green"){
		verticalPadding = 2*Card::height;
	}
	else if(card->getColor()=="blue"){
		verticalPadding = 3*Card::height;
	}

	if(card->getValue()<15){
		horizontalPadding = Card::width*card->getValue();
	}

	if(isActive)
		cardSprite.setPosition(0, -20);
	else
		cardSprite.setPosition(0, -10);
	cardSprite.setTexture(cardDeckTexture);
	cardSprite.setTextureRect(Rect<int>(horizontalPadding, verticalPadding, Card::width, Card::height));
	cardSprite.setScale(Card::scale, Card::scale);
	cardsToDraw.push_back(cardSprite);

}

void VideoManager::drawBackground(){
	window.draw(background);
}

void VideoManager::clear(){
	window.clear();
}

void VideoManager::display(){
	if(cardsToDraw.size()*Card::width*Card::scale>width){
		for(int c=0;c<cardsToDraw.size();c++){
			int horizontalPadding = width/(int)cardsToDraw.size();
			int verticalPadding = height - Card::height*Card::scale;
			cardsToDraw[c].move(horizontalPadding*c, verticalPadding);
			window.draw(cardsToDraw[c]);
		}
	}
	else{
		for(int c=0;c<cardsToDraw.size();c++){
			int horizontalPadding = (width - cardsToDraw.size()*Card::width*Card::scale)/2;
			int verticalPadding = height - Card::height*Card::scale;
			// cout<<height<<'\t'<<cardHeight<<'\t'<<verticalPadding<<endl;
			cardsToDraw[c].move(horizontalPadding+Card::width*c*Card::scale, verticalPadding);
			// cardsToDraw[c].setOrigin(0, 0);
			window.draw(cardsToDraw[c]);
		}
	}
	cardsToDraw.clear();
	window.display();
}