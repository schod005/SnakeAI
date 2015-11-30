#include "Constants.h"
#ifndef SNAKE_HPP
#define SNAKE_HPP

bool boundary_check(int, sf::Vector2i);

enum{
	LEFT = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3
};

class Snake
{
public:
	Snake();
	Snake(Grid*, int x, int y);
	void randMove();
	void aStarMove();
	bool checkApple(int);



private:
	int length;
	Grid* GRID;
	struct Node
	{
		Node* next;
		Node* prev;
		sf::Vector2i location;
	}*head;

	Node *tail;
};

#endif

Snake::Snake()
{
	//empty
}

Snake::Snake(Grid* Grid_, int x, int y)
{
	length = 1;
	head = new Node;
	head->next = nullptr;
	head->prev = nullptr;
	//head->location.x = rand() % GRID_SIZE;
	//head->location.y = rand() % GRID_SIZE;
	head->location.x = x;
	head->location.y = y;
	tail = head;

	GRID = Grid_;
	GRID->getDrawGrid()[x][y].setFillColor(sf::Color::Black);
}

void Snake::randMove()
{
	//0 move left
	//1 move up
	//2 move right
	//3 move down


	int move;

	//testing if we are sitting on boundary cases elminating those movements
	if ((head->location.x == 0) && (head->location.y == 0))                    //move right if at top left corner
		move = RIGHT;
	else if ((head->location.x == GRID->getCols() - 1) && (head->location.y == 0))        //move down if at top right corner
		move = DOWN;
	else if ((head->location.x == GRID->getCols() - 1) && (head->location.y == GRID->getRows() - 1)) //move left if at bottum right corner
		move = LEFT;
	else if ((head->location.x == 0) && (head->location.y == GRID->getRows() - 1))        //move up if bottum left corner
		move = UP;
	else if ((head->location.x == 0))
		move = RIGHT;
	else if ((head->location.x == GRID->getCols() - 1))
		move = DOWN;
	else if ((head->location.y == 0))
		move = DOWN;
	else if ((head->location.y == GRID->getRows() - 1))
		move = UP;
	else
		move = rand() % 4;

	while (true)
	{
		if (move == UP)
		{
			if (!boundary_check(move, head->location))
			{
				move = rand() % 4;
			}
			else if (GRID->getDrawGrid()[head->location.x][head->location.y - 1].getFillColor() != sf::Color(140, 140, 140, 255) &&
				GRID->getDrawGrid()[head->location.x][head->location.y - 1].getFillColor() != sf::Color::Red)
			{
				move = rand() % 4;
			}
			else
				break;
		}
		if (move == DOWN)
		{
			if (!boundary_check(move, head->location))
			{
				move = rand() % 4;
			}
			else if (GRID->getDrawGrid()[head->location.x][head->location.y + 1].getFillColor() != sf::Color(140, 140, 140, 255) &&
				GRID->getDrawGrid()[head->location.x][head->location.y + 1].getFillColor() != sf::Color::Red)
			{
				move = rand() % 4;
			}
			else
				break;
		}
		if (move == LEFT)
		{
			if (!boundary_check(move, head->location))
			{
				move = rand() % 4;
			}
			else if (GRID->getDrawGrid()[head->location.x - 1][head->location.y].getFillColor() != sf::Color(140, 140, 140, 255) &&
				GRID->getDrawGrid()[head->location.x - 1][head->location.y].getFillColor() != sf::Color::Red)
			{
				move = rand() % 4;
			}
			else
				break;
		}
		if (move == RIGHT)
		{
			if (!boundary_check(move, head->location))
			{
				move = rand() % 4;
			}
			else if (GRID->getDrawGrid()[head->location.x + 1][head->location.y].getFillColor() != sf::Color(140, 140, 140, 255) &&
				GRID->getDrawGrid()[head->location.x + 1][head->location.y].getFillColor() != sf::Color::Red)
			{
				move = rand() % 4;
			}
			else
				break;
		}
	}

	if (checkApple(move))
	{
		//std::cout << length << std::endl;
		//if apple is eaten, add a new head at its location
		Node* newHead = new Node;
		newHead->next = head;
		newHead->prev = nullptr;
		head->prev = newHead;

		switch (move)
		{
		case UP:
			newHead->location.x = head->location.x;
			newHead->location.y = head->location.y - 1;
			break;
		case DOWN:
			newHead->location.x = head->location.x;
			newHead->location.y = head->location.y + 1;
			break;
		case LEFT:
			newHead->location.x = head->location.x - 1;
			newHead->location.y = head->location.y;
			break;
		case RIGHT:
			newHead->location.x = head->location.x + 1;
			newHead->location.y = head->location.y;
			break;
		default:
			break;
		}
		head = newHead;
		length++;

		GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Black);
		GRID->generateApple();
	}
	else
	{
		if (length == 1)
		{
			//if length is 1, head and tail are pointing at the same thing, so just move head
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color(140, 140, 140, 255));
			switch (move)
			{
			case UP:
				head->location.y--;
				break;
			case DOWN:
				head->location.y++;
				break;
			case LEFT:
				head->location.x--;
				break;
			case RIGHT:
				head->location.x++;
				break;
			default:
				break;
			}
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Green);
		}
		else
		{
			//update colors and move tail to location of move
			GRID->getDrawGrid()[tail->location.x][tail->location.y].setFillColor(sf::Color(140, 140, 140, 255));
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Black);

			Node* tempTail = tail;
			tail = tail->prev;
			tempTail->prev->next = nullptr;
			tempTail->prev = nullptr;
			tempTail->next = head;
			head->prev = tempTail;
			head = tempTail;

			switch (move)
			{
			case UP:
				head->location.y = head->next->location.y - 1;
				head->location.x = head->next->location.x;
				break;
			case DOWN:
				head->location.y = head->next->location.y + 1;
				head->location.x = head->next->location.x;
				break;
			case LEFT:
				head->location.y = head->next->location.y;
				head->location.x = head->next->location.x - 1;
				break;
			case RIGHT:
				head->location.y = head->next->location.y;
				head->location.x = head->next->location.x + 1;
				break;
			default:
				break;
			}
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Green);
		}
	}

}

bool Snake::checkApple(int move)
{
	sf::Vector2i appleLoc = GRID->getAppleLoc();
	//std::cout << "apple at location (" << appleLoc.x << ',' << appleLoc.y << ")" << std::endl;
	//std::cout << "head at location (" << head->location.x << ',' << head->location.y << ")" << std::endl;

	switch (move)
	{
	case UP:
		if (appleLoc.x == head->location.x && appleLoc.y == head->location.y - 1)
			return true;
		break;
	case DOWN:
		if (appleLoc.x == head->location.x && appleLoc.y == head->location.y + 1)
			return true;
		break;
	case LEFT:
		if (appleLoc.x == head->location.x - 1 && appleLoc.y == head->location.y)
			return true;
		break;
	case RIGHT:
		if (appleLoc.x == head->location.x + 1 && appleLoc.y == head->location.y)
			return true;
		break;
	default:
		return false;
	}
	return false;
}

void Snake::aStarMove()
{

}

bool boundary_check(int move, sf::Vector2i location)
{
	if ((location.x == 0 && move == LEFT))
		return false;
	else if ((location.x == GRID_SIZE - 1 && move == RIGHT))
		return false;
	else if ((location.y == 0 && move == UP))
		return false;
	else if ((location.y == GRID_SIZE - 1 && move == DOWN))
		return false;
	return true;
}