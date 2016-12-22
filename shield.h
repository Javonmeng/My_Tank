#pragma once

#ifndef shield_hpp
#define shield_hpp


#define SHIELD_A 1
#define SHIELD_B 2
#define SHIELD_C 3
#define SHIELD_Cup 4
#define SHIELD_Cdown 5
#define SHIELD_Cleft 6
#define SHIELD_Cright 7


#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "tank.h"
#include <math.h>

class Shield
{
public:
	Shield(unsigned int category);

	float a_position_x = 0;
	float a_position_y = 0;

	sf::Sprite *map_array[20];
	float shield_position_array[17][2] = { { 16,16 },{ 100,100 },{ 100,150 },{ 150,150 },{ 200,150 },{ 600,100 },{ 650,100 },{ 650,150 },{ 100,350 },{ 150,350 },{ 150,400 },{ 150,450 },{ 100,450 },{ 550,450 },{ 600,400 },{ 600,450 },{ 650,450 } };

private:


	int block_counts = 0;
	sf::Vector2f* centre = new sf::Vector2f[20];
	int centre_top = 0;


public:

	int get_centre_top() { return centre_top; }
	//   void add_centre(sf::Vector2f c){centre[centre_top]=c;centre_top++;}
	sf::Vector2f get_Nth_centre(int n) { return centre[n]; }
	void set_block_counts(int block_counts) { this->block_counts = block_counts; }
	int get_block_counts() { return  block_counts; }

public:
	void create_map_A();
	void setshape_B();
	void check_collsion_with_bullet(Bullet &bullet, float position_x, float position_y, sf::Sound &knocksound);
	void check_collsion_with_tank(Tank &tank, float position_x, float position_y);


};


#endif /* shield_hpp */

