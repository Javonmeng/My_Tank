
#include "shield.h"






Shield::Shield(unsigned int category) {
	switch (category) {
	case SHIELD_A:
		//            ConvexShape(6);
		create_map_A();
		break;
	case SHIELD_B:
		//            ConvexShape(8);
		setshape_B();
		break;
		/*
		case SHIELD_Cup:
		setshape_Cup();
		break;
		case SHIELD_Cdown:
		setshape_Cdown();
		break;
		case SHIELD_Cleft:
		setshape_Cleft();
		break;
		case SHIELD_Cright:
		setshape_Cright();
		break;
		*/

	default:
		break;
	}
}

void Shield::check_collsion_with_bullet(Bullet &bullet, float position_x, float position_y, sf::Sound &knocksound) {
	sf::Vector2f centre_A, bullet_position;
	centre_A.x = position_x + 20;
	centre_A.y = position_y + 20;

	bullet_position = bullet.getPosition();

	float x = bullet_position.x - centre_A.x;
	float y = bullet_position.y - centre_A.y;

	if (x<35 && x>-35 && y<35 && y>-35) {
		if (y>x && y>-x) {
			bullet.reverse_dy_up();
			knocksound.play();
		}
		else if (y<x && y<-x) {
			bullet.reverse_dy_down();
			knocksound.play();
		}
		else if (y<x && y>-x) {
			bullet.reverse_dx_right();
			knocksound.play();
		}
		else {
			bullet.reverse_dx_left();
			knocksound.play();
		}
	}
}
void Shield::check_collsion_with_tank(Tank &tank, float position_x, float position_y) {
	sf::Vector2f centre_A, bullet_position, tank_position;
	centre_A.x = position_x + 25;
	centre_A.y = position_y + 25;

	tank_position = tank.getPosition();

	float x = tank_position.x - centre_A.x;
	float y = tank_position.y - centre_A.y;

	if (sqrt(x*x + y*y)<(50 * 1.414)) {

		sf::Vector2f left_up_point, right_down_point, right_up_point, left_down_point;
		float l = sqrt(TANK_WIDTH*TANK_WIDTH + TANK_HEIGHT*TANK_HEIGHT)*0.5;
		sf::Vector2f p = tank.getPosition();
		// ◊Û…œ
		float angle = 3.1416*0.25 - tank.getRotation() TO_RADIAN;

		left_up_point.x = p.x - l*sin(angle);
		left_up_point.y = p.y - l*cos(angle);

		//”“œ¬

		right_down_point.x = p.x + l*sin(angle);
		right_down_point.y = p.y + l*cos(angle);
		//”“…œ
		angle = 3.1415926535*0.25 + tank.getRotation() TO_RADIAN;
		right_up_point.x = p.x + l*sin(angle);
		right_up_point.y = p.y - l*cos(angle);



		//◊Ûœ¬
		left_down_point.x = p.x - l*sin(angle);
		left_down_point.y = p.y + l*cos(angle);


		//«∞√Ê»°10∏ˆµ„
		float k = (right_up_point.y - left_up_point.y) / (right_up_point.x - left_up_point.x);
		float dx = (right_up_point.x - left_up_point.x) / 9;
		//        float x,y;


		for (int i = 0; i<10; i++) {
			x = left_up_point.x + dx*i;
			y = k*(x - left_up_point.x) + left_up_point.y;

			x = x - centre_A.x;
			y = y - centre_A.y;

			if (x<27 && x>-27 && y<27 && y>-27) {
				tank.setPosition(tank.previous_position.x, tank.previous_position.y);
				tank.setRotation(tank.previous_rotation);
				break;
			}

		}



		//∫Û√Ê»°10∏ˆµ„
		k = (right_down_point.y - left_down_point.y) / (right_down_point.x - left_down_point.x);
		dx = (right_down_point.x - left_down_point.x) / 9;
		//        float x,y;


		for (int i = 0; i<10; i++) {
			x = left_down_point.x + dx*i;
			y = k*(x - left_down_point.x) + left_down_point.y;

			x = x - centre_A.x;
			y = y - centre_A.y;

			if (x<27 && x>-27 && y<27 && y>-27) {
				tank.setPosition(tank.previous_position.x, tank.previous_position.y);
				tank.setRotation(tank.previous_rotation);
				break;
			}

		}





	}

}
void Shield::create_map_A() {}

void Shield::setshape_B() {

	//*
	//**
	//*


	//  set_block_counts(get_block_counts()+4);
	/*

	add_centre(sf::Vector2f(200+25,200+25));
	add_centre(sf::Vector2f(200+25,200+75));
	add_centre(sf::Vector2f(200+25,200+125));
	add_centre(sf::Vector2f(200+75,200+75));
	*/

}

