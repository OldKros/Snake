#include "SnakeNode.h"

#include <iostream>

SnakeNode::SnakeNode()
    : x(0), y(0), ox(0), oy(0), direction(eDirection::RIGHT), odirection(direction)
{
}

SnakeNode::SnakeNode(int x, int y, eDirection direction)
    : x(x), y(y), ox(0), oy(0), direction(direction), odirection(direction)
{
}

void SnakeNode::ChangeDirection(eDirection direction)
{
    this->direction = direction;
}

void SnakeNode::Draw()
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(hOut, p);
    std::cout << '#';
}

void SnakeNode::Undraw()
{
    COORD p;
    p.X = ox;
    p.Y = oy;
    SetConsoleCursorPosition(hOut, p);
    std::cout << ' ';
}

void SnakeNode::MoveNode(int x, int y, eDirection direction)
{
    ox = this->x;
    oy = this->y;
    odirection = this->direction;

    this->x = x;
    this->y = y;
    this->direction = direction;
}
