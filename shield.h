#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "tank.h"
#include <math.h>

#define MIN 10
#define MAX 50

class Shield
{
public:
	Shield(int category);

	float a_position_x = 0;
	float a_position_y = 0;

	sf::Sprite *map_array[20];
	float *shield_position_array;

	/*
	float level_0_shield[17][2] = { { 16,16 },{ 100,100 },{ 100,150 },{ 150,150 },{ 200,150 },{ 600,100 },{ 650,100 },{ 650,150 },{ 100,350 },{ 150,350 },{ 150,400 },{ 150,450 },{ 100,450 },{ 550,450 },{ 600,400 },{ 600,450 },{ 650,450 } };
	float level_1_shield[10][2] = { { 9,9 },{175,125},{175,275},{175,425},{375,125},{375,275},{375,425},{575,125},{575,275},{575,425} };
	float level_2_shield[5][2] = { { 4,4 }, {350,250},{350,300},{400,250},{400,300}};
	*/
	float level_shield[MAX + 1][2];

private:


	int block_counts = 0;
	sf::Vector2f* centre = new sf::Vector2f[20];
	int centre_top = 0;
	bool shield_flag[16][12];


public:

	int get_centre_top() { return centre_top; }
	//   void add_centre(sf::Vector2f c){centre[centre_top]=c;centre_top++;}
	sf::Vector2f get_Nth_centre(int n) { return centre[n]; }
	void set_block_counts(int block_counts) { this->block_counts = block_counts; }
	int get_block_counts() { return  block_counts; }

public:
	void create_map_A();
	void create_map_B();
	void create_map_C();
	void check_collsion_with_bullet(Bullet &bullet, float position_x, float position_y, sf::Sound &knocksound);
	void check_collsion_with_tank(Tank &tank, float position_x, float position_y);
	bool check_creat_tank(Tank &tank, float position_x, float position_y);


};




