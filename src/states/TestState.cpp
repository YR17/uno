#include <states/TestState.hpp>
#include <iostream>
using namespace std;

TestState::TestState(){
	cout<<"TestState"<<endl;
	connectionManager = ConnectionManager::getInst();
}

void TestState::draw(){

}

void TestState::event(sf::Event event){

}

void TestState::tick(sf::Time time){
}