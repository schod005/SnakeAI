#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include "Constants.h"
#include "Grid.h"


#define GRID_SIZE 40

time_t now = 0, then = 0;
int frames = 0;
void FPS();
//init
int init = 0;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
	//window.setFramerateLimit(60);
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
			grid->randMove();      //generating a random 1 cell movement for the snake
			grid->draw(window);
			window.display();			

			sf::sleep(sf::Time(sf::milliseconds(80)));            //adding some delay to see snake move
			
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