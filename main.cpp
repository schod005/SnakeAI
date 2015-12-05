#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include "Constants.h"
#include "Grid.h"
#include "Snake.h"


time_t now = 0, then = 0;
int frames = 0;
void FPS();
//init
int init = 0;

int main()
{
  srand(time(0));
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
  //window.setFramerateLimit(60);
  WINDOW_HANDLE = &window;
  Grid *grid = new Grid(GRID_SIZE, GRID_SIZE);
  Snake *snake1 = new Snake(grid, 0, 0);
//   Snake *snake2 = new Snake(grid, GRID_SIZE - 1, GRID_SIZE - 1);
//   Snake *snake3 = new Snake(grid, GRID_SIZE - 1, 0);
//   Snake *snake4 = new Snake(grid, 0, GRID_SIZE - 1);

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
    snake1->aStarMove();
//     snake2->randMove();
//     snake3->randMove();
//     snake4->randMove();
    grid->draw(window);
    window.display();			

    			sf::sleep(sf::Time(sf::milliseconds(150)));            //adding some delay to see snake move


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
    std::cout << std::setw(5) << frames << " FPS\r" << std::flush;
    frames = 0;
  }
}
