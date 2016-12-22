#include <SFML/Graphics.hpp>
#include"tank.h"
#include"bullet.h"
#define BUFF_HEIGHT 25
#define BUFF_WIDTH 25

#define BUFF_TANK_DISTANCE 28
#define RAND_MAX_X  700
#define RAND_MIN_X 50
#define RAND_MAX_Y  600
#define RAND_MIN_Y 50
#define TYPE_MAX 3
#define TYPE_MIN 1
//using namespace std
class Buff : public sf::RectangleShape
{
public:
	Buff(int type);
	int tank_buff_collision(Tank *tank);
	void buff_collision_handle_one();

private:

	sf::Texture buff_texture;
	bool is_exist = 0;
public:
	int type = 0;
	void clear_all_bullets(Bullet *bullets[], int bullets_number);
	void add_mytank_life(int &life);
	void clear_all_tanks(Tank *tanks[], int tanks_number);
};

