
#include "shield.h"



Shield::Shield(int category) {
	int number, x, y;
	srand((unsigned)time(0));
	number = MIN + rand() % (MAX - MIN + 1);

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j<12; j++) {
			shield_flag[i][j] = false;
		}
	}

	for (int i = 0; i < number; ) {
		x = rand() % 16;
		y = rand() % 12;
		if (shield_flag[x][y] == true) {
			continue;
		}

		//tank_creat_position
		if (x >= 5 && x <= 9 && y >= 9 && y <= 11) {
			continue;
		}

		shield_flag[x][y] = true;
		i++;
	}

	level_shield[0][0] = number;
	level_shield[0][1] = number;

	int count = 1;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j<12; j++) {
			if (shield_flag[i][j] == true) {
				level_shield[count][0] = i * 50;
				level_shield[count][1] = j * 50;
				count++;
			}
		}
	}

	shield_position_array = &level_shield[0][0];


	/*
	switch (category) {
	case 0:
	//            ConvexShape(6);
	create_map_A();
	break;
	case 1:
	//            ConvexShape(8);
	create_map_B();
	break;
	case 2:
	//            ConvexShape(6);
	create_map_C();
	break;


	default:
	break;
	}
	*/
}

/*
void Shield::create_map_A(){shield_position_array = &level_0_shield[0][0];}
void Shield::create_map_B(){shield_position_array = &level_1_shield[0][0];}
void Shield::create_map_C(){shield_position_array = &level_2_shield[0][0];}
*/

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

bool Shield::check_creat_tank(Tank &tank, float position_x, float position_y) {
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

				return false;
			}

		}

		k = (right_up_point.y - right_down_point.y) / (right_up_point.x - right_down_point.x);
		dx = (right_up_point.x - right_down_point.x) / 9;
		//        float x,y;


		for (int i = 0; i<10; i++) {
			x = right_down_point.x + dx*i;
			y = k*(x - right_down_point.x) + right_down_point.y;

			x = x - centre_A.x;
			y = y - centre_A.y;

			if (x<27 && x>-27 && y<27 && y>-27) {

				return false;
			}

		}

		k = (left_up_point.y - left_down_point.y) / (left_up_point.x - left_down_point.x);
		dx = (left_up_point.x - left_down_point.x) / 9;
		//        float x,y;


		for (int i = 0; i<10; i++) {
			x = left_down_point.x + dx*i;
			y = k*(x - left_down_point.x) + left_down_point.y;

			x = x - centre_A.x;
			y = y - centre_A.y;

			if (x<27 && x>-27 && y<27 && y>-27) {

				return false;
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
				return false;
			}

		}





	}
	return true;
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

		int distance_limit = 26;

		for (int i = 0; i<10; i++) {
			x = left_up_point.x + dx*i;
			y = k*(x - left_up_point.x) + left_up_point.y;

			x = x - centre_A.x;
			y = y - centre_A.y;

			if (x<distance_limit && x>-distance_limit && y<distance_limit && y>-distance_limit) {
				tank.setPosition(tank.previous_position.x, tank.previous_position.y);
				//	tank.setRotation(tank.previous_rotation);
				k = (right_up_point.y - left_up_point.y) / (right_up_point.x - left_up_point.x);
				dx = (right_up_point.x - left_up_point.x) / 9;
				for (int i = 0; i<10; i++) {
					x = left_up_point.x + dx*i;
					y = k*(x - left_up_point.x) + left_up_point.y;

					x = x - centre_A.x;
					y = y - centre_A.y;
					if (x<distance_limit && x>-distance_limit && y<distance_limit && y>-distance_limit) {
						tank.setRotation(tank.previous_rotation);
						break;
					}
				}
				k = (right_down_point.y - left_down_point.y) / (right_down_point.x - left_down_point.x);
				dx = (right_down_point.x - left_down_point.x) / 9;
				x = left_down_point.x + dx*i;
				y = k*(x - left_down_point.x) + left_down_point.y;

				x = x - centre_A.x;
				y = y - centre_A.y;
				for (int i = 0; i<10; i++) {
					x = left_up_point.x + dx*i;
					y = k*(x - left_up_point.x) + left_up_point.y;

					x = x - centre_A.x;
					y = y - centre_A.y;
					if (x<distance_limit && x>-distance_limit && y<distance_limit && y>-distance_limit) {
						tank.setRotation(tank.previous_rotation);
						break;
					}
				}
				break;
			}

			/*
			if (x<27 && x>-27 && y<27 && y>-27) {
			if (x>26 || x < -26) {
			tank.setPosition(tank.previous_position.x, tank_position.y);

			}
			else if (y>26 || y<-26) {
			tank.setPosition(tank_position.x, tank.previous_position.y);
			}

			//tank.setRotation(tank.previous_rotation);
			break;
			}
			*/
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

			if (x<distance_limit && x>-distance_limit && y<distance_limit && y>-distance_limit) {
				tank.setPosition(tank.previous_position.x, tank.previous_position.y);
				//	tank.setRotation(tank.previous_rotation);
				k = (right_up_point.y - left_up_point.y) / (right_up_point.x - left_up_point.x);
				dx = (right_up_point.x - left_up_point.x) / 9;
				for (int i = 0; i<10; i++) {
					x = left_up_point.x + dx*i;
					y = k*(x - left_up_point.x) + left_up_point.y;

					x = x - centre_A.x;
					y = y - centre_A.y;
					if (x<distance_limit && x>-distance_limit && y<distance_limit && y>-distance_limit) {
						tank.setRotation(tank.previous_rotation);
						break;
					}
				}
				k = (right_down_point.y - left_down_point.y) / (right_down_point.x - left_down_point.x);
				dx = (right_down_point.x - left_down_point.x) / 9;
				x = left_down_point.x + dx*i;
				y = k*(x - left_down_point.x) + left_down_point.y;

				x = x - centre_A.x;
				y = y - centre_A.y;
				for (int i = 0; i<10; i++) {
					x = left_up_point.x + dx*i;
					y = k*(x - left_up_point.x) + left_up_point.y;

					x = x - centre_A.x;
					y = y - centre_A.y;
					/*if (x<distance_limit && x>-distance_limit && y<distance_limit && y>-distance_limit) {
						tank.setRotation(tank.previous_rotation);
						break;
					}*/
				}
				break;
			}
		}





	}

}



