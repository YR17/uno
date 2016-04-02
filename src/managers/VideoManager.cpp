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
	window.create(sf::VideoMode(windowWidth, windowHeight), "Uno");
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

void VideoManager::drawCard(Card *card){

	Sprite cardSprite;
	// cardSprite.setPosition(Vector2f(0, 0));
	int horizontalPadding;
	int verticalPadding;
	
	if(card->getStringColor()=="red"){
		verticalPadding = 0;
	}
	else if(card->getStringColor()=="yellow"){
		verticalPadding = cardHeight;
	}
	else if(card->getStringColor()=="green"){
		verticalPadding = 2*cardHeight;
	}
	else if(card->getStringColor()=="blue"){
		verticalPadding = 3*cardHeight;
	}

	if(card->getValue()<10){
		horizontalPadding = cardWidth*card->getValue();
	}

	horizontalPadding*=cardScale;
	verticalPadding*=cardScale;

	cardSprite.setTexture(cardDeckTexture);
	cardSprite.setTextureRect(Rect<int>(horizontalPadding, verticalPadding, cardWidth, cardHeight));
	cardSprite.setScale(cardScale, cardScale);
	cardsToDraw.push_back(cardSprite);

}

void VideoManager::drawBackground(){
	window.draw(background);
}

void VideoManager::clear(){
	window.clear();
}

void VideoManager::display(){
	// if(cardsToDraw.size()*cardWidth*cardScale>windowWidth){
		// int paddingBetween = (windowWidth - cardWidth*cardsToDraw.size())/cardsToDraw.size();
		for(int c=0;c<cardsToDraw.size();c++){
			int horizontalPadding = windowWidth/(int)cardsToDraw.size();
			int verticalPadding = windowHeight - cardHeight*cardScale;
			cardsToDraw[c].setPosition(horizontalPadding*c, verticalPadding);
			window.draw(cardsToDraw[c]);
		}
	// }
	// else{
		// for(int c=0;c<cardsToDraw.size();c++){
		// 	int horizontalPadding = (windowWidth - cardsToDraw.size()*cardWidth*cardScale)/2;
		// 	int verticalPadding = windowHeight - cardHeight*cardScale;
		// 	// cout<<windowHeight<<'\t'<<cardHeight<<'\t'<<verticalPadding<<endl;
		// 	cardsToDraw[c].setPosition(horizontalPadding+cardWidth*c*cardScale, verticalPadding);
		// 	// cardsToDraw[c].setOrigin(0, 0);
		// 	window.draw(cardsToDraw[c]);
		// }
	// }
	window.display();
}