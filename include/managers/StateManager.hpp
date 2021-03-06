#ifndef STATE_MANAGER_HPP
	#define STATE_MANAGER_HPP
	#include <states/State.hpp>
	#include <stack>
	class StateManager{
		std::stack<State*> states;
		static StateManager *pInstance;
		StateManager(){};
	public:
		static StateManager *getInst();
		void push(State*);
		void pop();
		void clear();
		void draw();
		void event(sf::Event);
		void tick(int);
		bool isExit();
	};
#endif