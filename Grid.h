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

private:
	int **grid;
	int rows;
	int cols;
	sf::RectangleShape **drawGrid;
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
	grid = new int*[rows];
	for (int i = 0; i < rows; i++)
		grid[i] = new int[cols];

	drawGrid = new sf::RectangleShape*[rows];
	for (int i = 0; i < rows; i++)
	{
		drawGrid[i] = new sf::RectangleShape[cols];
	}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			drawGrid[i][j].setSize(sf::Vector2f(WINDOW_WIDTH / rows - 2,
											    WINDOW_HEIGHT / cols - 2));
			drawGrid[i][j].setPosition(sf::Vector2f(i * WINDOW_WIDTH / rows + 1,
													j * WINDOW_HEIGHT / cols + 1));
			drawGrid[i][j].setFillColor(sf::Color(140, 140, 140, 255));
			
		}
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
