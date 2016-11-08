#include <SFML/Graphics.hpp>
#include "tank.h"
#define WIDTH 800
#define HEIGHT 600

void is_exit(sf::Event &event, sf::RenderWindow &window)
{
	//判断是否点×
	bool close = (event.type == sf::Event::Closed);
	//判断是否按ESC
	bool escape = (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);
	if (close || escape)
		window.close();
}
void move_tank(sf::Event &event, Tank &tank)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			tank.forward();
			break;
		case sf::Keyboard::Down:
			tank.back();
			break;
		case sf::Keyboard::Left:
			tank.clockwise();
			break;
		case sf::Keyboard::Right:
			tank.anti_clockwise();
			break;
		case sf::Keyboard::Space:
			tank.speedup();
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
			tank.stop_forward();
			break;
		case sf::Keyboard::Down:
			tank.stop_back();
		case sf::Keyboard::Left:
			tank.stop_clockwise();
			break;
		case sf::Keyboard::Right:
			tank.stop_anti_clockwise();
			break;
		case sf::Keyboard::Space:
			tank.stop_speedup();
			break;
		default:
			break;
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TANK");
	sf::Clock clock;
    Tank tank;
	sf::Texture tank_texture;
	if (!tank_texture.loadFromFile("tank.png"))
	{
		return EXIT_FAILURE;
	}
	tank.setTexture(&tank_texture);
	Tank &tank_draw = tank;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			is_exit(event, window);
			move_tank(event, tank);
		}
		sf::Time elapsed = clock.restart();
		window.clear(sf::Color(255,255,255));
		tank.update(elapsed, WIDTH, HEIGHT);
		window.draw(tank_draw);

		window.display();
	}

}