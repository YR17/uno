#include <managers/JsonManager.hpp>
using namespace std;

JsonManager *JsonManager::pInst = 0;

JsonManager *JsonManager::getInst(){
	if(pInst==NULL)pInst = new JsonManager();
	return pInst;
}

string JsonManager::getCard(Card *card){
	string result = "{\"request\":\"move\", \"card\":{\"color\":\"";
	result+= card->getColor();
	result+= "\", \"value\":";
	result+= to_string(card->getValue());
	result+="}}";
	return result;
}

string JsonManager::getConnectionString(string name){
	string result = "{\"request\":\"newConnection\", \"name\":\"";
	result+=name;
	result+="\"}";
	return result;
}