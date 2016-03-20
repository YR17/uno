#ifndef VIDEO_MANAGER_HPP
	#define VIDEO_MANAGER_HPP
	#include <sfml/Window.hpp>
	#include <sfml/System.hpp>
	class VideoManager{
		VideoManager();
		static VideoManager *pInstance;
		sf::Window window;
	public:
		static VideoManager *getInst();
		void drawBackground();
	};
#endif