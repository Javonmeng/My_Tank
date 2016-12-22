#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.h"
#include <iostream>
#include<time.h>
#define random(x) (rand()%x)
#define TANK_WIDTH 25
#define TANK_HEIGHT 25
#define TANK_VELOCITY sf::Vector2f(0.0,-1.0)
#define TO_RADIAN * 3.1415926f / 180
#define ERROR 0;
#define OK 1;

using namespace std;
class Tank : public sf::RectangleShape
{
public:
	Tank() :RectangleShape(sf::Vector2f(TANK_WIDTH, TANK_HEIGHT))
	{

		this->tank_texture.loadFromFile("./resources/tank.png");
		this->gun_texture.loadFromFile("./resources/gun.png");
		this->setPosition(50, 50);
		this->setOrigin(TANK_WIDTH / 2, TANK_HEIGHT / 2);
		this->velocity = TANK_VELOCITY;
		this->r0 = sf::Vector2f(-TANK_WIDTH / 2, TANK_HEIGHT / 2);
		this->r1 = sf::Vector2f(TANK_WIDTH / 2, TANK_HEIGHT / 2);
		this->r2 = sf::Vector2f(TANK_WIDTH / 2, -TANK_HEIGHT / 2);
		this->r3 = sf::Vector2f(-TANK_WIDTH / 2, -TANK_HEIGHT / 2);
		this->is_exist = true;
		this->setTexture(&tank_texture);
		this->gun.setTexture(gun_texture);
		this->gun.setTextureRect(sf::IntRect(0, 0, 22, 25));
		this->gun.setOrigin(sf::Vector2f(21.5, 22.5));
		this->gun.setScale(sf::Vector2f(0.7f, 0.7f));
		this->gun.setPosition(this->getPosition());
	}
public:
	void forward();
	void stop_forward();
	void back();
	void stop_back();
	void clockwise();
	void stop_clockwise();
	void anti_clockwise();
	void stop_anti_clockwise();
	void speedup();
	void stop_speedup();
public:
	//	float getRadius();
public:
	sf::Vector2f previous_position;
	float previous_rotation;
	Bullet fire(sf::RenderWindow &window);
	void move_tank(sf::Event &event);
	void move_tank_bymouse(sf::Event &event, sf::RenderWindow &window);
	void move_tank_bymouse_check();
	float enemy_fire_angle(sf::Vector2f vector);
	Bullet enemy_fire2tank(Tank tank);
	void enemy_move(int seed);
	void enemy_update(sf::Time elapsed, sf::RenderWindow &window);
	void update(sf::Time elapsed, sf::RenderWindow &window);
	void bullet_collision(Bullet &bullet);
	void tank_collison(Tank &other_tank);
	float angle_of_gun(sf::RenderWindow &window);
private:
	float tank_speed = 200.f;
	float rotate_speed = 300;
	bool forwarding = false;
	bool backing = false;
	bool clockwising = false;
	bool anti_clockwising = false;
	sf::Vector2f velocity;
	sf::Vector2f r0;
	sf::Vector2f r1;
	sf::Vector2f r2;
	sf::Vector2f r3;
	sf::Texture gun_texture;
	sf::Texture tank_texture;
	sf::Vector2f mousePosition = this->getPosition();
	bool head_move = true;
public:
	bool is_exist = true;
	sf::Sprite gun;
};
