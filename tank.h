#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.hpp"
#include <iostream>
#define TANK_WIDTH 50
#define TANK_HEIGHT 50
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
		
		this->tank_texture.loadFromFile("tank.png");
		this->gun_texture.loadFromFile("gun.png");
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
		this->gun.setTextureRect(sf::IntRect(0, 0, 43, 69));
		this->gun.setOrigin(sf::Vector2f(21.5, 42.5));
		this->gun.setScale(sf::Vector2f(0.7f, 0.7f));//she zhi xing zhuang
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

	Bullet Tank::fire(sf::RenderWindow &window);
	void Tank::move_tank(sf::Event &event);
	void Tank::update(sf::Time elapsed,sf::RenderWindow &window);
	void Tank::bullet_collision(Bullet &bullet);
	float Tank::angle_of_gun(sf::RenderWindow &window);
private:
	float tank_speed = 200.f;
	bool forwarding = false;
	bool backing = false;
	bool clockwising = false;
	bool anti_clockwising = false;
	sf::Vector2f velocity;
	sf::Vector2f r0;
	sf::Vector2f r1;
	sf::Vector2f r2;
	sf::Vector2f r3;
	bool is_exist = true;
	sf::Texture gun_texture;
	sf::Texture tank_texture;
public:
	sf::Sprite gun;
};