#include <managers/VideoManager.hpp>
#include <iostream>
using namespace std;


VideoManager *VideoManager::pInstance = 0;

VideoManager *VideoManager::getInst(){

	if(pInstance==NULL)pInstance = new VideoManager();
	return pInstance;
}

VideoManager::VideoManager(){
	window.create(sf::VideoMode(640, 420), "Uno");
	if(!backgroundTexture.loadFromFile("data/background.png")){
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
	sf::Text text;
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

void VideoManager::drawBackground(){
	window.draw(background);
}

void VideoManager::clear(){
	window.clear();
}

void VideoManager::display(){
	window.display();
}