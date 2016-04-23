#ifndef RING_HPP
	#define RING_HPP
	#include <vector>
	#include <string>
	class Ring{
		std::vector<std::string> positions;
		std::vector<std::string>::iterator curentPosition;
	public:
		Ring();
		void add(std::string);
		std::string getCurent();
		std::string getNext();
		std::string getPrevious();
	};
#endif