#pragma once
#include "Globals.h"

class SnakeNode
{
public:
    int x, y;
    int ox, oy = ox = 0;
    eDirection direction;
    eDirection odirection;

    SnakeNode();
    SnakeNode(int _x, int _y, eDirection _direction);
    void ChangeDirection(eDirection _direction);
    void Draw();
    void Undraw();
    void MoveNode(int _x, int _y, eDirection _direction);
};

