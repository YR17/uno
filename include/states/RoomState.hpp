#ifndef ROOM_STATE_HPP
	#define ROOM_STATE_HPP
	#include <states/State.hpp>
	#include <managers/ConnectionManager.hpp>
	#include <managers/VideoManager.hpp>
	#include <json/json.h>
	#include <iostream>
	#include <vector>
	class RoomState:public State{
		std::string id;
		int playersToGo;
		std::vector<std::string> players;
		ConnectionManager *connectionManager;
		VideoManager *videoManager;
		Json::Reader reader;
	public:
		RoomState(std::string);
		void tick(int);
		void draw();
		void event(int, int, bool);
	};
#endif