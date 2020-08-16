#pragma once
#include "Globals.h"

class SnakeNode
{
public:
    int x, y;
    int ox, oy;
    eDirection direction;
    eDirection odirection;

    SnakeNode();
    SnakeNode(int x, int y, eDirection direction);
    void ChangeDirection(eDirection direction);
    void Draw();
    void Undraw();
    void MoveNode(int x, int y, eDirection direction);
};

