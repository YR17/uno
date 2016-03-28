#include <application/Application.hpp>
#include <managers/StateManager.hpp>
#include <managers/VideoManager.hpp>
#include <managers/ConnectionManager.hpp>
#include <states/TestState.hpp>

void Application::start(){
	sf::Clock clock;
	VideoManager *videoManager = VideoManager::getInst();
	StateManager *stateManager = StateManager::getInst();
	ConnectionManager *connectionManager = ConnectionManager::getInst();
	stateManager->push(new TestState());
	sf::Window *window = VideoManager::getInst()->getWindow();
	while(!stateManager->isExit()){
		sf::Event event;
		while(window->pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:{
					stateManager->clear();
					return;
				}break;
			}
		}
		connectionManager->receive();
		videoManager->clear();
		videoManager->drawBackground();
		stateManager->draw();
		stateManager->tick(clock.getElapsedTime());
		videoManager->display();
		sf::sleep(sf::milliseconds(100));
	}
}