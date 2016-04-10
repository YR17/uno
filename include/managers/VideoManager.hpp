#ifndef VIDEO_MANAGER_HPP
	#define VIDEO_MANAGER_HPP
	#include <sfml/Graphics.hpp>
	#include <application/Card.hpp>
	#include <string>
	#include <vector>
	class VideoManager{
		VideoManager();
		static VideoManager *pInstance;
		sf::RenderWindow window;
		sf::Texture backgroundTexture;
		sf::Texture cardDeckTexture;
		sf::Sprite background;
		sf::Font font;
	public:
		static const int width = 640;
		static const int height = 420;
		static VideoManager *getInst();
		void drawBackground();
		void drawMessage(std::string);
		void drawCards(std::vector<Card*>, int);
		sf::RenderWindow *getWindow();
		void clear();
		void display();
	};
#endif