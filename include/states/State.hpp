#ifndef STATE_HPP
	#define STATE_HPP
	class State{
	public:
		virtual void draw() = 0;
		virtual void event(int, int, bool) = 0;
		virtual void tick(int) = 0;
	};
#endif