#include <application/Application.hpp>
#include <managers/StateManager.hpp>
#include <managers/VideoManager.hpp>
#include <managers/ConnectionManager.hpp>
#include <managers/EventManager.hpp>
#include <states/TestState.hpp>

void Application::start(){
	sf::Clock clock;
	VideoManager *videoManager = VideoManager::getInst();
	videoManager->clear();
	for(int c=0;c<10;c++){
		Card buf("red", c);
		videoManager->drawCard(&buf);
	}
	videoManager->display();
	sf::sleep(sf::seconds(5));
	// StateManager *stateManager = StateManager::getInst();
	// ConnectionManager *connectionManager = ConnectionManager::getInst();
	// EventManager *eventManager = EventManager::getInst();
	// stateManager->push(new TestState());
	// sf::RenderWindow *window = VideoManager::getInst()->getWindow();
	// while(!stateManager->isExit()){
	// 	eventManager->eventHandle();
	// 	connectionManager->receive();
	// 	videoManager->clear();
	// 	videoManager->drawBackground();
	// 	stateManager->tick(clock.getElapsedTime().asMilliseconds());
	// 	stateManager->draw();
	// 	videoManager->display();
	// 	sf::sleep(sf::milliseconds(100));
	// }
}