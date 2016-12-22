#pragma once
#ifndef game_hpp
#define game_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "bullet.h"
#include "tank.h"
#include "shield.h"
#include "buff.h"

#define WIDTH 800
#define HEIGHT 600

#define BULLETS_NUMBER 10
#define TANKS_NUMBER 4


#define ENEMY_TANKS_CREATE_TIME_S 5
#define BUFF_CREATE_TIME_S 5

#define TANK_SCORE 5
class Game {
public:
	Game();
	void play_game(sf::RenderWindow &window);
	void start_game(sf::RenderWindow &window);
	void delete_game();

private:







};




#endif /* game_hpp */
