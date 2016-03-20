#ifndef STATE_MANAGER_HPP
	#define STATE_MANAGER_HPP
	#include <states/State.hpp>
	#include <stack>
	#include <sfml/System.hpp>
	class StateManager{
		std::stack<State*> states;
		static StateManager *pInstance;
		StateManager(){};
	public:
		static StateManager *getInst();
		void push(State*);
		void pop();
		void draw();
		void event(sf::Event);
		void tick(sf::Time);
		bool isExit();
	};
#endif