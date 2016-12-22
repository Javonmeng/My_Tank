#include "Game.h"

bool game_over = false;

float score = 0;
int current_score = 0;
int highest_score = 0;
int mytank_life = 1;

Bullet *bullets[BULLETS_NUMBER];

//tank[0]为自己
Tank *tanks[TANKS_NUMBER];

Buff *buff = NULL;


void is_exit(sf::Event &event, sf::RenderWindow &window)
{
	//close by mouse
	bool close = (event.type == sf::Event::Closed);
	//close by keyboard
	bool escape = (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);

	if (close || escape)
		window.close();
}


void mytank_move(sf::RenderWindow &window, sf::Event &event, sf::Sound &shotsound) {

	tanks[0]->move_tank_bymouse_check();

	while (window.pollEvent(event))
	{
		is_exit(event, window);

		//tanks[0]->move_tank(event);
		tanks[0]->move_tank_bymouse(event, window);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				for (int i = 0; i < BULLETS_NUMBER; i++) {
					if (bullets[i] == NULL) {
						bullets[i] = new Bullet(tanks[0]->fire(window));
						shotsound.play();
						break;
					}
				}



			}
		}
	}
}

void enemy_tanks_move(sf::Clock &enemy_fire_clock, sf::Clock create_enemy_clock) {
	sf::Time fire_gap = enemy_fire_clock.getElapsedTime();

	for (int i = 1; i < TANKS_NUMBER; i++) {
		if (tanks[i] != NULL)
		{
			if (create_enemy_clock.getElapsedTime().asSeconds() < 3)
			{
				;
			}
			else {


				sf::Vector2f vector = tanks[0]->getPosition() - tanks[i]->getPosition();
				float distance = (sqrt(vector.x*vector.x + vector.y*vector.y));
				if (distance < 250)
				{
					float angle = tanks[i]->enemy_fire_angle(vector);
					tanks[i]->gun.setRotation(angle);
					if (fire_gap.asSeconds() > 2)
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
			}

				tanks[i]->enemy_move(i);
			}

		}
}

void create_and_draw_shields(Shield &shield, sf::Sprite &map_sprite, sf::RenderWindow &window) {
	for (int i = 1; i <= shield.shield_position_array[0][0]; i++) {
		map_sprite.setPosition(shield.a_position_x + shield.shield_position_array[i][0], shield.a_position_y + shield.shield_position_array[i][1]);
		window.draw(map_sprite);
	}
}



void draw_tanks_and_bullets(sf::Clock &clock, sf::RenderWindow &window, sf::Sound &knocksound)
{
	sf::Time elapsed = clock.restart();
	tanks[0]->update(elapsed, window);
	window.draw(*tanks[0]);
	window.draw(tanks[0]->gun);

	for (int i = 1; i < TANKS_NUMBER; i++) {
		if (tanks[i] != NULL) {
			tanks[i]->enemy_update(elapsed, window);
			window.draw(*tanks[i]);
			window.draw(tanks[i]->gun);
		}
	}

	for (int i = 0; i< BULLETS_NUMBER; i++) {
		if (bullets[i] && bullets[i]->is_exist == true)
		{
			bullets[i]->update(elapsed, knocksound);
			window.draw(*bullets[i]);

		}
	}

}

void add_and_draw_life(sf::RenderWindow &window, sf::Text &life_test, string &life_str) {
	life_test.setString(life_str + std::to_string(mytank_life));
	window.draw(life_test);
}

void add_and_draw_score(sf::RenderWindow &window, sf::Text &score_test, string &score_str,sf::Clock &score_clock) {
	if (score_clock.getElapsedTime().asMilliseconds() >= 200)
	{
		score += 1;
		score_clock.restart();
	}
	score_test.setString(score_str + std::to_string((int)score));
	window.draw(score_test);
}

void all_check_collsion(Shield &shield, sf::Sound &boomsound, sf::Sound &knocksound) {
	//check_collsion
	for (int i = 0; i< BULLETS_NUMBER; i++) {
		if (bullets[i] != NULL) {
			//障碍物与子弹碰撞检查
			for (int j = 1; j <= shield.shield_position_array[0][0]; j++) {
				shield.check_collsion_with_bullet(*bullets[i], shield.a_position_x + shield.shield_position_array[j][0], shield.a_position_y + shield.shield_position_array[j][1], knocksound);

			}

			///坦克与子弹碰撞检验
			for (int j = 0; j < TANKS_NUMBER; j++) {
				if (tanks[j] != NULL) {
					tanks[j]->bullet_collision(*bullets[i]);
					if (tanks[j]->is_exist == false)
					{
						boomsound.play();
					}
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
	for (int i = 1; i<TANKS_NUMBER; i++)
	{
		if (tanks[i] != NULL)
		{
			for (int j = i + 1; j<TANKS_NUMBER; j++)
			{
				if (tanks[j] != NULL)
				{
					tanks[i]->tank_collison(*tanks[j]);
				}
			}
		}
	}
}



void all_check_exit() {
	//子弹存在
	for (int i = 0; i< BULLETS_NUMBER; i++) {
		if (bullets[i] != NULL && bullets[i]->is_exist == false) {
			delete bullets[i];
			bullets[i] = NULL;
		}
	}

	//坦克存在
	for (int j = 1; j < TANKS_NUMBER; j++) {
		if (tanks[j] != NULL && tanks[j]->is_exist == false) {
			score += 10;
			delete tanks[j];
			tanks[j] = NULL;
		}
	}
	//mytank exist
	if (tanks[0]->is_exist == false) {
		if (mytank_life == 1) {
			game_over = true;
		}
		else {
			tanks[0]->is_exist = true;
			mytank_life--;
		}
	}
}


void create_enemy_tanks(sf::Clock &create_enemy_clock) {

	sf::Vector2i enemy_position[] = { sf::Vector2i(375,100),sf::Vector2i(100,550),sf::Vector2i(720,50),sf::Vector2i(160,250),sf::Vector2i(70,50) };
	
	for (int i = 1; i < TANKS_NUMBER; i++) {
		if (tanks[i] == NULL && create_enemy_clock.getElapsedTime().asSeconds() > ENEMY_TANKS_CREATE_TIME_S) {
			create_enemy_clock.restart();
			tanks[i] = new Tank();
			//srand((int)time(0));
			int position = random(5);
			tanks[i]->setPosition(enemy_position[position].x, enemy_position[position].y);

		}

	}
}



void Game::delete_game() {

	game_over = false;

	current_score = (int)score;
	if (current_score > highest_score) {
		highest_score = current_score;
		ofstream highest_score_txt("./resources/highest_score.txt");
		if (highest_score_txt.is_open())
		{
			highest_score_txt << std::to_string(highest_score);
			highest_score_txt.close();
		}
	}

	score = 0;

	for (int i = 0; i < TANKS_NUMBER; i++) {
		if (tanks[i] != NULL) {
			delete tanks[i];
		}
		tanks[i] = NULL;
	}

	for (int i = 0; i < BULLETS_NUMBER; i++) {
		if (bullets[i] != NULL) {
			delete bullets[i];
		}
		bullets[i] = NULL;
	}

	if (buff != NULL) {
		delete buff;
		buff = NULL;
	}
}

void Game::start_game(sf::RenderWindow &window) {

	sf::Texture mouse_texture;
	sf::Sprite mouse_sprite;
	mouse_texture.loadFromFile("./resources/mouse.jpg");
	mouse_sprite.setTexture(mouse_texture);
	mouse_sprite.setPosition(10, 10);


	sf::Event event;
	sf::Font font;
	if (!font.loadFromFile("./resources/sansation.ttf")) {
		return;
	}
	string current_score_str = "Score: ";
	string highest_score_str = "Highest Score: ";
	ifstream highest_score_txt("./resources/highest_score.txt");
	if (highest_score_txt.is_open())
	{
		char buffer[10];
		highest_score_txt.getline(buffer, 10);
		highest_score = atoi(buffer);
	}
	string start_game_str = "Click Here to Start ! ";
	sf::Text current_score_text(current_score_str + std::to_string(current_score), font, 50);
	sf::Text highest_score_text(highest_score_str + std::to_string(highest_score), font, 50);
	sf::Text start_game_text(start_game_str, font, 60);

	current_score_text.setPosition(WIDTH / 2 - 200, HEIGHT / 2 - 100);
	highest_score_text.setPosition(WIDTH / 2 - 200, HEIGHT / 2 - 50);
	start_game_text.setPosition(WIDTH / 2 - 250, HEIGHT / 2 + 100);

	start_game_text.setFillColor(sf::Color::Black);
	highest_score_text.setFillColor(sf::Color::Black);
	current_score_text.setFillColor(sf::Color::Black);

	window.clear(sf::Color::White);

	window.draw(mouse_sprite);
	window.draw(start_game_text);
	window.draw(current_score_text);
	window.draw(highest_score_text);

	window.display();

	bool flag = true;

	while (window.isOpen() && flag) {
		while (window.pollEvent(event))
		{
			bool close = (event.type == sf::Event::Closed);
			//≈–∂œ «∑Ò∞¥ESC
			bool escape = (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);
			if (close || escape)
				window.close();


			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					flag = false;
					break;
				}
			}
		}

	}
}



void Game::play_game(sf::RenderWindow &window) {

	/////////////music load
	sf::SoundBuffer shotbuffer;
	shotbuffer.loadFromFile("./resources/shot.wav");
	sf::Sound shotsound;
	shotsound.setBuffer(shotbuffer);

	sf::SoundBuffer buffbuffer;
	buffbuffer.loadFromFile("./resources/buff.wav");
	sf::Sound buffsound;
	buffsound.setBuffer(buffbuffer);

	sf::SoundBuffer knockbuffer;
	knockbuffer.loadFromFile("./resources/knock.wav");
	sf::Sound knocksound;
	knocksound.setBuffer(knockbuffer);

	sf::SoundBuffer gameoverbuffer;
	gameoverbuffer.loadFromFile("./resources/gameover.wav");
	sf::Sound gameoversound;
	gameoversound.setBuffer(gameoverbuffer);

	sf::SoundBuffer boombuffer;
	boombuffer.loadFromFile("./resources/boom.wav");
	sf::Sound boomsound;
	boomsound.setBuffer(boombuffer);

	sf::SoundBuffer gamestartbuffer;
	gamestartbuffer.loadFromFile("./resources/gamestart.wav");
	sf::Sound gamestartsound;
	gamestartsound.setBuffer(gamestartbuffer);
	gamestartsound.play();
	//////////////////////////////////////////////////

	//	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TANK");
	sf::Clock clock;
	sf::Clock enemy_fire_clock;
	sf::Clock create_enemy_clock;
	sf::Clock buff_create_clock;
	sf::Clock score_clock;

	//score
	sf::Font font;
	if (!font.loadFromFile("./resources/sansation.ttf")) {
		return;
	}
	string score_str = "Score: ";
	string life_str = "Life: ";
	sf::Text score_text(score_str + "0", font, 50);
	sf::Text life_text(life_str + "0", font, 30);
	score_text.setFillColor(sf::Color::Black);
	life_text.setFillColor(sf::Color::Black);
	life_text.setPosition(0, 50);




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

	if (!shield_texture.loadFromFile("./resources/shield.jpg")) {
		return;
	}

	sf::Sprite map_sprite(shield_texture);

	Shield shield(SHIELD_A);




	while (window.isOpen() && (!game_over))
	{

		create_enemy_tanks(create_enemy_clock);


		mytank_move(window, event, shotsound);

		enemy_tanks_move(enemy_fire_clock,create_enemy_clock);



		if (buff_create_clock.getElapsedTime().asSeconds() > BUFF_CREATE_TIME_S) {
			buff_create_clock.restart();

			int type = (rand() % (TYPE_MAX - TYPE_MIN + 1)) + TYPE_MIN;

			if (buff == NULL) {

				buff = new Buff(type);

			}
			else {
				delete buff;
				buff = new Buff(type);

			}


		}


		if (buff != NULL) {
			int buff_type = buff->tank_buff_collision(tanks[0]);

			if (buff_type == 1) {
				buff->clear_all_bullets(bullets, BULLETS_NUMBER);

				delete buff;
				buff = NULL;
				buffsound.play();
			}

			if (buff_type == 2) {

				//                tanks[0]->reset_tank_texture();
				buff->add_mytank_life(mytank_life);

				delete buff;
				buff = NULL;
				buffsound.play();
			}

			if (buff_type == 3) {
				buff->clear_all_tanks(tanks, TANKS_NUMBER);
				delete buff;
				buff = NULL;
				buffsound.play();

			}

		}



		window.clear(sf::Color(225, 225, 225));

		if (buff != NULL) {
			window.draw(*buff);
		}


		create_and_draw_shields(shield, map_sprite, window);


		draw_tanks_and_bullets(clock, window, knocksound);


		add_and_draw_score(window, score_text, score_str,score_clock);
		add_and_draw_life(window, life_text, life_str);


		all_check_collsion(shield, boomsound, knocksound);


		all_check_exit();



		window.display();

	}
	gameoversound.play();

}






Game::Game() {


}

