
#include <SFML/Graphics.hpp>
#include "Game.h"





int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TANK");
	Game *game = new Game();
	game->delete_game();

	while (window.isOpen()) {
		game->start_game(window);



		game->play_game(window);

		game->delete_game();




	}

	delete game;
	return 0;
}



