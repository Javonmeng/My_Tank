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
float max(float a, float b, float c, float d)
{
	float tmp1 = (a > b ? a : b);
	float tmp2 = (c > d ? c : d);
	return (tmp1 > tmp2 ? tmp1 : tmp2);
}
float min(float a, float b, float c, float d)
{
	float tmp1 = (a > b ? b : a);
	float tmp2 = (c > d ? d : c);
	return (tmp1 > tmp2 ? tmp2 : tmp1);
}
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
			this->velocity = TANK_VELOCITY;
		}
		if (backing)
		{
			this->velocity = TANK_VELOCITY * (-1.0f);
		}
		float rotation = this->getRotation() TO_RADIAN;
		rotateVector(this->velocity, rotation);		
		sf::Vector2f offset_position = this->velocity * this->tank_speed * elapsed_time;
		this->move(offset_position);

		//stay in window
		sf::Vector2f p = this->getPosition();
		float min_x = min(this->r0.x, this->r1.x, this->r2.x, this->r3.x);
		float min_y = min(this->r0.y, this->r1.y, this->r2.y, this->r3.y);
		float max_x = max(this->r0.x, this->r1.x, this->r2.x, this->r3.x);
		float max_y = max(this->r0.y, this->r1.y, this->r2.y, this->r3.y);
	
		if ((p.x + min_x) < 0)
		{
			p.x = -min_x;
		}
		if ((p.y + min_y) < 0)
		{
			p.y = -min_y ;
		}
		if ((p.x + max_x) > width)
		{
			p.x = width - max_x;
		}
		if ((p.y+max_y) > height)
		{			
			p.y = height-max_y;
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
		this->r0 = sf::Vector2f(-TANK_WEIGHT / 2, TANK_HEIGHT / 2);
		this->r1 = sf::Vector2f(TANK_WEIGHT / 2, TANK_HEIGHT / 2);
		this->r2 = sf::Vector2f(TANK_WEIGHT / 2, -TANK_HEIGHT / 2);
		this->r3 = sf::Vector2f(-TANK_WEIGHT / 2, -TANK_HEIGHT / 2);
		float rotation = this->getRotation() TO_RADIAN;
		rotateVector(this->r0, rotation);//各边矢量旋转计算顶点位置
		rotateVector(this->r1, rotation);
		rotateVector(this->r2, rotation);
		rotateVector(this->r3, rotation);
		float min_x = min(this->r0.x, this->r1.x, this->r2.x, this->r3.x);
		float min_y = min(this->r0.y, this->r1.y, this->r2.y, this->r3.y);
		float max_x = max(this->r0.x, this->r1.x, this->r2.x, this->r3.x);
		float max_y = max(this->r0.y, this->r1.y, this->r2.y, this->r3.y);
		sf::Vector2f p = this->getPosition();
		//这里几项因为图片切割后内容距离边缘有微小距离，可以加一项视觉上的补偿修正
		if ((p.x + min_x) < 0)
		{
			this->rotate(-angle_velocity * elapsed_time);
		}
		if ((p.y + min_y) < 0)
		{
			this->rotate(-angle_velocity * elapsed_time);
		}
		if ((p.x + max_x) > width)
		{
			this->rotate(-angle_velocity * elapsed_time);
		}
		if ((p.y + max_y) > (height))
		{
			this->rotate(-angle_velocity * elapsed_time);
		}
		
	}
}