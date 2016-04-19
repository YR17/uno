#ifndef JSON_MANAGER_HPP
	#define JSON_MANAGER_HPP
	#include <string>
	#include <application/Card.hpp>
	class JsonManager{
		JsonManager(){};
		// static JsonManager *pInst;
	public:
		// static JsonManager *getInst();
		static std::string sendCard(Card*);
		static std::string getConnectionString(std::string);
		static std::string getCard();
	};
#endif