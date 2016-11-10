//
//  bullet.hpp
//  MySFML
//
//  Created by Xer on 10/11/2016.
//  Copyright © 2016 Xer. All rights reserved.
//

#ifndef bullet_hpp
#define bullet_hpp

#include <SFML/Graphics.hpp>
#include <math.h>
#define PI 3.1415926

#define SPEED 2

class Bullet : public sf::CircleShape {
private:
	float dx, dy;
	sf::Vector2f current_position;
	sf::Vector2f up_point;
	sf::Vector2f down_point;
	sf::Vector2f right_point;
	sf::Vector2f left_point;
	

	bool horizontal_collision = false;
	bool vertical_collsion = false;
public:
	bool is_exist = false;

public:

	Bullet(sf::Vector2f position, float angle) {
		this->setRadius(5);
		this->setFillColor(sf::Color::Green);

		this->setPosition(position);
		dx = SPEED*sin(angle);
		dy  -SPEED*cos(angle);
	}
	void horizontal_collide();
	void vertical_collide();
	void reset_collision();

	void update(sf::Image &image);



	void collsion_check(sf::Image image);

	void Draw_Bullet(sf::RenderWindow &window);
	//bullet_shape.setRadius(5);
	//void Get_Next_Position(int x,int y,int vx,int vy,int t);
	void Run_Bullet();
	//void Put_Bullet(int x,int y,int vx,int vy);

	//    void Get_Next_Position();
};

#endif /* bullet_hpp */
