#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <iostream>
#ifndef GRID_HPP
#define GRID_HPP

class Grid
{
public:
	Grid();
	Grid(int, int);
	~Grid();
	void draw(sf::RenderWindow&);
	void generateApple();
  std::vector<sf::Vector2i> neighbors(sf::Vector2i Loc);
  int aStarSearch(sf::Vector2i currentLoc, sf::Vector2i destLoc);

	inline int getRows(){ return rows; }
	inline int getCols(){ return cols; }
	inline sf::RectangleShape **getDrawGrid(){ return drawGrid; }
	inline sf::Vector2i getAppleLoc(){ return appleLoc; }

private:
	int rows;
	int cols;
	sf::RectangleShape **drawGrid;
	sf::Vector2i appleLoc;

};

#endif

Grid::Grid()
{
	//empty
}

Grid::Grid(int cols_, int rows_)
{
	rows = rows_;
	cols = cols_;

	//generating two rand values for loc of apple
	int rand_row = rand() % rows;
	int rand_col = rand() % cols;

	//assigning appleLoc first random location
	appleLoc.x = rand_col;
	appleLoc.y = rand_row;

	drawGrid = new sf::RectangleShape*[rows];
	for (int i = 0; i < rows; i++)
	{
		drawGrid[i] = new sf::RectangleShape[cols];
	}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			drawGrid[i][j].setSize(sf::Vector2f((float)WINDOW_WIDTH / rows - 2,
											    (float)WINDOW_HEIGHT / cols - 2));
			drawGrid[i][j].setPosition(sf::Vector2f((float)i * WINDOW_WIDTH / rows + 1,
													(float)j * WINDOW_HEIGHT / cols + 1));
			drawGrid[i][j].setFillColor(sf::Color(140, 140, 140, 255));
			
		}

	//adding a random apple at start of creation
	drawGrid[rand_col][rand_row].setFillColor(sf::Color::Red);
}

Grid::~Grid()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] drawGrid[i];
	}
	delete[] drawGrid;
}

//git test
void Grid::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			window.draw(drawGrid[i][j]);
		}
}

void Grid::generateApple()
{
	int rand_row = rand() % rows;
	int rand_col = rand() % cols;

	appleLoc.x = rand_col;
	appleLoc.y = rand_row;

	drawGrid[appleLoc.x][appleLoc.y].setFillColor(sf::Color::Red);
}

std::vector<sf::Vector2i> Grid::neighbors(sf::Vector2i Loc)
{
  std::vector<sf::Vector2i> list;
  if(Loc.x - 1 > 0 && drawGrid[Loc.x - 1][Loc.y].getFillColor() == sf::Color(140,140,140,255))
    list.emplace_back(sf::Vector2i(Loc.x - 1, Loc.y));
  if(Loc.x + 1 > 0 && drawGrid[Loc.x + 1][Loc.y].getFillColor() == sf::Color(140,140,140,255))
    list.emplace_back(sf::Vector2i(Loc.x + 1, Loc.y));
  if(Loc.y - 1 > 0 && drawGrid[Loc.x][Loc.y - 1].getFillColor() == sf::Color(140,140,140,255))
    list.emplace_back(sf::Vector2i(Loc.x, Loc.y - 1));
  if(Loc.y + 1 > 0 && drawGrid[Loc.x][Loc.y + 1].getFillColor() == sf::Color(140,140,140,255))
    list.emplace_back(sf::Vector2i(Loc.x, Loc.y + 1));
  return list;
}

inline double heuristic(sf::Vector2i Loc1, sf::Vector2i Loc2)
{
  return abs(Loc1.x - Loc2.x) + abs(Loc1.y - Loc2.y);
}

int Grid::aStarSearch(sf::Vector2i currentLoc, sf::Vector2i destLoc)
{


}
