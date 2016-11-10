#include <SFML/Graphics.hpp>
#include "tank.h"
#include "bullet.hpp"
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
void Draw_Tank(Tank &tank,sf::Time elapsed,sf::RenderWindow &window)
{
	tank.update(elapsed, window);
	window.draw(tank);
	window.draw(tank.gun);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TANK");
	sf::Clock clock;
    Tank tank;
	Bullet *bullet=NULL;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			is_exit(event, window);
			tank.move_tank(event);
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					bullet = new Bullet(tank.fire(window));
				}
			}
		}
		sf::Time elapsed = clock.restart();
		window.clear(sf::Color(255,255,255));
		Draw_Tank(tank,elapsed,window);
		if(bullet&&bullet->is_exist==true)
			window.draw(*bullet);
		window.display();
	}

}