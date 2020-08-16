#pragma once

#include <vector>

class SnakeNode;

class Food
{
public:
    int x, y;

    Food();
    ~Food();
    void Draw();
    void Undraw();
    void Spawn();
    void Respawn(const std::vector<SnakeNode>& snake_body);
};

