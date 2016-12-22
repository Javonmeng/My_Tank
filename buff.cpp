#include "buff.h"
using namespace std;

Buff::Buff(int type) :RectangleShape(sf::Vector2f(BUFF_WIDTH, BUFF_HEIGHT)) {
	//int type;

	sf::Vector2f buff_position;
	buff_position.x = (rand() % (RAND_MAX_X - RAND_MIN_X)) + RAND_MIN_X;
	buff_position.y = (rand() % (RAND_MAX_Y - RAND_MIN_Y)) + RAND_MIN_Y;
	//type=(rand() % (TYPE_MAX - TYPE_MIN + 1)) + TYPE_MIN;
	if (type == 1)
	{
		this->buff_texture.loadFromFile("./resources/star.png");
		//this->setFillColor(sf::Color::Blue);
		this->type = type;
	}
	if (type == 2)
	{
		this->buff_texture.loadFromFile("./resources/life.png");
		//this->setFillColor(sf::Color::Red);
		this->type = type;
	}
	if (type == 3)
	{
		this->buff_texture.loadFromFile("./resources/boom.png");
		//this->setFillColor(sf::Color::Yellow);
		this->type = type;
	}
	this->setTexture(&buff_texture);
	this->setPosition(buff_position.x, buff_position.y);
	this->setOrigin(BUFF_WIDTH / 2, BUFF_HEIGHT / 2);

}

int Buff::tank_buff_collision(Tank *tank) {
	sf::Vector2f tank_position;
	sf::Vector2f buff_position;
	sf::Vector2f position_distance;
	float distance;
	tank_position = tank->getPosition();
	buff_position = this->getPosition();
	position_distance.x = tank_position.x - buff_position.x;
	position_distance.y = tank_position.y - buff_position.y;
	distance = (sqrt(position_distance.x*position_distance.x + position_distance.y*position_distance.y));
	if (distance < BUFF_TANK_DISTANCE) {
		int temp_type = this->type;
		this->type = 0;
		return temp_type;
	}
	return 0;
}

void Buff::clear_all_bullets(Bullet *bullets[], int bullets_number) {

	for (int i = 0; i < bullets_number; i++) {
		if (bullets[i] != NULL) {
			bullets[i]->is_exist = false;
		}
	}
}

void Buff::clear_all_tanks(Tank *tanks[], int tanks_number) {
	for (int i = 1; i < tanks_number; i++) {
		if (tanks[i] != NULL) {
			tanks[i]->is_exist = false;
		}
	}
}


void Buff::add_mytank_life(int &life) {
	life++;
}

void Buff::buff_collision_handle_one() {

}
