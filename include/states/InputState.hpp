#ifndef INPUT_STATE
	#define INPUT_STATE
	#include <states/State.hpp>
	class InputState: public State{
		std::string nickname;
	public:
		InputState();
		void draw();
		void tick(int);
		void event(sf::Event);
	};
#endif