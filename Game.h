#pragma once
#ifndef game_hpp
#define game_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "bullet.h"
#include "tank.h"
#include "shield.h"

#define WIDTH 800
#define HEIGHT 600

#define BULLETS_NUMBER 10
#define TANKS_NUMBER 4

class Game {
public:
	Game(sf::RenderWindow &window);
private:
	Bullet *bullets[BULLETS_NUMBER] = { NULL };

	//tank[0]Îª×Ô¼º
	Tank *tanks[TANKS_NUMBER] = { NULL };

public:
	void is_exit(sf::Event &event, sf::RenderWindow &window);
	void Draw_Tank(Tank &tank, sf::Time elapsed, sf::RenderWindow &window);




};




#endif /* game_hpp */
