#include "tank.h"
#include "math.h"

void rotateVector(sf::Vector2f &v, float angle)
{
	float current_x = v.x;
	float current_y = v.y;
	//rotate
	v.x = current_x * cos(angle) - current_y * sin(angle);
	v.y = current_x * sin(angle) + current_y * cos(angle);
}
void Tank::forward()
{
	forwarding = true;
}
void Tank::stop_forward()
{
	forwarding = false;
}
void Tank::back()
{
	backing = true;
}
void Tank::stop_back()
{
	backing = false;
}
void Tank::clockwise()
{
	clockwising = true;
}
void Tank::stop_clockwise()
{
	clockwising = false;
}
void Tank::anti_clockwise()
{
	anti_clockwising = true;
}
void Tank::stop_anti_clockwise()
{
	anti_clockwising = false;
}
void Tank::speedup()
{
	tank_speed = 400.0f;
}
void Tank::stop_speedup()
{
	tank_speed = 200.0f;
}
float Tank::getRadius()
{
	sf::Vector2f tsize = this->getSize();
	return sqrt(tsize.x*tsize.x+tsize.y*tsize.y) / 2;
}
//sf::Vector2f Tank::intersects(Obstacle &o)
//{
//
//}
void Tank::update(sf::Time elapsed, float width, float height)
{
	float elapsed_time = elapsed.asSeconds();
	//update position
	if (!(forwarding ^ backing))
	{
		//don't move if orders are contradictory
	}
	else
	{
		if (forwarding)
		{
			velocity = TANK_VELOCITY;
		}
		if (backing)
		{
			velocity = TANK_VELOCITY * (-1.0f);
		}
		float rotation = this->getRotation() TO_RADIAN;
		rotateVector(velocity, rotation);
		this->move(velocity * this->tank_speed * elapsed_time);

		//stay in window
		sf::Vector2f p = this->getPosition();
		float r = this->getRadius();
		if (p.x < r)
		{
			p.x = r;
		}
		if (p.y < r)
		{
			p.y = r;
		}
		if (p.x > width - r)
		{
			p.x = width - r;
		}
		if (p.y > height - r)
		{
			p.y = height - r;
		}
		this->setPosition(p.x, p.y);
	}
	if (clockwising ^ anti_clockwising)
	{
		float angle_velocity = 0.0;
		if (clockwising)
		{
			angle_velocity = -50;
		}
		if (anti_clockwising)
		{
			angle_velocity = 50;
		}
		this->rotate(angle_velocity * elapsed_time);
	}
}