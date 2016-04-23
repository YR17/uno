#include <application/Ring.hpp>
using namespace std;

Ring::Ring(){
	curentPosition = positions.begin();
}

void Ring::add(string newPosition){
	positions.push_back(newPosition);
	curentPosition = positions.begin();
}

string Ring::getCurent(){
	if(curentPosition!=positions.end()){
		return *curentPosition;
	}
	else return string();
}

string Ring::getNext(){
	if(++curentPosition==positions.end()){
		curentPosition = positions.begin();
	}
	return getCurent();
}

string Ring::getPrevious(){
	if(curentPosition==positions.begin()){
		curentPosition = positions.end()-1;
	}
	else curentPosition--;
	return getCurent();
}