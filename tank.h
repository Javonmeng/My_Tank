#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#define TANK_WEIGHT 50
#define TANK_HEIGHT 50
#define TANK_VELOCITY sf::Vector2f(0.0,-1.0)
#define TO_RADIAN * 3.1415926f / 180
using namespace std;
class Tank : public sf::RectangleShape

{
public:
	Tank() :RectangleShape(sf::Vector2f(TANK_WEIGHT, TANK_HEIGHT))
	{
		this->setPosition(50, 50);
		this->setOrigin(TANK_WEIGHT / 2, TANK_HEIGHT / 2);
		this->velocity = TANK_VELOCITY;
		this->r0 = sf::Vector2f(-TANK_WEIGHT / 2, TANK_HEIGHT / 2);
		this->r1 = sf::Vector2f(TANK_WEIGHT / 2, TANK_HEIGHT / 2);
		this->r2 = sf::Vector2f(TANK_WEIGHT / 2, -TANK_HEIGHT / 2);
		this->r3 = sf::Vector2f(-TANK_WEIGHT / 2, -TANK_HEIGHT / 2);
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
	float getRadius();
public:
	//sf::Vector2f intersects(Obstacle &);
	//Bullet fire();
	void update(sf::Time elapsed, float width, float height);
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
};