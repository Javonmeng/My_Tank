#include "Game.h"

bool game_over = false;

float score = 0;
int current_score = 0;
int highest_score = 0;
int mytank_life = 1;

int goal[3] = { 200,500,1200 };

int enemy_create_speed; //3
int enemy_fire_distance;  //250
int enemy_fire_gap;   //2

bool pausing = false;
bool stop_pausing = false;

Bullet *bullets[BULLETS_NUMBER];
Bullet *my_bullets[MY_BULLETS_NUMBER];


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

void is_pause(sf::Event &event, sf::RenderWindow &window, sf::Clock &pause_clock)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	{
		if (pausing == false)
		{
			pausing = true;
			pause_clock.restart();
		}
		else
		{
			pausing = false;
			stop_pausing = true;
		}
	}
}

void mytank_move(sf::RenderWindow &window, sf::Event &event, sf::Sound &shotsound,sf::Clock &pause_clock) {

	tanks[0]->move_tank_bymouse_check();

	while (window.pollEvent(event))
	{
		is_exit(event, window);
		is_pause(event, window, pause_clock);
		//tanks[0]->move_tank(event);
		tanks[0]->move_tank_bymouse(event, window);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				for (int i = 0; i < MY_BULLETS_NUMBER; i++) {
					if (my_bullets[i] == NULL) {
						my_bullets[i] = new Bullet(tanks[0]->fire(window));
						my_bullets[i]->setFillColor(sf::Color(63, 153, 183));
						shotsound.play();
						break;
					}
				}



			}
		}
	}
}

void pausing_move(sf::RenderWindow &window, sf::Event &event, sf::Clock &pause_clock)
{
	sf::Text PAUSING_TEXT;

	while (window.pollEvent(event))
	{
		is_exit(event, window);
		is_pause(event, window, pause_clock);
	}
	PAUSING_TEXT.setString("PAUSING");
	window.draw(PAUSING_TEXT);
}

void enemy_tanks_move(sf::Clock &enemy_fire_clock, sf::Clock create_enemy_clock) {
	sf::Time fire_gap = enemy_fire_clock.getElapsedTime();

	for (int i = 1; i < TANKS_NUMBER; i++) {
		if (tanks[i] != NULL)
		{
			if (create_enemy_clock.getElapsedTime().asSeconds() < enemy_create_speed)
			{
				;
			}
			else {


				sf::Vector2f vector = tanks[0]->getPosition() - tanks[i]->getPosition();
				float distance = (sqrt(vector.x*vector.x + vector.y*vector.y));
				if (distance < enemy_fire_distance)
				{
					float angle = tanks[i]->enemy_fire_angle(vector);
					tanks[i]->gun.setRotation(angle);
					if (fire_gap.asSeconds() > enemy_fire_gap)
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
	for (int i = 1; i <= shield.shield_position_array[0]; i++) {
		map_sprite.setPosition(shield.a_position_x + shield.shield_position_array[2 * i], shield.a_position_y + shield.shield_position_array[2 * i + 1]);
		window.draw(map_sprite);
	}
}



void draw_tanks_bullets_and_buff(sf::Clock &clock, sf::RenderWindow &window, sf::Sound &knocksound,sf::Clock pause_clock)
{
	window.clear(sf::Color(250, 250, 250));

	if (buff != NULL) {
		window.draw(*buff);
	}

	sf::Time elapsed = clock.restart();
	if (stop_pausing == true)
	{
		sf::Time temp_time = pause_clock.getElapsedTime();
		elapsed = elapsed - temp_time;
		stop_pausing = false;
	}
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
	for (int i = 0; i< MY_BULLETS_NUMBER; i++) {
		if (my_bullets[i] && my_bullets[i]->is_exist == true)
		{
			my_bullets[i]->update(elapsed, knocksound);
			window.draw(*my_bullets[i]);

		}
	}

}

void add_and_draw_life(sf::RenderWindow &window, sf::Text &life_test, string &life_str) {
	life_test.setString(life_str + std::to_string(mytank_life));
	window.draw(life_test);
}

void add_and_draw_score(sf::RenderWindow &window, sf::Text &score_test, string &score_str, sf::Clock &score_clock) {
	if (score_clock.getElapsedTime().asMilliseconds() >= 200)
	{
		score += 1;
		score_clock.restart();
	}
	score_test.setString(score_str + std::to_string((int)score));
	window.draw(score_test);
}

bool check_creating_tanks(Shield &shield, Tank &tank) {
	bool flag;
	for (int i = 1; i <= shield.shield_position_array[0]; i++) {

		flag = shield.check_creat_tank(tank, shield.a_position_x + shield.shield_position_array[2 * i], shield.a_position_y + shield.shield_position_array[2 * i + 1]);
		if (flag == false) {
			return false;
		}
	}
	return true;
}
void all_check_collsion(Shield &shield, sf::Sound &boomsound, sf::Sound &knocksound) {
	//check_collsion
	//enemy_bullets
	for (int i = 0; i< BULLETS_NUMBER; i++) {
		if (bullets[i] != NULL) {
			//障碍物与子弹碰撞检查
			for (int j = 1; j <= shield.shield_position_array[0]; j++) {
				shield.check_collsion_with_bullet(*bullets[i], shield.a_position_x + shield.shield_position_array[2 * j], shield.a_position_y + shield.shield_position_array[2 * j + 1], knocksound);

			}


			///坦克与子弹碰撞检验
			tanks[0]->bullet_collision(*bullets[i]);
			if (tanks[0]->is_exist == false)
			{
				boomsound.play();
			}

			//子弹与子弹碰撞检验

			//enemy_bullet and enemy_bullet
			/*
			for (int j = i + 1; j< BULLETS_NUMBER; j++) {
			if (bullets[j] != NULL) {
			bullets[i]->bullet_collision_check(bullets[j]);
			}

			}
			*/

			//enemy_bullet and my_bullet
			for (int j = 0; j< MY_BULLETS_NUMBER; j++) {
				if (my_bullets[j] != NULL) {
					bullets[i]->bullet_collision_check(my_bullets[j]);
				}

			}

		}
	}

	//my_bullets
	for (int i = 0; i< MY_BULLETS_NUMBER; i++) {
		if (my_bullets[i] != NULL) {
			//障碍物与子弹碰撞检查
			for (int j = 1; j <= shield.shield_position_array[0]; j++) {
				shield.check_collsion_with_bullet(*my_bullets[i], shield.a_position_x + shield.shield_position_array[2 * j], shield.a_position_y + shield.shield_position_array[2 * j + 1], knocksound);

			}


			//坦克与子弹碰撞检验
			for (int j = 1; j < TANKS_NUMBER; j++) {
				if (tanks[j] != NULL) {
					tanks[j]->bullet_collision(*my_bullets[i]);
					if (tanks[j]->is_exist == false)
					{
						boomsound.play();
					}
				}
			}


		}
	}


	// 障碍物与坦克碰撞
	for (int i = 1; i <= shield.shield_position_array[0]; i++) {
		for (int j = 0; j < TANKS_NUMBER; j++) {
			if (tanks[j] != NULL) {
				shield.check_collsion_with_tank(*tanks[j], shield.a_position_x + shield.shield_position_array[2 * i], shield.a_position_y + shield.shield_position_array[2 * i + 1]);
			}
		}
	}

	//tank and tank
	for (int i = 0; i<TANKS_NUMBER; i++)
	{
		if (tanks[i] != NULL)
		{
			for (int j = i + 1; j<TANKS_NUMBER; j++)
			{
				if (tanks[j] != NULL)
				{
					tanks[i]->tank_collison(*tanks[j]);
					if (tanks[j]->is_exist == false)
					{
						boomsound.play();
					}
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
	for (int i = 0; i< MY_BULLETS_NUMBER; i++) {
		if (my_bullets[i] != NULL && my_bullets[i]->is_exist == false) {
			delete my_bullets[i];
			my_bullets[i] = NULL;
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



void create_enemy_tanks(sf::Clock &create_enemy_clock, Shield &shield) {
	int position_x;
	int position_y;
	int my_tank_x = tanks[0]->getPosition().x;
	int my_tank_y = tanks[0]->getPosition().y;
	// sf::Vector2i enemy_position[] = { sf::Vector2i(375,100),sf::Vector2i(100,550),sf::Vector2i(720,50),sf::Vector2i(160,250),sf::Vector2i(70,50) };

	for (int i = 1; i < TANKS_NUMBER; i++) {
		if (tanks[i] == NULL && create_enemy_clock.getElapsedTime().asSeconds() > ENEMY_TANKS_CREATE_TIME_S) {

			tanks[i] = new Tank();
			//srand((int)time(0));
			srand(my_tank_x);

			position_x = random(WIDTH - 60) + 30;
			position_y = random(HEIGHT - 60) + 30;

			tanks[i]->setPosition(position_x, position_y);
			tanks[i]->setRotation(random(359));

			while (!check_creating_tanks(shield, *tanks[i]) || (my_tank_x - position_x)*(my_tank_x - position_x) + (my_tank_y - position_y)*(my_tank_y - position_y)<100 * 100) {

				position_x = random(800);
				position_y = random(600);
				tanks[i]->setPosition(position_x, position_y);
			}

			create_enemy_clock.restart();


		}

	}
}

void create_buff(sf::Clock &buff_create_clock) {
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
}

void check_buff(sf::Sound &buffsound) {
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
}

void Game::delete_game() {

	game_over = false;

	current_score = (int)score;
	if (current_score > highest_score) {
		highest_score = current_score;
		/*ofstream highest_score_txt("./resources/highest_score.txt");
		if (highest_score_txt.is_open())
		{
		highest_score_txt << std::to_string(highest_score);
		highest_score_txt.close();
		}*/
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
	for (int i = 0; i < MY_BULLETS_NUMBER; i++) {
		if (my_bullets[i] != NULL) {
			delete my_bullets[i];
		}
		my_bullets[i] = NULL;
	}

	if (buff != NULL) {
		delete buff;
		buff = NULL;
	}
}

void Game::next_game(sf::RenderWindow &window, int level) {

	game_over = false;

	current_score = (int)score;
	if (current_score > highest_score) {
		highest_score = current_score;
		/*ofstream highest_score_txt("./resources/highest_score.txt");
		if (highest_score_txt.is_open())
		{
		highest_score_txt << std::to_string(highest_score);
		highest_score_txt.close();
		}*/
	}

	//score = 0;

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
	for (int i = 0; i < MY_BULLETS_NUMBER; i++) {
		if (my_bullets[i] != NULL) {
			delete my_bullets[i];
		}
		my_bullets[i] = NULL;
	}


	if (buff != NULL) {
		delete buff;
		buff = NULL;
	}

	sf::Texture mouse_texture;
	sf::Sprite mouse_sprite;
	mouse_texture.loadFromFile("./resources/introduction.png");
	mouse_sprite.setTexture(mouse_texture);
	mouse_sprite.setPosition(10, 10);


	sf::Event event;
	sf::Font font;
	if (!font.loadFromFile("./resources/sansation.ttf")) {
		return;
	}
	string current_score_str = "Score: ";
	string highest_score_str = "Highest Score: ";
	/*ifstream highest_score_txt("./resources/highest_score.txt");
	if (highest_score_txt.is_open())
	{
		char buffer[10];
		highest_score_txt.getline(buffer, 10);
		highest_score = atoi(buffer);
	}*/
	string start_game_str = "Click Here to Start !";
	string level_str = "Level " + to_string(level) + "(" + "Goal : " + to_string(goal[level]) + ")";
	sf::Text current_score_text(current_score_str + std::to_string(current_score), font, 50);
	sf::Text highest_score_text(highest_score_str + std::to_string(highest_score), font, 50);
	sf::Text start_game_text(start_game_str, font, 60);
	sf::Text level_text(level_str, font, 30);

	current_score_text.setPosition(WIDTH / 2 - 200, HEIGHT / 2 - 100);
	highest_score_text.setPosition(WIDTH / 2 - 200, HEIGHT / 2 - 50);
	start_game_text.setPosition(WIDTH / 2 - 250, HEIGHT / 2 + 100);
	level_text.setPosition(WIDTH / 2 - 150, HEIGHT / 2 + 50);

	start_game_text.setFillColor(sf::Color::Black);
	highest_score_text.setFillColor(sf::Color::Black);
	current_score_text.setFillColor(sf::Color::Black);
	level_text.setFillColor(sf::Color::Red);

	window.clear(sf::Color::White);

	window.draw(mouse_sprite);
	window.draw(start_game_text);
	window.draw(current_score_text);
	window.draw(highest_score_text);
	window.draw(level_text);

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
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					if (mousePosition.x > 160 && mousePosition.x < 660 && mousePosition.y < 460 && mousePosition.y>410)
					{
						window.clear(sf::Color::White);
						sf::Text Load_text("Loading", font, 50);
						Load_text.setPosition(300, 200);
						sf::Color Color(200, 200, 200);
						Load_text.setFillColor(Color);
						window.draw(Load_text);
						window.display();
						flag = false;
						break;
					}
				}
			}
		}

	}
}

void Game::start_game(sf::RenderWindow &window) {

	sf::Texture mouse_texture;
	sf::Sprite mouse_sprite;
	mouse_texture.loadFromFile("./resources/introduction.png");
	mouse_sprite.setTexture(mouse_texture);
	mouse_sprite.setPosition(10, 10);


	sf::Event event;
	sf::Font font;
	if (!font.loadFromFile("./resources/sansation.ttf")) {
		return;
	}
	string current_score_str = "Score: ";
	string highest_score_str = "Highest Score: ";
	/*ifstream highest_score_txt("./resources/highest_score.txt");
	if (highest_score_txt.is_open())
	{
	char buffer[10];
	highest_score_txt.getline(buffer, 10);
	highest_score = atoi(buffer);
	}
	*/
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
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					if (mousePosition.x>160 && mousePosition.x<660 && mousePosition.y<460 && mousePosition.y>410)
					{
						window.clear(sf::Color::White);
						sf::Text Load_text("Loading", font, 50);
						Load_text.setPosition(300, 200);
						sf::Color Color(200, 200, 200);
						Load_text.setFillColor(Color);
						window.draw(Load_text);
						window.display();
						flag = false;
						break;
					}
				}
			}
		}

	}
}



bool Game::play_game(sf::RenderWindow &window, int level) {

	//difficulty
	if (level == 0) {
		enemy_create_speed = 3; //3
		enemy_fire_distance = 250;  //250
		enemy_fire_gap = 2;   //2

	}
	else if (level == 1) {
		enemy_create_speed = 2; //3
		enemy_fire_distance = 500;  //250
		enemy_fire_gap = 2;   //2

	}
	else if (level == 2) {
		enemy_create_speed = 2; //3
		enemy_fire_distance = 1000;  //250
		enemy_fire_gap = 1;   //2

	}


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
	sf::Clock pause_clock;
	//score
	sf::Font font;
	if (!font.loadFromFile("./resources/sansation.ttf")) {
		return false;
	}
	string score_str = "Score: ";
	string life_str = "Life: ";
	string pausing_str = "Take A Break...";
	sf::Text score_text(score_str + "0", font, 50);
	sf::Text life_text(life_str + "0", font, 30);
	sf::Text pausing_text(pausing_str, font, 70);
	score_text.setFillColor(sf::Color::Black);
	life_text.setFillColor(sf::Color::Black);
	pausing_text.setColor(sf::Color::Black);
	life_text.setPosition(0, 50);
	pausing_text.setPosition(200, 250);




	//create my tank
	tanks[0] = new Tank();
	tanks[0]->setPosition(375, 500);
	sf::Texture my_tank_texture, my_gun_texture;
	my_tank_texture.loadFromFile("./resources/my_tank.png");
	my_gun_texture.loadFromFile("./resources/my_gun.png");
	tanks[0]->setTexture(&my_tank_texture);
	tanks[0]->gun.setTexture(my_gun_texture);


	/*
	Tank enemy_tank;
	enemy_tank.setPosition(150, 150);
	enemy_tank.gun.setPosition(350, 450);
	*/

	sf::Event event;


	sf::Texture shield_texture;

	if (!shield_texture.loadFromFile("./resources/shield.jpg")) {
		return false;
	}

	sf::Sprite map_sprite(shield_texture);

	Shield shield(level);




	while (window.isOpen() && (!game_over) && ((int)score < goal[level]))
	{
		if (pausing == false)
		{
			create_enemy_tanks(create_enemy_clock, shield);


			mytank_move(window, event, shotsound, pause_clock);

			enemy_tanks_move(enemy_fire_clock, create_enemy_clock);


			create_buff(buff_create_clock);
			check_buff(buffsound);





			draw_tanks_bullets_and_buff(clock, window, knocksound,pause_clock);

			create_and_draw_shields(shield, map_sprite, window);


			add_and_draw_score(window, score_text, score_str, score_clock);
			add_and_draw_life(window, life_text, life_str);
			if (pausing == true)
			{
				window.draw(pausing_text);
			}

			all_check_collsion(shield, boomsound, knocksound);


			all_check_exit();



			window.display();
		}
		else
		{
			pausing_move(window, event, pause_clock);
		}



	}

	//check pass
	if ((int)score >= goal[level]) {
		return true;
	}
	else {
		gameoversound.play();
		return false;
	}


}






Game::Game() {


}

