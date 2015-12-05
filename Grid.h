#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <iostream>
#include <queue>
#include <functional>
#include <unordered_map>
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
	std::vector<sf::Vector2i> reconstruct_path(sf::Vector2i& currentLoc, sf::Vector2i& destLoc, std::unordered_map<int, int>&);

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

	while (drawGrid[rand_col][rand_row].getFillColor() == sf::Color::Black ||
		   drawGrid[rand_col][rand_row].getFillColor() == sf::Color::Green)
	{
		rand_row = rand() % rows;
		rand_col = rand() % cols;
	}

//	std::cout << "PLACING APPLE AT (" << rand_col << "," << rand_row << ")\n";

	appleLoc.x = rand_col;
	appleLoc.y = rand_row;

	drawGrid[appleLoc.x][appleLoc.y].setFillColor(sf::Color::Red);
}

std::vector<sf::Vector2i> Grid::neighbors(sf::Vector2i Loc)
{
  std::vector<sf::Vector2i> list;
  if(Loc.x - 1 >= 0 && (drawGrid[Loc.x - 1][Loc.y].getFillColor() == sf::Color(140,140,140,255) || drawGrid[Loc.x - 1][Loc.y].getFillColor() == sf::Color::Red))
    list.emplace_back(sf::Vector2i(Loc.x - 1, Loc.y));
  if(Loc.x + 1 < GRID_SIZE && (drawGrid[Loc.x + 1][Loc.y].getFillColor() == sf::Color(140,140,140,255) || drawGrid[Loc.x + 1][Loc.y].getFillColor() == sf::Color::Red))
    list.emplace_back(sf::Vector2i(Loc.x + 1, Loc.y));
  if(Loc.y - 1 >= 0 && (drawGrid[Loc.x][Loc.y - 1].getFillColor() == sf::Color(140,140,140,255) || drawGrid[Loc.x][Loc.y - 1].getFillColor() == sf::Color::Red))
    list.emplace_back(sf::Vector2i(Loc.x, Loc.y - 1));
  if(Loc.y + 1 < GRID_SIZE && (drawGrid[Loc.x][Loc.y + 1].getFillColor() == sf::Color(140,140,140,255) || drawGrid[Loc.x][Loc.y + 1].getFillColor() == sf::Color::Red))
    list.emplace_back(sf::Vector2i(Loc.x, Loc.y + 1));
  return list;
}

int sfVecToInt(sf::Vector2i vec)
{
	return vec.x + GRID_SIZE * vec.y;
}

sf::Vector2i intTosfVec(int num)
{
	if (num >= GRID_SIZE)
		return sf::Vector2i(num % GRID_SIZE, num / GRID_SIZE);
	else
		return sf::Vector2i(num, 0);
}

inline double heuristic(sf::Vector2i Loc1, sf::Vector2i Loc2)
{
  return abs(Loc1.x - Loc2.x) + abs(Loc1.y - Loc2.y);
}

template <class T> struct greater1
{
	bool operator() (const T& a, const T& b) const { return a.first > b.first; }
};

struct PriorityQueue{
	typedef std::pair<int, sf::Vector2i> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
						greater1<PQElement>> elements;

	inline bool empty() { return elements.empty(); }

	inline void put(sf::Vector2i item, int priority)
	{
		elements.emplace(priority, item);
	}

	inline sf::Vector2i get()
	{
		sf::Vector2i best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

int Grid::aStarSearch(sf::Vector2i currentLoc, sf::Vector2i destLoc)
{
	/*
	for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++)
	{
	sf::Vector2i test = intTosfVec(i);
	int test2 = sfVecToInt(test);
	std::cout << "(" << test.x << "," << test.y << ") ";
	std::cout << test2 << std::endl;
	}*/
	PriorityQueue frontier;
	frontier.put(currentLoc, 0);

	std::unordered_map<int, int> came_from;
	std::unordered_map<int, int> cost_so_far;

	came_from[sfVecToInt(currentLoc)] = sfVecToInt(currentLoc);
	cost_so_far[sfVecToInt(currentLoc)] = 0;

	//	std::cout << "APPLE LOCATION: (" << destLoc.x << "," << destLoc.y << ")\n";
	//	std::cout << "$$$$$$$$$$$$$$$$$\n";
	while (!frontier.empty())
	{
		auto current = frontier.get();
		if (current == destLoc)
		{
			break;
		}

		for (auto next : neighbors(current))
		{
			//		std::cout << "NEIGHBORS " << "(" << next.x << "," << next.y << ")\n";
			int new_cost = cost_so_far[sfVecToInt(current)] + 1;
			if (!cost_so_far.count(sfVecToInt(next)) || new_cost < cost_so_far[sfVecToInt(next)])
			{
				cost_so_far[sfVecToInt(next)] = new_cost;
				int priority = new_cost + heuristic(next, destLoc);
				frontier.put(next, priority);
				came_from[sfVecToInt(next)] = sfVecToInt(current);
			}
		}
	}
	//for (auto next : came_from)
	//{
	//	std::cout << "CHECKING NODE (" << next.first->x << "," << next.first->y << ")" << std::endl;
	//}
	std::vector <sf::Vector2i> path = reconstruct_path(currentLoc, destLoc, came_from);
//	std::cout << "MOVE TO LOCATION (" << intTosfVec(came_from[sfVecToInt(currentLoc)]).x 
//			  << "," << intTosfVec(came_from[sfVecToInt(currentLoc)]).y << ")\n";
			
	sf::Vector2i next = path[1];
	if (currentLoc.x - next.x == -1)
		return RIGHT;
	if (currentLoc.x - next.x == 1)
		return LEFT;
	if (currentLoc.y - next.y == -1)
		return DOWN;
	if (currentLoc.y - next.y == 1)
		return UP;
	return 0;
}

std::vector<sf::Vector2i> Grid::reconstruct_path(sf::Vector2i& currentLoc, sf::Vector2i& destLoc, std::unordered_map<int, int>& came_from)
{
	std::vector<sf::Vector2i> path;
	sf::Vector2i current = destLoc;
	path.push_back(current);
	//std::cout << std::endl << "###################\n";
	int count = 0;
	while (current != currentLoc)
	{
		count++;
		if (count > GRID_SIZE * GRID_SIZE)
		{
			std::cout << "DEAD" << std::endl;
		}
		current = intTosfVec(came_from[sfVecToInt(current)]);
		path.push_back(current);
	//	std::cout << "(" << current.x << "," << current.y << ")\n";
	}
	std::reverse(path.begin(), path.end());
	for (int i = 1; i < path.size(); i++)
	{
	//	drawGrid[path[i].x][path[i].y].setFillColor(sf::Color::Yellow);
	}
	return path;
}
