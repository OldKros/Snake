#pragma once
#include "SnakeNode.h"

#include <vector>

class Food
{
public:
    int x, y;

    Food();
    void Draw();
    void Undraw();
    void Spawn();
    void Respawn(const std::vector<SnakeNode>& _snake_body);
};

