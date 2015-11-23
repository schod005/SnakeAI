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
	void randMove();


private:
	int **grid;
	int rows;
	int cols;
	sf::RectangleShape **drawGrid;
	std::pair <int, int> appleLoc; //holds coordinates to apple
	std::vector <std::pair<int, int>> snakeLoc; //holds coordinates snake is in

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

	//generating two rand values for loc of apple
	int rand_row = rand() % rows;
	int rand_col = rand() % cols;

	//assigning appleLoc first random location
	appleLoc = std::make_pair(rand_col, rand_row);

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

	//adding a random apple at start of creation
	drawGrid[rand_col][rand_row].setFillColor(sf::Color::Red);

	//snake start
	drawGrid[0][0].setFillColor(sf::Color::Black);
	//setting location of snake
	snakeLoc.push_back(std::make_pair(0, 0));

}

//
void Grid::randMove()
{
	//0 move left
	//1 move up
	//2 move right
	//3 move down

	int move;

	//testing if we are sitting on boundary cases elminating those movements
	if ((snakeLoc.at(0).first == 0) && (snakeLoc.at(0).second == 0))                    //move right if at top left corner
		move = 2;  
	else if ((snakeLoc.at(0).first == cols - 1) && (snakeLoc.at(0).second == 0))        //move down if at top right corner
		move = 3;
	else if ((snakeLoc.at(0).first == cols - 1) && (snakeLoc.at(0).second == rows - 1)) //move left if at bottum right corner
		move = 0;
	else if ((snakeLoc.at(0).first == 0) && (snakeLoc.at(0).second == rows - 1))        //move up if bottum left corner
		move = 1;	
	else if ((snakeLoc.at(0).first == 0))
		move = 2;
	else if ((snakeLoc.at(0).first == cols - 1))
		move = 3;
	else if ((snakeLoc.at(0).second == 0))
		move = 3;
	else if ((snakeLoc.at(0).second == rows - 1))
		move = 1;
	else
		move = rand() % 4;                                                              //free to move anywhere not at corner case

	//making appropriate location updates and coloring cells in draw grid representing snake	
	switch (move)
	{
		case 0: //moves snake left one cell
		{
			//clear out old location
			drawGrid[snakeLoc.at(0).first][snakeLoc.at(0).second].setFillColor(sf::Color(140, 140, 140, 255));
			//update new snake location and remove old
			snakeLoc.push_back(std::make_pair(snakeLoc.at(0).first - 1, snakeLoc.at(0).second));
			snakeLoc.erase(snakeLoc.begin());
			//color in snake at new location
			drawGrid[snakeLoc.at(0).first][snakeLoc.at(0).second].setFillColor(sf::Color::Black);
			break;
		}
		case 1: //move snake up one cell
		{
			//clear out old location
			drawGrid[snakeLoc.at(0).first][snakeLoc.at(0).second].setFillColor(sf::Color(140, 140, 140, 255));
			//update new snake location and remove old
			snakeLoc.push_back(std::make_pair(snakeLoc.at(0).first, snakeLoc.at(0).second - 1));
			snakeLoc.erase(snakeLoc.begin());
			//color in snake at new location
			drawGrid[snakeLoc.at(0).first][snakeLoc.at(0).second].setFillColor(sf::Color::Black);
			break;
		}		
		case 2: //move snake right one cell
		{
			//clear out old location
			drawGrid[snakeLoc.at(0).first][snakeLoc.at(0).second].setFillColor(sf::Color(140, 140, 140, 255));
			//update new snake location and remove old
			snakeLoc.push_back(std::make_pair(snakeLoc.at(0).first + 1, snakeLoc.at(0).second));
			snakeLoc.erase(snakeLoc.begin());
			//color in snake at new location
			drawGrid[snakeLoc.at(0).first][snakeLoc.at(0).second].setFillColor(sf::Color::Black);
			break;
		}		
		case 3: //move snake down one cell
		{
			//clear out old location
			drawGrid[snakeLoc.at(0).first][snakeLoc.at(0).second].setFillColor(sf::Color(140, 140, 140, 255));
			//update new snake location and remove old
			snakeLoc.push_back(std::make_pair(snakeLoc.at(0).first, snakeLoc.at(0).second + 1));
			snakeLoc.erase(snakeLoc.begin());
			//color in snake at new location
			drawGrid[snakeLoc.at(0).first][snakeLoc.at(0).second].setFillColor(sf::Color::Black);
			break;
		}		
		default:
			break;

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


