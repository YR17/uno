#ifndef EVENT_MANAGER_HPP
	#define EVENT_MANAGER_HPP
	class EventManager{
		static EventManager *pInst;
		EventManager(){};
	public:
		static EventManager *getInst();
		void eventHandle();
	};
#endif