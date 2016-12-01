//#include "stdafx.h"
//#include<SFML/Graphics.hpp>


#include <SFML/Graphics.hpp>
#include "Game.h"



void start_game(sf::RenderWindow &window) {
	sf::Event event;
	sf::Texture startgame_texture;
	if (!startgame_texture.loadFromFile("./resource/gamestart.jpg")) {
		return;
	}
	sf::Sprite startgame_sprite(startgame_texture);



	window.draw(startgame_sprite);
	window.display();

	bool flag = true;

	while (window.isOpen() && flag) {
		while (window.pollEvent(event))
		{
			bool close = (event.type == sf::Event::Closed);
			//≈–∂œ «∑Ò∞¥ESC
			bool escape = (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);
			if (close || escape)
				window.close();


			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					flag = false;
					break;
				}
			}
		}

	}
}


int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TANK");


	start_game(window);

	Game game(window);


	return 0;
}



