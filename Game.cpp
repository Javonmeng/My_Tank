#include "Game.h"

float score = 0;

void Game::is_exit(sf::Event &event, sf::RenderWindow &window)
{
	//≈–∂œ «∑Òµ„°¡
	bool close = (event.type == sf::Event::Closed);
	//≈–∂œ «∑Ò∞¥ESC
	bool escape = (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);
	if (close || escape)
		window.close();
}
void Game::Draw_Tank(Tank &tank, sf::Time elapsed, sf::RenderWindow &window)
{
	tank.update(elapsed, window);
	window.draw(tank);
	window.draw(tank.gun);
}

Game::Game(sf::RenderWindow &window) {
	//	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TANK");
	sf::Clock clock;
	sf::Clock enemy_fire_clock;
	sf::Clock create_enemy_clock;

	//score
	sf::Font font;
	if (!font.loadFromFile("./resource/sansation.ttf")) {
		return;
	}
	string score_text = "Score: ";
	sf::Text text(score_text + "0", font, 50);
	text.setFillColor(sf::Color::Black);


	//create tanks
	tanks[0] = new Tank();
	tanks[0]->setPosition(375, 500);

	/*
	Tank enemy_tank;
	enemy_tank.setPosition(150, 150);
	enemy_tank.gun.setPosition(350, 450);
	*/

	sf::Event event;





	sf::Texture shield_texture;

	if (!shield_texture.loadFromFile("./resource/shield.jpg")) {
		return;
	}
	sf::Sprite map_sprite(shield_texture);

	Shield shield(SHIELD_A);
	/*SYSTEMTIME sys;
	GetLocalTime(&sys);
	int fire_time = sys.wSecond;*/
	//	sf::Time fire_time = clock1.restart();
	//	sf::Event event;
	while (window.isOpen())
	{
		//create enemy tanks
		for (int i = 1; i < TANKS_NUMBER; i++) {
			if (tanks[i] == NULL && create_enemy_clock.getElapsedTime().asSeconds() > 10) {
				create_enemy_clock.restart();
				tanks[i] = new Tank();
				tanks[i]->setPosition(375, 100);

			}

		}


		while (window.pollEvent(event))
		{
			is_exit(event, window);

			tanks[0]->move_tank(event);

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < BULLETS_NUMBER; i++) {
						if (bullets[i] == NULL) {
							bullets[i] = new Bullet(tanks[0]->fire(window));
							break;
						}
					}

				}
			}
		}

		sf::Time fire_gap = enemy_fire_clock.getElapsedTime();

		for (int i = 1; i < TANKS_NUMBER; i++) {
			if (tanks[i] != NULL) {

				sf::Vector2f vector = tanks[0]->getPosition() - tanks[i]->getPosition();
				float distance = (sqrt(vector.x*vector.x + vector.y*vector.y));
				if (distance<150)
				{
					float angle = tanks[i]->enemy_fire_angle(vector);
					tanks[i]->gun.setRotation(angle);
					if (fire_gap.asSeconds() > 1)
					{
						for (int j = 0; j < BULLETS_NUMBER; j++) {
							if (bullets[j] == NULL) {
								bullets[j] = new Bullet(tanks[i]->enemy_fire2tank(*tanks[0]));
								break;
							}
						}
						enemy_fire_clock.restart();
					}
				}


				tanks[i]->enemy_move(i);
			}

		}



		window.clear(sf::Color(225, 225, 225));


		//shield 生成

		for (int i = 1; i <= shield.shield_position_array[0][0]; i++) {
			map_sprite.setPosition(shield.a_position_x + shield.shield_position_array[i][0], shield.a_position_y + shield.shield_position_array[i][1]);
			window.draw(map_sprite);
		}



		/*if (enemy_tank.is_exist == true)
		{
		window.draw(enemy_tank);
		window.draw(enemy_tank.gun);
		}*/


		for (int i = 1; i < TANKS_NUMBER; i++) {
			if (tanks[i] != NULL) {
				window.draw(*tanks[i]);
				window.draw(tanks[i]->gun);


			}

		}


		sf::Time elapsed = clock.restart();

		Draw_Tank(*tanks[0], elapsed, window);

		score = score + 0.01;
		text.setString(score_text + std::to_string((int)score));
		window.draw(text);

		//坦克碰撞检查,消失
		/*
		for (int i=0; i < TANKS_NUMBER; i++) {
		if (tanks[i] != NULL) {
		for (int j = i+1; j < TANKS_NUMBER; j++) {
		tanks[i]->tank_collison(*tanks[j]);
		}

		}

		}
		*/


		for (int i = 1; i < TANKS_NUMBER; i++) {
			if (tanks[i] != NULL) {
				tanks[i]->enemy_update(elapsed, window);
			}

		}



		//check_collsion
		for (int i = 0; i< BULLETS_NUMBER; i++) {
			if (bullets[i] != NULL) {
				//				障碍物与子弹碰撞检查
				for (int j = 1; j <= shield.shield_position_array[0][0]; j++) {
					shield.check_collsion_with_bullet(*bullets[i], shield.a_position_x + shield.shield_position_array[j][0], shield.a_position_y + shield.shield_position_array[j][1]);

				}

				///坦克与子弹碰撞检验
				for (int j = 0; j < TANKS_NUMBER; j++) {
					if (tanks[j] != NULL) {
						tanks[j]->bullet_collision(*bullets[i]);
					}
				}

				//子弹与子弹碰撞检验
				for (int j = i + 1; j< BULLETS_NUMBER; j++) {
					if (bullets[j] != NULL) {
						bullets[i]->bullet_collision_check(bullets[j]);
					}

				}

			}
		}

		// 障碍物与坦克碰撞
		for (int i = 1; i <= shield.shield_position_array[0][0]; i++) {
			for (int j = 0; j < TANKS_NUMBER; j++) {
				if (tanks[j] != NULL) {
					shield.check_collsion_with_tank(*tanks[j], shield.a_position_x + shield.shield_position_array[i][0], shield.a_position_y + shield.shield_position_array[i][1]);
				}
			}
		}









		//check_exit

		//子弹存在
		for (int i = 0; i< BULLETS_NUMBER; i++) {
			if (bullets[i] != NULL && bullets[i]->is_exist == false) {
				delete bullets[i];
				bullets[i] = NULL;
			}
		}

		for (int i = 0; i< BULLETS_NUMBER; i++) {
			if (bullets[i] && bullets[i]->is_exist == true)
			{
				bullets[i]->update(elapsed);
				window.draw(*bullets[i]);

			}
		}
		//坦克存在
		for (int j = 1; j < TANKS_NUMBER; j++) {
			if (tanks[j] != NULL && tanks[j]->is_exist == false) {
				score += 20;
				delete tanks[j];
				tanks[j] = NULL;
			}
		}


		window.display();
	}

}

