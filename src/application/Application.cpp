#include <application/Application.hpp>
#include <managers/StateManager.hpp>
#include <managers/VideoManager.hpp>
#include <states/TestState.hpp>

void Application::start(){
	sf::Clock clock;
	VideoManager *videoManager = VideoManager::getInst();
	StateManager *stateManager = StateManager::getInst();
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
		videoManager->drawBackground();
		stateManager->draw();
		stateManager->tick(clock.getElapsedTime());
		sf::sleep(sf::milliseconds(100));
	}
}