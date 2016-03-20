#include <managers/VideoManager.hpp>

VideoManager *VideoManager::pInstance = 0;

VideoManager *VideoManager::getInst(){

	if(pInstance==NULL)pInstance = new VideoManager();
	return pInstance;
}

VideoManager::VideoManager(){
	window.create(sf::VideoMode(640, 420), "Uno");
}

void VideoManager::drawBackground(){

}