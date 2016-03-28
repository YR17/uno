#ifndef VIDEO_MANAGER_HPP
	#define VIDEO_MANAGER_HPP
	#include <sfml/Window.hpp>
	#include <sfml/System.hpp>
	#include <sfml/Graphics.hpp>
	#include <iostream>
	class VideoManager{
		VideoManager();
		static VideoManager *pInstance;
		sf::RenderWindow window;
		sf::Texture backgroundTexture;
		sf::Sprite background;
		sf::Font font;
	public:
		static VideoManager *getInst();
		void drawBackground();
		void drawMessage(std::string);
		sf::RenderWindow *getWindow();
		void clear();
		void display();
	};
#endif