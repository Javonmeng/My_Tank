#pragma once
#ifndef game_hpp
#define game_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <fstream>
#include "bullet.h"
#include "tank.h"
#include "shield.h"
#include "buff.h"

#define WIDTH 800
#define HEIGHT 600

#define BULLETS_NUMBER 50
#define MY_BULLETS_NUMBER 5
#define TANKS_NUMBER 4


#define ENEMY_TANKS_CREATE_TIME_S 5
#define BUFF_CREATE_TIME_S 8

#define TANK_SCORE 5
class Game {
public:
	Game();
	bool play_game(sf::RenderWindow &window, int level);
	void start_game(sf::RenderWindow &window);
	void delete_game();
	void next_game(sf::RenderWindow &window, int level);

private:







};




#endif /* game_hpp */
