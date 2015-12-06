#include <SFML/Graphics.hpp>
#ifndef CONSTANTS_H
#define CONSTANTS_H

static int WINDOW_WIDTH = 600;
static int WINDOW_HEIGHT = 600;
static sf::RenderWindow *WINDOW_HANDLE;
static sf::Font font;
#define GRID_SIZE 29

enum{
	LEFT = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3
};



#endif
