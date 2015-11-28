#include "Constants.h"
#ifndef SNAKE_HPP
#define SNAKE_HPP

class Snake
{
public:
	Snake();
	Snake(Grid*);
	void randMove();
	bool checkApple(int);

	enum{
		LEFT = 0,
		UP = 1,
		RIGHT = 2,
		DOWN = 3
	};

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

Snake::Snake(Grid* Grid_)
{
	length = 1;
	head = new Node;
	head->next = nullptr;
	head->prev = nullptr;
	//head->location.x = rand() % GRID_SIZE;
	//head->location.y = rand() % GRID_SIZE;
	head->location.x = 0;
	head->location.y = 0;
	tail = head;

	GRID = Grid_;
	GRID->getDrawGrid()[0][0].setFillColor(sf::Color::Black);
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

	if (checkApple(move))
	{
		//std::cout << length << std::endl;
		//if apple is eaten, add a new head at its location
		Node* newHead = new Node;
		newHead->next = head;
		newHead->prev = nullptr;

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
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Black);
		}
		else
		{
			//update colors and move tail to location of move
			GRID->getDrawGrid()[tail->location.x][tail->location.y].setFillColor(sf::Color(140, 140, 140, 255));
			head->next = tail;
			tail->prev = head;
			head = tail;
			tail->prev->next = nullptr;
			tail = tail->prev;
			head->next = nullptr;
			switch (move)
			{
			case UP:
				head->location.y = head->prev->location.y - 1;
				head->location.x = head->prev->location.x;
				break;
			case DOWN:
				head->location.y = head->prev->location.y + 1;
				head->location.x = head->prev->location.x;
				break;
			case LEFT:
				head->location.y = head->prev->location.y;
				head->location.x = head->prev->location.x - 1;
				break;
			case RIGHT:
				head->location.y = head->prev->location.y;
				head->location.x = head->prev->location.x + 1;
				break;
			default:
				break;
			}
			GRID->getDrawGrid()[head->location.x][head->location.y].setFillColor(sf::Color::Black);
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