#pragma once
#include <SFML/Graphics.hpp>
#define TANK_WEIGHT 45
#define TANK_HEIGHT 68
#define TANK_VELOCITY sf::Vector2f(0.0,-1.0)
#define TO_RADIAN * 3.1415926f / 180
class Tank : public sf::RectangleShape

{
public:
	Tank() :RectangleShape(sf::Vector2f(TANK_WEIGHT, TANK_HEIGHT))
	{
		this->setPosition(400, 570);
		this->setOrigin(TANK_WEIGHT / 2, TANK_HEIGHT / 2);
		this->velocity = TANK_VELOCITY;
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
};