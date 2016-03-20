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

void VideoManager::drawBackground(){
	window.clear();
	window.draw(background);
	window.display();
}