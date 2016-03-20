#include <application/Application.hpp>
#include <managers/StateManager.hpp>
#include <managers/VideoManager.hpp>
#include <states/TestState.hpp>

void Application::start(){
	VideoManager *videoManager = VideoManager::getInst();
	StateManager *stateManager = StateManager::getInst();
	stateManager->push(new TestState());
	while(!stateManager->isExit()){
		stateManager->draw();
	}
}