#ifndef VIDEO_MANAGER_HPP
	#define VIDEO_MANAGER_HPP
	#include <sfml/Graphics.hpp>
	#include <application/Card.hpp>
	#include <string>
	#include <vector>
	class VideoManager{
		const int cardWidth = 240;
		const int cardHeight = 360;
		const float cardScale = 0.3;
		const int windowWidth = 640;
		const int windowHeight = 420;
		VideoManager();
		static VideoManager *pInstance;
		sf::RenderWindow window;
		sf::Texture backgroundTexture;
		sf::Texture cardDeckTexture;
		sf::Sprite background;
		sf::Font font;
		std::vector<sf::Sprite> cardsToDraw;
	public:
		static VideoManager *getInst();
		void drawBackground();
		void drawMessage(std::string);
		void drawCard(Card*);
		sf::RenderWindow *getWindow();
		void clear();
		void display();
	};
#endif