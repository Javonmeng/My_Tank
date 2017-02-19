
#include <SFML/Graphics.hpp>
#include "Game.h"





int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TANK");
	Game *game = new Game();
	game->delete_game();

	int level = 0;
	int highest_level = 0;
	bool score_flag;

	while (window.isOpen()) {

		//game->start_game(window);

		for (level = highest_level; level < MAX_LEVEL; level++) {
			game->next_game(window, level, score_flag);
			score_flag = false;
			bool pass = game->play_game(window, level);
			if (!pass) {
				score_flag = true;
				break;
			}
		}
		highest_level = level;

		if (level == MAX_LEVEL) {
			game->pass_game(window);
			game->previous_score = 0;
			highest_level = 0;
		}

		game->delete_game();




	}

	delete game;
	return 0;
}



