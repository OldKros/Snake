#include "SnakeNode.h"

#include <iostream>

SnakeNode::SnakeNode()
    : x(0), y(0), direction(eDirection::RIGHT), odirection(direction)
{
}

SnakeNode::SnakeNode(int _x, int _y, eDirection _direction)
    : x(_x), y(_y), direction(_direction), odirection(_direction)
{
}

void SnakeNode::ChangeDirection(eDirection _direction)
{
    direction = _direction;
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

void SnakeNode::MoveNode(int _x, int _y, eDirection _direction)
{
    ox = x;
    oy = y;
    odirection = direction;

    x = _x;
    y = _y;
    direction = _direction;
}
