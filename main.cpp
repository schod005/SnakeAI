#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include "Constants.h"
#include "Grid.h"

#define GRID_SIZE 40

time_t now = 0, then = 0;
int frames = 0;
void FPS();

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
	window.setFramerateLimit(60);
	WINDOW_HANDLE = &window;
	Grid *grid = new Grid(GRID_SIZE, GRID_SIZE);

	while (window.isOpen())
	{
		FPS();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		grid->draw(window);
		window.display();
	}

	return 0;
}

void FPS()
{
	then = now;
	now = time(0);
	frames++;
	if (now != then)
	{
		std::cout << std::setw(5) << frames << " FPS\r";
		frames = 0;
	}
}