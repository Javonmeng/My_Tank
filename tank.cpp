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
float Tank::angle_of_gun(sf::RenderWindow &window)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	sf::Vector2i Vector_mouse;
	sf::Vector2f p = this->getPosition();
	Vector_mouse.x = localPosition.x - p.x;
	Vector_mouse.y = localPosition.y - p.y;
	float cosangle;
	cosangle = -Vector_mouse.y / (sqrt(pow(Vector_mouse.x, 2) + pow(Vector_mouse.y, 2)));
	float angle, angle_hudu;
	angle_hudu = acos(cosangle);
	angle = angle_hudu * 180 / PI;
	if (Vector_mouse.x < 0) {
		angle = 360 - angle;
	}
	return angle;
}
void Tank::update(sf::Time elapsed,sf::RenderWindow &window)
{
	float width = window.getSize().x;
	float height = window.getSize().y;
	float elapsed_time = elapsed.asSeconds();
	//update position
	
	if (!(this->forwarding ^ this->backing))
	{
		//don't move if orders are contradictory
	}
	else
	{
		if (this->forwarding)
		{
			this->velocity = TANK_VELOCITY;
		}
		if (this->backing)
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
	if (this->clockwising ^ this->anti_clockwising)
	{
		float angle_velocity = 0.0;
		if (this->clockwising)
		{
			angle_velocity = -50;
		}
		if (this->anti_clockwising)
		{
			angle_velocity = 50;
		}
		this->rotate(angle_velocity * elapsed_time);
		this->r0 = sf::Vector2f(-TANK_WIDTH / 2, TANK_HEIGHT / 2);
		this->r1 = sf::Vector2f(TANK_WIDTH / 2, TANK_HEIGHT / 2);
		this->r2 = sf::Vector2f(TANK_WIDTH / 2, -TANK_HEIGHT / 2);
		this->r3 = sf::Vector2f(-TANK_WIDTH / 2, -TANK_HEIGHT / 2);
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
	sf::Vector2f p = this->getPosition();
	this->gun.setPosition(p);
	this->gun.setRotation(this->angle_of_gun(window));
}

Bullet Tank::fire(sf::RenderWindow &window)
{
	Bullet bullet(this->getPosition(), this->angle_of_gun(window));
	bullet.is_exist = true;
	return bullet;
}

void Tank::move_tank(sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			this->forward();
			break;
		case sf::Keyboard::Down:
			this->back();
			break;
		case sf::Keyboard::Left:
			this->clockwise();
			break;
		case sf::Keyboard::Right:
			this->anti_clockwise();
			break;
		case sf::Keyboard::Space:
			this->speedup();
			break;
		default:
			break;
		}
	}
	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			this->stop_forward();
			break;
		case sf::Keyboard::Down:
			this->stop_back();
		case sf::Keyboard::Left:
			this->stop_clockwise();
			break;
		case sf::Keyboard::Right:
			this->stop_anti_clockwise();
			break;
		case sf::Keyboard::Space:
			this->stop_speedup();
			break;
		default:
			break;
		}
	}
}
float distance(sf::Vector2f point, sf::Vector2f point1, sf::Vector2f point2)
{//计算返回点point到point1的距离加上到point2的距离
	return sqrt((point.x - point1.x)*(point.x - point1.x) + (point.y - point1.y)*(point.y - point1.y))
			+ sqrt((point.x - point2.x)*(point.x - point2.x) + (point.y - point2.y)*(point.y - point2.y));
}
void Tank::bullet_collision(Bullet &bullet)
{//检测与子弹的碰撞修改tank是否存活,子弹是否消失
	sf::Vector2f p_tank = this->getPosition();
	sf::Vector2f vertex0 = p_tank + this->r0;
	sf::Vector2f vertex1 = p_tank + this->r1;
	sf::Vector2f vertex2 = p_tank + this->r2;
	sf::Vector2f vertex3 = p_tank + this->r3;
	sf::Vector2f p_bullet = bullet.getPosition();
	if (distance(p_bullet, vertex0, vertex1) <= TANK_WIDTH || distance(p_bullet, vertex2, vertex3) <= TANK_WIDTH
		|| distance(p_bullet,vertex1, vertex2) <= TANK_HEIGHT || distance(p_bullet, vertex3, vertex0) <= TANK_HEIGHT)
	{
		this->is_exist = false;
		bullet.is_exist = false;
	}
		
}